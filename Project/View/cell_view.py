import math
import pygame

import util


class CellView(pygame.sprite.Sprite):

    TERRAIN_TYPE = [(200, 200, 200),
                    (85,  107, 47),
                    (30,  144, 255),
                    (218, 165, 32),
                    (34,  139, 34)]

    WIDTH  = 30
    HEIGHT = 2 * WIDTH / math.sqrt(3)
    
    def __init__(self, row, col, terrain=0, base=-1, crystals=0):
        pygame.sprite.Sprite.__init__(self)

        self.row = int(row)
        self.col = int(col)
        self.cx, self.cy = util.convert(self.row, self.col)

        self.base = base
        self.crystals = crystals
        self.terrain = self.TERRAIN_TYPE[int(terrain)]

        self.edges = (
            (self.cx,  self.cy - self.HEIGHT),
            (self.cx + self.WIDTH, self.cy - self.HEIGHT / 2),
            (self.cx + self.WIDTH, self.cy + self.HEIGHT / 2),
            (self.cx,  self.cy + self.HEIGHT),
            (self.cx - self.WIDTH, self.cy + self.HEIGHT / 2),
            (self.cx - self.WIDTH, self.cy - self.HEIGHT / 2),
        )

    def render(self, screen):
        pygame.draw.polygon(screen, self.terrain, self.edges, 0)
        pygame.draw.lines(screen, (0, 0, 0), True, self.edges, 2)

        # TODO: The code below prints the Cell [Row, Column] in the screen , just for Debug
        font = pygame.font.SysFont("monospace", 12)
        label = font.render("[{}, {}]".format(self.row, self.col), 1, (255, 255, 0))
        screen.blit(label, (self.cx - 20, self.cy - 5))
