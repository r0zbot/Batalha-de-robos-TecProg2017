#include <algorithm>

#include <application/component/hex.h>

#include <util/config.h>
#include <util/log.h>

Hex::Hex(const int col,
         const int row,
         const int base,
         const int occup,
         const int crystals,
         const Terrain terrain) :
        col(col), row(row),
        base(base), occup(occup),
        crystals(crystals), terrain(terrain) {}

Hex& Hex::operator=(const Hex &hex) = default;

bool Hex::operator==(const Hex &hex) const {
    return this->col == hex.col && this->row == hex.row;
}

bool Hex::operator!=(const Hex &hex) const {
    return !(*this == hex);
}

//string Hex::operator string() {
//    return {"Type: Cell; Col = " + to_string(this->col)
//            + "; Row = "         + to_string(this->row)
//            + "; Base = "        + to_string(this->base)
//            + "; Occup = "       + to_string(this->occup)
//            + "; Crystals = "    + to_string(this->crystals)};
//}

int Hex::distance(const Hex &hex) const {
    const vector<int> a = this->to_cube();
    const vector<int> b = hex.to_cube();
    return (abs(a[0] - b[0]) + abs(a[1] - b[1])) + abs(a[2] - b[2]) / 2;
}

int Hex::get_atr(const int i) const {
    if (i == 0) {
        return this->terrain;
    }
    if (i == 1) {
        return this->crystals;
    }
    if (i == 2) {
        return this->occup;
    }
    if (i == 3) {
        return this->base;
    }
    Log::error("Invalid Operand (Hex) parameter access: ATR " + to_string(i));
}

int Hex::get_base() const {
    return this->base;
}

int Hex::get_col() const {
    return this->col;
}

int Hex::get_occup() const {
    return this->occup;
}

int Hex::get_row() const {
    return this->row;
}

Terrain Hex::get_terrain() const {
    return this->terrain;
}

bool Hex::insert_crystal() {
    if (this->crystals < MAX_CRYSTALS_PER_CELL){
        ++this->crystals;
        return true;
    }
    return false;
}

Hex Hex::neighbor(const Direction d) const {
    int parity = this->col & 1;
    Hex dir = directions[parity][d];
    return {this->col + dir.col, this->row + dir.row};
}

unordered_set<Hex> Hex::range(const int n) const {
    unordered_set<Hex> results;
    const vector<int> a = this->to_cube();
    for (int x = -n; x <= n; x++) {
        for (int y = max(-n, -x - n); y <= min(n, n - x); y++) {
            results.insert(Hex::to_offset(a[0] + x, a[2] - x - y));
        }
    }
    results.erase(*this);
    return results;
}

bool Hex::remove_crystal() {
    if(this->crystals > 0){
        --this->crystals;
        return true;
    }
    return false;
}

void Hex::set_base(const int base) {
    this->base = base;
}

void Hex::set_crystals(const int crystals) {
    this->crystals = crystals;
}

void Hex::set_occup(const int occup) {
    this->occup = occup;
}

void Hex::set_terrain(const Terrain terrain) {
    this->terrain = terrain;
}

vector<int> Hex::to_cube() const {
    int z = this->row - ((this->col + (this->col & 1)) / 2);
    return {this->col, - z - this->col, z};
}

Hex Hex::to_offset(int x, int z) {
    return {x, z + ((x + (x & 1)) / 2)};
}