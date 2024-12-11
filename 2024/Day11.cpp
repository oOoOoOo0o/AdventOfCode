#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

void changeStones(vector<unsigned long long> &stones);
int countDigits(unsigned long long n);

int main() {
  auto start = chrono::high_resolution_clock::now();

  ifstream Input("2024/Day11Input.txt");

  string line;
  vector<unsigned long long> stones;
  getline(Input, line);

  istringstream iss(line);
  unsigned long long x;
  while (iss >> x) {
    stones.push_back(x);
  }

  unsigned long long blinks = 25; // use 75 blinks for part 2

  for (int i = 0; i < blinks; i++) {
    changeStones(stones);
  }

  cout << stones.size() << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}

void changeStones(vector<unsigned long long> &stones) {
  for (int i = 0; i < stones.size(); i++) {
    unsigned long long num = stones[i];
    if (num == 0) {
      stones[i] = 1;
    } else if (countDigits(num) % 2 == 0) {
      unsigned long long divisor = pow(10, countDigits(num) / 2);
      unsigned long long num1 = num / divisor;
      unsigned long long num2 = num % divisor;
      stones[i] = num1;
      stones.insert(stones.begin() + i + 1, num2);
      i++;
    } else {
      stones[i] = num * 2024;
    }
  }
}

int countDigits(unsigned long long n) {
  int count = 0;

  if (n < 10) {
    return 1;
  }

  while (n != 0) {
    n /= 10;
    count++;
  }

  return count;
}