import fileinput
import pygame

from arena_view  import ArenaView
from cell_view   import CellView
from entity_view import EntityView

try:
   input = raw_input
except NameError:
   pass


class GameView:

    def __init__(self):
        pygame.init()
        self.entities = {}

        self.arena_view = None
        self.screen     = None
        self.init_screen()

    def ini_entity(self, entity):
        #Handle paths with spaces in them
        imagePath = entity[3]
        for i in range(4, len(entity)):
            imagePath += " "+entity[i]
        print("imagePath: "+imagePath)
        self.entities[int(entity[0])] = EntityView(entity[0], entity[1], entity[2], imagePath)

    def init_screen(self):
        token = input().split()
        if token[0] == 'arena':
            self.arena_view = ArenaView(token[1], token[2])
            screen_width    = 2 * self.arena_view.width * CellView.WIDTH + CellView.WIDTH
            screen_height   = int(1.5 * CellView.HEIGHT * self.arena_view.height + CellView.HEIGHT / 2)
            self.screen     = pygame.display.set_mode((screen_width, screen_height))
        else:
            print("Arena configuration not found")
            self.unload()
            exit()

    def load(self):
        self.screen.fill((0, 200, 0))
        self.arena_view.load()

    def render(self):
        self.arena_view.render(self.screen)
        for entity in self.entities.values():
            entity.render(self.screen)
        pygame.time.wait(1)
        pygame.display.update()
        pygame.event.pump()

    def update_entity(self, e_id, row, col):
        self.entities[e_id].update(row, col)

    def update(self):
        for line in fileinput.input():
            token = line.split()

            if token[0] == 'quit':
                break

            if token[0] == 'entity':
                self.ini_entity(token[1:])
                continue

            if token[0] == 'cell':
                self.arena_view.update(CellView(token[1], token[2], token[3], token[4], token[5]))
                continue

            e_id, row, col = list(map(int, token))
            self.update_entity(e_id, row, col)
            self.render()
        self.unload()

    def unload(self):
        pygame.quit()

    def show(self):
        self.load()
        self.update()


if __name__ == "__main__":
    GameView().show()
