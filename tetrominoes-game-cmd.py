import curses
from random import randrange
import numpy as np
import game_utilities as gu


def create_shape():
    all_points = [
        np.array([
            [0, 0],
            [0, 1],
            [0, 2],
            [0, 3],
        ]),
        np.array([
            [1, 0],
            [0, 0],
            [0, 1],
            [0, 2],
        ]),
        np.array([
            [0, 0],
            [0, 1],
            [0, 2],
            [1, 2],
        ]),
        np.array([
            [0, 0],
            [0, 1],
            [1, 0],
            [1, 1],
        ]),
        np.array([
            [0, 0],
            [0, 1],
            [1, 1],
            [1, 2],
        ]),
        np.array([
            [0, 0],
            [0, 1],
            [0, 2],
            [1, 1],
        ]),
        np.array([
            [0, 1],
            [0, 2],
            [1, 0],
            [1, 1],
        ]),
    ]
    points = all_points[randrange(len(all_points))]
    shape = gu.Shape(points)
    return shape


def create_shape_instance(stdscr):
    # Pick random shape
    shape = create_shape()

    # Initially position so that shape is in top centre
    return gu.GameObject(stdscr, shape, char="x",
                         position=gu.align(stdscr, shape.size, gu.HorizontalAlignment.CENTER, gu.VerticalAlignment.TOP),
                         velocity=gu.DOWN)


class Game:
    def __init__(self, stdscr):
        self.stdscr = stdscr
        self.shape_instances = []
        self.moving_shape_instance = create_shape_instance(stdscr)

    def play(self):
        self.stdscr.timeout(500)

        self.draw()
        key = None
        # getch return value of 27 corresponds to escape key - doesn't look like curses has a constant for this
        while key != 27 and key != ord("q"):
            key = self.stdscr.getch()
            self.update(key)
            self.draw()

        self.stdscr.nodelay(False)

    def update(self, key):
        if key == curses.KEY_LEFT:
            translation = gu.LEFT
            self.moving_shape_instance.velocity = np.array([0, 0])
        elif key == curses.KEY_RIGHT:
            translation = gu.RIGHT
            self.moving_shape_instance.velocity = np.array([0, 0])
        else:
            translation = gu.ZERO
            self.moving_shape_instance.velocity = np.array([1, 0])

        self.moving_shape_instance.position += translation
        if self.moving_shape_instance.is_within_window and not self.check_for_collision():
            self.moving_shape_instance.update()
        else:
            self.moving_shape_instance.velocity = np.array([0, 0])
            self.shape_instances.append(self.moving_shape_instance)
            self.moving_shape_instance = create_shape_instance(self.stdscr)

    def draw(self):
        self.stdscr.clear()

        for shape_instance in self.shape_instances:
            shape_instance.draw()

        self.moving_shape_instance.draw()

    def check_for_collision(self):
        # Translate the moving shape instance's cells by the given translation
        # shape_instance_cells_translated = map(lambda c: (c[0] + translation[0], c[1] + translation[1]),
        #                                       self.moving_shape_instance.get_cells_world())
        # For each shape instance, check whether its cells are disjoint from the moving shape instances's cells
        # (i.e. whether their intersection is empty - none of the cells overlap)
        # If not, there has been a collision between this shape instance and the moving shape instance
        # Obviously want to return True if the moving shape instance has collided with *any* shape instance (hence using
        # `any` function)
        # In other words, check whether the moving shape instance's cells overlap with any shape instance's cells
        # return any(map(lambda si: not set(shape_instance_cells_translated).isdisjoint(si.get_cells_world()),
        #                self.shape_instances))

        # return gu.intersect2d(self.moving_shape_instance.cells_world, np.vstack([x.cells_world for x in self.shape_instances]))

        return any(self.moving_shape_instance.collides_with(x) for x in self.shape_instances)


def main(stdscr):
    # TODO: Initialise colours

    # Show cursor
    curses.curs_set(1)

    # TODO: Title screen

    # Hide cursor
    curses.curs_set(0)

    game = Game(stdscr)
    game.play()

    # Show cursor
    curses.curs_set(1)

    # TODO: "Game over" screen


if __name__ == "__main__":
    curses.wrapper(main)
