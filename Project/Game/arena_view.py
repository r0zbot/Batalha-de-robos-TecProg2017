from cell_view import CellView


class ArenaView:

    def __init__(self, height, width):
        self.height = int(height)
        self.width = int(width)
        self.grid = []

    def load(self):
        for lin in range(self.height):
            self.grid.append([])
            for col in range(self.width):
                self.grid[lin].append(CellView(lin, col))

    def render(self, scr):
        for line in self.grid:
            for cell in line:
                cell.draw(scr)
