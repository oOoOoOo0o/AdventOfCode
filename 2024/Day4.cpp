#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main() {
  auto start = chrono::high_resolution_clock::now();

  ifstream Input("2024/Day4Input.txt");
  string line;
  vector<string> rows;

  while (getline(Input, line)) {
    rows.push_back(line);
  }

  // Part 1 (awful)

  int count = 0;

  // Search horizontally
  for (string row: rows) {
    for (int i = 0; i < (row.size() - 3); i++) {
      if (row[i] == 'X' &&
          row[i + 1] == 'M' &&
          row[i + 2] == 'A' &&
          row[i + 3] == 'S') {
        count++;
      } else if (row[i] == 'S' &&
                 row[i + 1] == 'A' &&
                 row[i + 2] == 'M' &&
                 row[i + 3] == 'X') {
        count++;
      }
    }
  }

  // Search vertically
  int length = rows[0].length();

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < (length - 3); j++) {
      if (rows[j][i] == 'X' &&
          rows[j + 1][i] == 'M' &&
          rows[j + 2][i] == 'A' &&
          rows[j + 3][i] == 'S') {
        count++;
      } else if (rows[j][i] == 'S' &&
                 rows[j + 1][i] == 'A' &&
                 rows[j + 2][i] == 'M' &&
                 rows[j + 3][i] == 'X') {
        count++;
      }
    }
  }

  // Search diagonally
  for (int i = 0; i < (length - 3); i++) {
    for (int j = 0; j < (length - 3); j++) {
      if (rows[j][i] == 'X' &&
          rows[j + 1][i + 1] == 'M' &&
          rows[j + 2][i + 2] == 'A' &&
          rows[j + 3][i + 3] == 'S') {
        count++;
      } else if (rows[j][i] == 'S' &&
                 rows[j + 1][i + 1] == 'A' &&
                 rows[j + 2][i + 2] == 'M' &&
                 rows[j + 3][i + 3] == 'X') {
        count++;
      }
      if (rows[j + 3][i] == 'X' &&
          rows[j + 2][i + 1] == 'M' &&
          rows[j + 1][i + 2] == 'A' &&
          rows[j][i + 3] == 'S') {
        count++;
      } else if (rows[j + 3][i] == 'S' &&
                 rows[j + 2][i + 1] == 'A' &&
                 rows[j + 1][i + 2] == 'M' &&
                 rows[j][i + 3] == 'X') {
        count++;
      }
    }
  }

  cout << count << endl;

  // Part 2 (nice!)

  count = 0;

  for (int i = 0; i < (length - 2); i++) {
    for (int j = 0; j < (length - 2); j++) {
      string s1({rows[i][j], rows[i+1][j+1], rows[i+2][j+2]});
      string s2({rows[i][j+2], rows[i+1][j+1], rows[i+2][j]});

      if ((s1 == "MAS" || s1 == "SAM") && (s2 == "MAS" || s2 == "SAM")) {
        count++;
      }
    }
  }

  cout << count << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}
