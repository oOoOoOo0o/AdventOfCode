#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>

using namespace std;

struct pos {
  int x, y;
  pos() = default;
  bool operator==(const pos& other) const {
    return x == other.x && y == other.y;
  }
};

namespace std {
  template <>
  struct hash<pos> {
    size_t operator()(const pos& p) const {
      return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
    }
  };
}

void addRegion(pos p, int&, int&, char, unordered_map<pos, bool>&, vector<string>&);
void addRegion2(pos p, int&, int&, char, unordered_map<pos, bool>&, vector<string>&);

int main() {
  auto start = chrono::high_resolution_clock::now();

  ifstream Input("2024/Day12Input.txt");
  string line;
  vector<string> map;

  while (getline(Input, line)) {
    map.push_back(line);
  }

  unordered_map<pos, bool> seen;
  int price = 0;

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      pos p = {i, j};
      if (!seen[p]) {
        int area = 0;
        int perimeter = 0;
        char symbol = map[i][j];
        addRegion(p, area, perimeter, symbol, seen, map);
        price += area * perimeter;
      }
    }
  }

  cout << price << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}

void addRegion(pos p, int& area, int& perimeter, char symbol, unordered_map<pos, bool>& seen, vector<string>& map) {
  if (seen[p]) return;
  area++;
  seen[p] = true;

  // Calculate perimeter
  if (p.x > 0) { // Up
    if (map[p.x-1][p.y] != symbol) {
      perimeter++;
    } else {
      pos newPos = {p.x-1, p.y};
      addRegion(newPos, area, perimeter, symbol, seen, map);
    }
  } else {
    perimeter++; // Add boundary if at an extreme
  }

  if (p.x < map.size()-1) { // Down
    if (map[p.x+1][p.y] != symbol) {
      perimeter++;
    } else {
      pos newPos = {p.x+1, p.y};
      addRegion(newPos, area, perimeter, symbol, seen, map);
    }
  } else {
    perimeter++;
  }

  if (p.y > 0) { // Left
    if (map[p.x][p.y-1] != symbol) {
      perimeter++;
    } else {
      pos newPos = {p.x, p.y-1};
      addRegion(newPos, area, perimeter, symbol, seen, map);
    }
  } else {
    perimeter++;
  }

  if (p.y < map[0].size()-1) { // Right
    if (map[p.x][p.y+1] != symbol) {
      perimeter++;
    } else {
      pos newPos = {p.x, p.y+1};
      addRegion(newPos, area, perimeter, symbol, seen, map);
    }
  } else {
    perimeter++;
  }
}