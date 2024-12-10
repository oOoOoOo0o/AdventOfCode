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

void findPaths1(vector<vector<int>>&, int, int, int, unordered_map<pos, int>&);
int findPaths2(vector<vector<int>>&, int, int, int);

int main() {
  auto start = chrono::high_resolution_clock::now();

  ifstream Input("2024/Day10Input.txt");

  string line;
  vector<vector<int>> map;
  while (getline(Input, line)) {
    vector<int> row;
    for (char c : line) {
      int i = c - '0';
      row.push_back(i);
    }
    map.push_back(row);
  }

  unordered_map<pos, int> trailEnds;
  int score1 = 0;
  int score2 = 0;

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 0) {
        findPaths1(map, i, j, 0, trailEnds);
        score1 += trailEnds.size();
        trailEnds.clear();
        score2 += findPaths2(map, i, j, 0);
      }
    }
  }

  cout << score1 << endl;
  cout << score2 << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}

void findPaths1(vector<vector<int>> &map, int i, int j, int curr, unordered_map<pos, int> &trailEnds) {
  if (i < 0 || j < 0 || i >= map.size() || j >= map[i].size()) {
    return;
  }

  if (map[i][j] != curr) {
    return;
  }

  if (curr == 9) {
    pos p = {i, j};
    trailEnds[p] = 1;
    return;
  }

  int next = curr + 1;
  findPaths1(map, i, j+1, next, trailEnds);
  findPaths1(map, i+1, j, next, trailEnds);
  findPaths1(map, i-1, j, next, trailEnds);
  findPaths1(map, i, j-1, next, trailEnds);
}

int findPaths2(vector<vector<int>> &map, int i, int j, int curr) {
  if (i < 0 || j < 0 || i >= map.size() || j >= map[i].size()) {
    return 0;
  }

  if (map[i][j] != curr) {
    return 0;
  }

  if (curr == 9) {
    return 1;
  }

  int next = curr + 1;
  return findPaths2(map, i, j+1, next) + findPaths2(map, i+1, j, next) + findPaths2(map, i-1, j, next) + findPaths2(map, i, j-1, next);
}