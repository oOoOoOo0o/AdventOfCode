#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

bool isSafe(vector<int>& nums);

int main() {
  auto start = chrono::high_resolution_clock::now();

  // Part 1

  ifstream Input("2024/Day2Input.txt");
  string line;

  int safeReports = 0;

  while (getline(Input, line)) {
    // Parse ints in line
    istringstream iss(line);
    int x;
    vector<int> nums;

    while (iss >> x) {
      nums.push_back(x);
    }

    if (isSafe(nums)) {
      safeReports++;
    }
  }
  Input.close();

  cout << "Part 1: " << safeReports << endl;

  // Part 2

  Input.open("2024/Day2Input.txt");

  safeReports = 0;

  while (getline(Input, line)) {
    istringstream iss(line);
    int x;
    vector<int> nums;

    while (iss >> x) {
      nums.push_back(x);
    }

    for(int i = 0; i < nums.size(); i++) {
      std::vector<int> tempNums = nums;
      tempNums.erase(tempNums.begin() + i);

      if(isSafe(tempNums)) {
        safeReports++;
        break;
      }
    }
  }

  cout << "Part 2: " << safeReports << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}

bool isSafe(vector<int>& nums) {
  bool increasing = nums[0] < nums[1];
  bool isSafe = true;

  for (int i = 1; i < nums.size(); i++) {
    if ((nums[i - 1] < nums[i]) != increasing) {
      isSafe = false;
      break;
    }

    int diff = abs(nums[i] - nums[i - 1]);
    if (diff > 3 || diff == 0) {
      isSafe = false;
      break;
    }
  }

  return isSafe;
}