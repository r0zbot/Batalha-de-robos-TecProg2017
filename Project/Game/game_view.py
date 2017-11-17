import fileinput

import pygame

from arena_view  import ArenaView
from cell_view   import CellView
from entity_view import EntityView


class GameView:

    def __init__(self):
        pygame.init()
        self.entities = {}
        self.arena_view = ArenaView(15, 15)
        self.screen = pygame.display.set_mode((2 * 15 * 30 + 30,
                                              int(1.5 * CellView.HEIGHT * 15 + CellView.HEIGHT / 2)))

    @staticmethod
    def convert(lin, col):
        x = (1 + lin % 2) * 15 + 2 * col * 15
        y = 1.5 * lin * 15 + 15
        return x, y

    def load(self):
        self.screen.fill((0, 200, 0))
        self.arena_view.load()

    def load_entity(self, entity):
        self.entities[entity.id] = entity

    def render(self):
        self.arena_view.render(self.screen)
        for entity in self.entities.values():
            entity.render(self.screen)
        pygame.time.wait(100)
        pygame.display.update()

    def update_entity(self, id, lin, col):
        self.entities[id].update(lin, col)

    def update(self):
        for line in fileinput.input():
            token = line.split()

            if token[0] == 'fim':
                break

            if token[0] == 'rob':
                self.load_entity(EntityView(token[1], token[2], token[3], token[4]))
                continue

            eid, lin, col = list(map(int, token))

            self.update_entity(eid, lin, col)
            self.render()

    def unload(self):
        pygame.quit()


if __name__ == "__main__":
    g = GameView()
    g.load()
    g.update()
