#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

bool move(vector<string> &, int &, int &, char &, int &, int &);

int main() {
  auto start = chrono::high_resolution_clock::now();

  ifstream Input("2024/Day6Input.txt");
  string line;
  vector<string> map;

  while (getline(Input, line)) {
    map.push_back(line);
  }

  vector<string> map2 = map;

  int xStart = 0, yStart = 0;

  for (int i = 0; i < map.size(); i++) {
    if (map[i].find('^') != string::npos) {
      xStart = i;
      yStart = map[i].find('^');
      break;
    };
  }

  int x = xStart, y = yStart;

  char dir = 'U';
  map[x][y] = 'X';

  // Part 1

  int place = 0, holder = 0;
  while (move(map, x, y, dir, place, holder)) {}

  int count = 0;
  for (string row: map) {
    for (char c: row) {
      if (c == 'X') {
        count++;
      }
    }
  }

  cout << count << endl;

  // Part 2

  int numOfLoops = 0;

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      x = xStart, y = yStart;
      map = map2;
      map[i][j] = '#';
      dir = 'U';
      int seen = 0;
      int unique = 0;
      while (move(map, x, y, dir, unique, seen)) {
        if (unique < seen) {
          numOfLoops++;
          break;
        }
      }
    }
  }

  cout << numOfLoops << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}

bool move(vector<string> &map, int &x, int &y, char &dir, int &unique, int &seen) {
  switch (dir) {
    case 'U':
      if (x - 1 < 0) {
        map[x][y] = 'X';
        return false;
      }
      if (map[x-1][y] != '#') {
        x--;
        map[x][y] == 'X' ? seen++ : unique++;
        map[x][y] = 'X';
      } else {
        dir = 'R';
        move(map, x, y, dir, unique, seen);
      }
      break;
    case 'R':
      if (y + 1 >= map[x].size()) {
        map[x][y] = 'X';
        return false;
      }
      if (map[x][y+1] != '#') {
        y++;
        map[x][y] == 'X' ? seen++ : unique++;
        map[x][y] = 'X';
      } else {
        dir = 'D';
        move(map, x, y, dir, unique, seen);
      }
      break;
    case 'D':
      if (x + 1 >= map.size()) {
        map[x][y] = 'X';
        return false;
      }
      if (map[x+1][y] != '#') {
        x++;
        map[x][y] == 'X' ? seen++ : unique++;
        map[x][y] = 'X';
      } else {
        dir = 'L';
        move(map, x, y, dir, unique, seen);
      }
      break;
    case 'L':
      if (y - 1 < 0) {
        map[x][y] = 'X';
        return false;
      }
      if (map[x][y-1] != '#') {
        y--;
        map[x][y] == 'X' ? seen++ : unique++;
        map[x][y] = 'X';
      } else {
        dir = 'U';
        move(map, x, y, dir, unique, seen);
      }
      break;
  }
  return true;
}