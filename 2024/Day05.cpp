#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

unordered_map<int, vector<int>> rules;

bool isLineCorrect(vector<int>&, unordered_map<int, vector<int>>&);

bool compare(int, int);

int main() {
  auto start = chrono::high_resolution_clock::now();

  ifstream Input("2024/Day5Input.txt");
  string line;
  bool loadingRules = true;
  int total = 0;
  int totalPart2 = 0;

  while (getline(Input, line)) {
    if (line.empty()) {
      continue;
    }

    if (loadingRules && line.find('|') != string::npos) {
      int value = stoi(line.substr(0, line.find('|')));
      int key = stoi(line.substr(line.find('|') + 1));
      rules[key].push_back(value);
      continue;
    }

    loadingRules = false;

    istringstream iss(line);
    string x;
    vector<int> nums;

    while (getline(iss, x, ',')) {
      nums.push_back(stoi(x));
    }

    if (isLineCorrect(nums, rules)) {
      int index = nums.size() / 2;
      total += nums[index];
    } else {
      sort(nums.begin(), nums.end(), compare);
      int index = nums.size() / 2;
      totalPart2 += nums[index];
    }
  }

  cout << "Part 1: " << total << endl;
  cout << "Part 2: " << totalPart2 << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}

bool isLineCorrect(vector<int> &nums, unordered_map<int, vector<int>> &rules) {
  vector<int> badNums;
  for (int num : nums) {
    if (rules.count(num)) {
      badNums.insert(badNums.end(), rules[num].begin(), rules[num].end());
    }
    if (find(badNums.begin(), badNums.end(), num) != badNums.end()) {
      return false;
    }
  }

  return true;
}

bool compare(int a, int b) {
  if (rules.count(a)) {
    if (find(rules[a].begin(), rules[a].end(), b) != rules[a].end()) {
      return false;
    }
  }
  return true;
}