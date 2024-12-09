#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

unsigned long long part1(string&);
unsigned long long part2(string&);

int main() {
  auto start = chrono::high_resolution_clock::now();

  ifstream Input("2024/Day9Input.txt");

  string line;
  getline(Input, line);

  cout << part1(line) << endl;

  cout << part2(line) << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}

unsigned long long part1(string &line) {
  bool isFile = true;
  vector<int> ids;
  int id = 0;

  for (int i = 0; i < line.size(); i++) {
    int count = line[i] - '0';
    if (isFile) {
      for (int j = 0; j < count; j++) {
        ids.push_back(id);
      }
      id++;
    } else {
      for (int j = 0; j < count; j++) {
        ids.push_back(-1);
      }
    }
    isFile = !isFile;
  }

  int j = ids.size() - 1;
  int i = 0;
  while (i < j) {
    if (ids[i] == -1) {
      while (ids[j] == -1) {
        j--;
      }
      ids[i] = ids[j];
      ids[j] = -1;
      j--;
    }
    i++;
  }

  unsigned long long total = 0;
  for (int i = 0; i < ids.size() && ids[i] != -1; i++) {
    total += ids[i] * i;
  }

  return total;
}

unsigned long long part2(string &line) {
  bool isFile = true;
  vector<int> ids;
  int id = 0;

  for (int i = 0; i < line.size(); i++) {
    int count = line[i] - '0';
    if (isFile) {
      for (int j = 0; j < count; j++) {
        ids.push_back(id);
      }
      id++;
    } else {
      for (int j = 0; j < count; j++) {
        ids.push_back(-1);
      }
    }
    isFile = !isFile;
  }

  for (int i = ids.size() - 1; i > 0;) {
    while (ids[i] == -1) {
      i--;
    }
    int num = ids[i];
    int numCount = 0;
    while (ids[i] == num) {
      numCount++;
      i--;
    }

    int j = 0;
    int freeSpace = 0;
    int k = 0;
    while (numCount > freeSpace && j < i) {
      freeSpace = 0;
      while (ids[j] != -1 && j < i) {
        j++;
      }
      k = j;
      while (ids[j] == -1) {
        freeSpace++;
        j++;
      }
    }

    if (numCount <= freeSpace) {
      for (int l = 0; l < numCount; l++) {
        ids[k] = num;
        k++;
        ids[i+l+1] = -1;
      }
    }
  }

  unsigned long long total = 0;
  for (int i = 0; i < ids.size(); i++) {
    if (ids[i] == -1) continue;
    total += ids[i] * i;
  }

  return total;
}