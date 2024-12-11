#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <cmath>

using namespace std;

void changeStones(unordered_map<unsigned long long, unsigned long long> &);
int countDigits(unsigned long long n);

int main() {
  auto start = chrono::high_resolution_clock::now();

  ifstream Input("2024/Day11Input.txt");

  string line;
  unordered_map<unsigned long long, unsigned long long> stones;
  getline(Input, line);

  istringstream iss(line);
  unsigned long long x;
  while (iss >> x) {
    stones[x] = 1;
  }

  // unsigned long long blinks = 25; // part 1
  unsigned long long blinks = 75; // part 2

  for (int i = 0; i < blinks; i++) {
    changeStones(stones);
  }

  unsigned long long total = 0;
  for (pair kv : stones) {
    total += kv.second;
  }

  cout << total << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}

void changeStones(unordered_map<unsigned long long, unsigned long long> &stones) {
  vector<pair<unsigned long long, unsigned long long>> stonesKvs;
  stonesKvs.reserve(stones.size());
  for (pair kv : stones) {
    stonesKvs.emplace_back(kv);
  }

  for (int i = 0; i < stonesKvs.size(); i++) {
    unsigned long long num = stonesKvs[i].first;
    unsigned long long count = stonesKvs[i].second;
    if (num == 0) {
      stones[num] -= count;
      stones[1] += count;
    } else if (countDigits(num) % 2 == 0) {
      unsigned long long divisor = pow(10, countDigits(num) / 2);
      unsigned long long num1 = num / divisor;
      unsigned long long num2 = num % divisor;

      stones[num] -= count;
      stones[num1] += count;
      stones[num2] += count;
    } else {
      stones[num] -= count;
      num *= 2024;
      stones[num] += count;
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