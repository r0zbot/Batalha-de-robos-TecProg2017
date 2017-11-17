import math
import pygame


class CellView(pygame.sprite.Sprite):

    WIDTH = 30
    HEIGHT = 2 * WIDTH / math.sqrt(3)
    
    def __init__(self, lin, col, color=(200, 200, 200)):
        pygame.sprite.Sprite.__init__(self)
        
        self.cx, self.cy = self.convert(lin, col)
        self.color = color

        self.edges = (
            (self.cx,  self.cy - self.HEIGHT),
            (self.cx + self.WIDTH, self.cy - self.HEIGHT / 2),
            (self.cx + self.WIDTH, self.cy + self.HEIGHT / 2),
            (self.cx,  self.cy + self.HEIGHT),
            (self.cx - self.WIDTH, self.cy + self.HEIGHT / 2),
            (self.cx - self.WIDTH, self.cy - self.HEIGHT / 2),
        )

    @staticmethod
    def convert(lin, col):
        x = (1 + lin % 2) * 15 + 2 * col * 15
        y = 1.5 * lin * 15 + 15
        return x, y

    def draw(self, scr):
        pygame.draw.polygon(scr, self.color, self.edges, 0)
        pygame.draw.lines(scr, (0, 0, 0), True, self.edges, 2)
