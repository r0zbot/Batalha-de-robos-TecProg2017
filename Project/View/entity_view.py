import pygame

import util


class EntityView(pygame.sprite.Sprite):

    def __init__(self, e_id, row, col, img_path):
        pygame.sprite.Sprite.__init__(self)
        self.e_id   = int(e_id)
        self.row    = int(row)
        self.col    = int(col)
        self.image  = pygame.image.load(img_path)
        self.bounds = self.image.get_rect()

    def render(self, scr):
        x, y = util.convert(self.row, self.col)

        l0, h0, l1, h1 = self.bounds

        self.bounds.topleft = [x - l1 / 2, y - h1 / 2]
        scr.blit(self.image, self.bounds)

    def update(self, row, col):
        self.row = int(row)
        self.col = int(col)
