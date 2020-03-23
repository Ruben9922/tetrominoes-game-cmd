import curses
from random import randrange
import copy


class Shape:
    def __init__(self, cells):
        self.cells = cells

    def size(self):
        xs = list(map(lambda c: c[1], self.cells))
        ys = list(map(lambda c: c[0], self.cells))
        print("hello")
        print(ys)
        return ((max(ys) - min(ys) + 1) if ys else 0), ((max(xs) - min(xs) + 1) if xs else 0)


class ShapeInstance:
    def __init__(self, stdscr, position, shape):
        self.stdscr = stdscr
        self.position = position
        self.shape = shape

    def draw(self):
        for cell in self.shape.cells:
            self.stdscr.addch(self.position[0] + cell[0], self.position[1] + cell[1], "x")

    def get_cells_world(self):
        return map(lambda c: (self.position[0] + c[0], self.position[1] + c[1]), self.shape.cells)

    def is_within_window(self, translation=(0, 0)):
        return all(map(lambda c: 0 <= c[0] + translation[0] < self.stdscr.getmaxyx()[0]
                                 and 0 <= c[1] + translation[1] < self.stdscr.getmaxyx()[1], self.get_cells_world()))


class Game:
    all_shapes = [
        Shape([
            (0, 0),
            (0, 1),
            (0, 2),
            (0, 3)
        ]),
        Shape([
            (1, 0),
            (0, 0),
            (0, 1),
            (0, 2)
        ]),
        Shape([
            (0, 0),
            (0, 1),
            (0, 2),
            (1, 2)
        ]),
        Shape([
            (0, 0),
            (0, 1),
            (1, 0),
            (1, 1)
        ]),
        Shape([
            (0, 0),
            (0, 1),
            (1, 1),
            (1, 2)
        ]),
        Shape([
            (0, 0),
            (0, 1),
            (0, 2),
            (1, 1)
        ]),
        Shape([
            (0, 1),
            (0, 2),
            (1, 0),
            (1, 1)
        ])
    ]

    def __init__(self, stdscr):
        self.stdscr = stdscr
        self.shape_instances = []
        self.moving_shape_instance = self.generate_shape_instance()

    def generate_shape_instance(self):
        # Pick random shape
        shape = Game.all_shapes[randrange(len(Game.all_shapes))]

        # Initially position so that shape is in top centre
        position = (0, (self.stdscr.getmaxyx()[1] - shape.size()[1]) // 2)

        return ShapeInstance(self.stdscr, position, shape)

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
        velocity = (1, 0)

        if key == curses.KEY_LEFT:
            velocity = (velocity[0], -1)
        elif key == curses.KEY_RIGHT:
            velocity = (velocity[0], 1)

        if self.moving_shape_instance.is_within_window(velocity):
            self.moving_shape_instance.position = (self.moving_shape_instance.position[0] + velocity[0],
                                                   self.moving_shape_instance.position[1] + velocity[1])
        else:
            self.shape_instances.append(self.moving_shape_instance)
            self.moving_shape_instance = self.generate_shape_instance()

    def draw(self):
        self.stdscr.clear()

        for shape_instance in self.shape_instances:
            shape_instance.draw()

        self.moving_shape_instance.draw()


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
