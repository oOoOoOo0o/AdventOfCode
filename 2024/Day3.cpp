#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <cmath>
#include <math.h>
#include <regex>

using namespace std;

int main() {
  auto start = chrono::high_resolution_clock::now();

  // Part 1 & 2

  ifstream Input("2024/Day3Input.txt");
  string line;

  int total1 = 0;
  int total2 = 0;
  string fileString;

  while (getline(Input, line)) {
    fileString += line;
  }
  Input.close();

  regex regDo(R"(do\(\))");
  regex regDont(R"(don't\(\))");
  regex reg(R"(mul\((\d{1,3}),(\d{1,3})\))");
  smatch matches;
  smatch tempMatch;
  string remainder;

  while (regex_search(fileString, matches, regDont)) {
    // Get from previous do to next don't
    string prefix = matches.prefix().str();
    fileString = matches.suffix().str();

    // Add all between do and don't to both totals
    while (regex_search(prefix, matches, reg)) {
      int a = stoi(matches[1]);
      int b = stoi(matches[2]);
      int c = a * b;

      total1 += c;
      total2 += c;

      prefix = matches.suffix().str();
    }

    // Get from don't to next do
    regex_search(fileString, matches, regDo);
    string prefix2 = matches.prefix().str();

    if (prefix2.empty()) {
      remainder = fileString;
    } else {
      // Add all between don't and do to total1
      while (regex_search(prefix2, tempMatch, reg)) {
        int a = stoi(tempMatch[1]);
        int b = stoi(tempMatch[2]);
        total1 += a * b;
        prefix2 = tempMatch.suffix().str();
      }
    }

    // Remove from don't to next do
    fileString = matches.suffix().str();
  }

  // Add remainder of string to total1
  while (regex_search(remainder, matches, reg)) {
    int a = stoi(matches[1]);
    int b = stoi(matches[2]);
    int c = a * b;
    total1 += c;
    remainder = matches.suffix().str();
  }

  cout << "Part 1: " << total1 << endl;
  cout << "Part 2: " << total2 << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}
