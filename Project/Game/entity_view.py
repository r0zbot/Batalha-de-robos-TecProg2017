import pygame


class EntityView(pygame.sprite.Sprite):

    def __init__(self, id, lin, col, img_path):
        pygame.sprite.Sprite.__init__(self)
        self.id = int(id)
        self.lin = int(lin)
        self.col = int(col)
        self.image = pygame.image.load(img_path)

    @staticmethod
    def convert(lin, col):
        x = (1 + lin % 2) * 15 + 2 * col * 15
        y = 1.5 * lin * 15 + 15
        return x, y

    def render(self, scr):
        x, y = self.convert(self.lin, self.col)

        l0, h0, l1, h1 = self.image.get_rect()

        self.image.get_rect().topleft = [x - l1 / 2, y - h1 / 2]
        scr.blit(self.image, self.image.get_rect())

    def update(self, lin, col):
        self.lin = int(lin)
        self.col = int(col)
