import cell_view


def convert(lin, col):
    x = (1 + lin % 2) * cell_view.CellView.WIDTH + 2 * col * cell_view.CellView.WIDTH
    y = 1.5 * lin * cell_view.CellView.HEIGHT + cell_view.CellView.HEIGHT
    return x, y
