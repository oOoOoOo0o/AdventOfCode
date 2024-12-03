#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <regex>

using namespace std;

int main() {
  auto start = chrono::high_resolution_clock::now();

  // Part 1

  ifstream Input("2024/Day3Input.txt");
  string line;

  int total = 0;

  while (getline(Input, line)) {
    // Regex for mul(x,y) where x and y are ints between 0 and 999 inclusive
    regex reg(R"(mul\((\d{1,3}),(\d{1,3})\))");
    smatch matches;

    while (regex_search(line, matches, reg)) {
      int a = stoi(matches[1]);
      int b = stoi(matches[2]);
      total += a * b;
      line = matches.suffix().str();
    }
  }
  Input.close();

  cout << total << endl;

  // Part 2

  Input.open("2024/Day3Input.txt");

  total = 0;
  string fileString;

  while (getline(Input, line)) {
    fileString += line;
  }
  Input.close();

  // Regex for mul(x,y) where x and y are ints between 0 and 999 inclusive
  regex regDo(R"(do\(\))");
  regex regDont(R"(don't\(\))");
  regex reg(R"(mul\((\d{1,3}),(\d{1,3})\))");
  smatch matches;

  while (regex_search(fileString, matches, regDont)) {
    string prefix = matches.prefix().str();
    fileString = matches.suffix().str();
    while (regex_search(prefix, matches, reg)) {
      int a = stoi(matches[1]);
      int b = stoi(matches[2]);
      total += a * b;
      prefix = matches.suffix().str();
    }

    regex_search(fileString, matches, regDo);
    fileString = matches.suffix().str();
  }

  while (regex_search(fileString, matches, reg)) {
    int a = stoi(matches[1]);
    int b = stoi(matches[2]);
    total += a * b;
    fileString = matches.suffix().str();
  }

  cout << total << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}
