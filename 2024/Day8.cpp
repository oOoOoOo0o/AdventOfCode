#include <fstream>
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

void findAntinodesPart1(char&, const pos&, unordered_map<char, vector<pos>>&, const int&, const int&, unordered_map<pos, int>&);
void findAntinodesPart2(char&, const pos&, unordered_map<char, vector<pos>>&, const int&, const int&, unordered_map<pos, int>&);

int main() {
  auto start = chrono::high_resolution_clock::now();

  ifstream Input("2024/Day8Input.txt");
  string line;

  vector<string> map;

  while (getline(Input, line)) {
    map.push_back(line);
  }

  int width = map[0].size();
  int height = map.size();

  unordered_map<char, vector<pos>> antennae;
  unordered_map<pos, int> antinodes;

  // Part 1

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (map[i][j] != '.') {
        pos p = {j, i};
        findAntinodesPart1(map[i][j], p, antennae, width, height, antinodes);
        antennae[map[i][j]].push_back(p);
      }
    }
  }

  cout << antinodes.size() << endl;

  // Part 2

  antennae.clear();
  antinodes.clear();

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (map[i][j] != '.') {
        pos p = {j, i};
        findAntinodesPart2(map[i][j], p, antennae, width, height, antinodes);
        antennae[map[i][j]].push_back(p);
      }
    }
  }

  cout << antinodes.size() << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}

void findAntinodesPart1(char &c, const pos &cPos, unordered_map<char, vector<pos>> &map, const int& width, const int& height, unordered_map<pos, int>& antinodes) {
  if (map.count(c) > 0) {
    vector<pos> frequencies = map.at(c);
    for (pos p : frequencies) {
      int xDist = cPos.x - p.x;
      int yDist = cPos.y - p.y;

      int a = cPos.x + xDist;
      int b = cPos.y + yDist;
      if (a >= 0 && a < width && b >=0 && b < height) {
        pos newPos = {a, b};
        antinodes[newPos] = 1;
      }

      a = p.x - xDist;
      b = p.y - yDist;
      if (a >= 0 && a < width && b >= 0 && b < height) {
        pos newPos = {a, b};
        antinodes[newPos] = 1;
      }
    }
  }
}

void findAntinodesPart2(char &c, const pos &cPos, unordered_map<char, vector<pos>> &map, const int& width, const int& height, unordered_map<pos, int>& antinodes) {
  if (map.count(c) > 0) {
    vector<pos> frequencies = map.at(c);
    for (pos p : frequencies) {
      int xDist = cPos.x - p.x;
      int yDist = cPos.y - p.y;

      int a = cPos.x;
      int b = cPos.y;
      while (a >= 0 && a < width && b >=0 && b < height) {
        pos newPos = {a, b};
        antinodes[newPos] = 1;
        a += xDist;
        b += yDist;
      }

      a = p.x;
      b = p.y;
      while (a >= 0 && a < width && b >= 0 && b < height) {
        pos newPos = {a, b};
        antinodes[newPos] = 1;
        a -= xDist;
        b -= yDist;
      }
    }
  }
}