import math

import os
import pygame

import util


class CellView(pygame.sprite.Sprite):

    TERRAIN_TYPE = [(76, 147, 44),
                    (31,  60, 18),
                    (100,  100, 100),
                    (76, 147, 44),
                    (67,  39, 14)]

    WIDTH  = 30
    HEIGHT = 2 * WIDTH / math.sqrt(3)
    
    def __init__(self, row, col, terrain=0, base=-1, crystals=0):
        pygame.sprite.Sprite.__init__(self)

        self.row = int(row)
        self.col = int(col)
        self.cx, self.cy = util.convert(self.row, self.col)

        self.base = int(base)
        self.crystals = crystals
        self.terrain = self.TERRAIN_TYPE[int(terrain)]
        self.crystalImage = pygame.image.load(os.path.join(os.path.dirname(os.path.realpath(__file__)), 'assets/crystal.png'))
        if terrain == "3":
            self.image = pygame.image.load(os.path.join(os.path.dirname(os.path.realpath(__file__)), 'assets/rock.png'))
        else:
            self.image = None

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
        if self.image is not None:
            rect = self.image.get_rect()
            rect.topleft = [self.edges[5][0] + 8, self.edges[5][1] - 10]
            screen.blit(self.image, rect)

        if self.crystals > 0:
            rect = self.crystalImage.get_rect()
            rect.topleft = [self.edges[3][0] - 6, self.edges[3][1] - 12]
            screen.blit(self.crystalImage, rect)

            font = pygame.font.SysFont("monospace", 8)
            label = font.render(str(self.crystals), 1, (243, 52, 156))
            screen.blit(label, (rect[0] - 1, rect[1] - 8))

        if self.base != -1:
            font = pygame.font.SysFont("monospace", 12)
            label = font.render("B{}".format(self.base), 1, (255, 255, 0))
            screen.blit(label, (self.cx - 20, self.cy - 5))
        # else:
        #     # TODO: The code below prints the Cell [Row, Column] in the screen , just for Debug
        #     font = pygame.font.SysFont("monospace", 12)
        #     label = font.render("[{}, {}]".format(self.row, self.col), 1, (255, 255, 0))
        #     screen.blit(label, (self.cx - 20, self.cy - 5))