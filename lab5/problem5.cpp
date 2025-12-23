#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <ctime>    
#include <cstdlib> 

using namespace std;

// Disjoint Set implementation
class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) {
        // TODO: Initialize parent and rank arrays
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        // TODO: Implement find with path compression
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        // TODO: Implement union by rank
        int roota = find(x);
        int rootb = find(y);
        if (roota == rootb) return;
        if (rank[roota] < rank[rootb]) {
            parent[roota] = rootb;
        } else if (rank[roota] > rank[rootb]) {
            parent[rootb] = roota;
        } else {
            parent[rootb] = roota;
            rank[roota]++;
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

struct Wall {
    int cell1;
    int cell2;
    // For visualization logic (optional, but good for understanding)
    // 0: vertical wall between (r, c) and (r, c+1)
    // 1: horizontal wall between (r, c) and (r+1, c)
};

class MazeGenerator {
private:
    int width;
    int height;
    DisjointSet ds;
    vector<Wall> walls;
    
    // Grid representation for visualization
    // cells[r][c] stores bitmask of open directions: 1=Right, 2=Down, 4=Left, 8=Up
    vector<vector<int>> grid; 

public:
    MazeGenerator(int w, int h) : width(w), height(h), ds(w * h), grid(h, vector<int>(w, 0)) {
        // Initialize all possible walls
        // Cell index = row * width + col
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                int current = r * width + c;
                
                // Add vertical wall to the right (if not last column)
                if (c < width - 1) {
                    int right = r * width + (c + 1);
                    walls.push_back({current, right});
                }
                
                // Add horizontal wall below (if not last row)
                if (r < height - 1) {
                    int down = (r + 1) * width + c;
                    walls.push_back({current, down});
                }
            }
        }
    }

    void generate() {
        srand(time(0));
    
        // Initialize all walls as present (0 = all walls present)
        // Shuffle walls randomly
        for (int i = walls.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(walls[i], walls[j]);
        }
        
        // Process each wall using Kruskal's Algorithm
        for (const Wall& wall : walls) {
            int cell1 = wall.cell1;
            int cell2 = wall.cell2;
            
            // If cells are not connected, remove the wall
            if (!ds.connected(cell1, cell2)) {
                ds.unite(cell1, cell2);
                
                // Update grid bitmask to reflect removed wall
                int r1 = cell1 / width;
                int c1 = cell1 % width;
                int r2 = cell2 / width;
                int c2 = cell2 % width;
                
                if (r1 == r2 && c2 == c1 + 1) {
                    // Right wall removed
                    grid[r1][c1] |= 1;
                } else if (r2 == r1 + 1 && c1 == c2) {
                    // Down wall removed
                    grid[r1][c1] |= 2;
                }
            }
        }
    }

    void printMaze() {
        // Top border
        for (int c = 0; c < width; c++) cout << "+---";
        cout << "+" << endl;

        for (int r = 0; r < height; r++) {
            // Left border of the row
            cout << "|";
            for (int c = 0; c < width; c++) {
                // If there is a connection to the right (bit 1 is set), print "   ", else "   |"
                // We need to check our grid or check connectivity
                // For simplicity in this template, let's assume 'grid' is updated correctly
                
                // Print cell space
                cout << "   ";
                
                // Check right wall
                if (c < width - 1 && (grid[r][c] & 1)) {
                    cout << " "; // No wall
                } else {
                    cout << "|"; // Wall
            }
            }
            cout << endl;

            // Bottom border of the row
            cout << "+";
            for (int c = 0; c < width; c++) {
                
                if (r < height - 1 && (grid[r][c] & 2)) {
                    cout << "   +"; // No wall
                } else {
                    cout << "---+"; // Wall
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int width = 10;
    int height = 10;

    cout << "Generating " << width << "x" << height << " maze..." << endl;
    
    MazeGenerator maze(width, height);
    maze.generate();
    maze.printMaze();

    return 0;
}
