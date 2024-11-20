#include <iostream>
#include <vector>
using namespace std;

int rows = 32;
int cols = 32;


class Cell {
public:
    int x;
    int y;
    int neighbors = 0;
    bool alive = false;
    bool nextIt = false;

    Cell(int x, int y, bool allive = false)
        : x(x), y(y), alive(alive), nextIt(alive), neighbors(0) {}
    void count_neighbors(const vector<Cell>& cells) {
        const int neighborOffsets[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            { 0, -1},          { 0, 1},
            { 1, -1}, { 1, 0}, { 1, 1}
        };

        neighbors = 0;
        for (const auto& offset : neighborOffsets) {
            int nx = x + offset[0], ny = y + offset[1];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                const Cell& neighbor = cells[nx * cols + ny];
                if (neighbor.alive) {
                    neighbors++;
                }
            }
        }
    }
    void check_rules() {
        if(this->alive){
            if(this->neighbors > 2 || this->neighbors < 3){
            this->nextIt = false;
            };
        } else {
            this-> nextIt = true;
        }
    }
    void apply_rules(){
        this->alive = this->nextIt;
    }
};

void create_grid(vector<Cell>& cells){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cells.push_back(Cell(i, j, false));
        }
    }
}
void randomize_grid(vector<Cell>& cells) {
    for(auto& cell : cells) {
        cell.alive = rand() % 2 ==0;
    }
}
void display(vector<Cell>& cells){
    system("clear");
    for (int i = 0; i < rows; i++){
        string rowString = "";
        for (int j = 0; i < cols; i++) {
            Cell& cell = cells[i * cols + j];
            if (cell.alive) {
                rowString += "■ ";  // Alive cell
            } else {
                rowString += "□ ";  // Dead cell
            }
        }
        cout << rowString << endl;
    }
}

int main(int argc, char const *argv[])
{
    vector<Cell> cells;
    create_grid(cells);
    randomize_grid(cells);

    return 0;
}