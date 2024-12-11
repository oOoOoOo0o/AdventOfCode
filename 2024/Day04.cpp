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

  // Part 1

  int count = 0;
  int length = rows[0].length();
  string s;

  for (int i = 0; i < (length); i++) {
    for (int j = 0; j < (length); j++) {
      // Horizontal search
      if (j < length - 3) {
        s = {rows[i][j], rows[i][j+1], rows[i][j+2], rows[i][j+3]};
        if (s == "XMAS" || s == "SAMX") {
          count++;
        }
      }

      // Vertical search
      if (i < length - 3) {
        s = {rows[i][j], rows[i+1][j], rows[i+2][j], rows[i+3][j]};
        if (s == "XMAS" || s == "SAMX") {
          count++;
        }
      }

      // Diagonal search
      if (i < length - 3 && j < length - 3) {
        s = {rows[i][j], rows[i+1][j+1], rows[i+2][j+2], rows[i+3][j+3]};
        if (s == "XMAS" || s == "SAMX") {
          count++;
        }

        s = {rows[i+3][j], rows[i+2][j+1], rows[i+1][j+2], rows[i][j+3]};
        if (s == "XMAS" || s == "SAMX") {
          count++;
        }
      }
    }
  }

  cout << count << endl;

  // Part 2

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
