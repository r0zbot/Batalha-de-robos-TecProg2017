class ArenaView:

    def __init__(self, height, width):
        self.grid   = []
        self.height = int(height)
        self.width  = int(width)

    def load(self):
        for row in range(self.height):
            self.grid.append([])
            for col in range(self.width):
                self.grid[row].append(None)

    def render(self, screen):
        for row in self.grid:
            for cell in row:
                cell.render(screen)

    def update(self, cell):
        self.grid[cell.row][cell.col] = cell
