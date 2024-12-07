#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

void incrementOperators(string&);
// int calculate(vector<int>&, string&);
long long concatenate(long long, int);
void incrementOperators2(string&);

int main() {
  auto start = chrono::high_resolution_clock::now();

  ifstream Input("2024/Day7Input.txt");
  string line;

  // Part 1

  long long answer = 0;

  while (getline(Input, line)) {
    long long value = stoll(line.substr(0, line.find(':')));

    string equation = line.substr(line.find(':') + 1);
    vector<int> operands;
    istringstream iss(equation);
    int x;

    while (iss >> x) {
      operands.push_back(x);
    }
    string operators(operands.size() - 1, '+');

    int iterations = pow(2, operands.size() - 1);
    for (int i = 0; i < iterations; i++) {
      long long result = operands[0];
      for (int j = 0; j < operators.size(); j++) {
        if (operators[j] == '+') {
          result += operands[j + 1];
        } else {
          result *= operands[j + 1];
        }
      }
      if (result == value) {
        answer += value;
        break;
      }
      incrementOperators(operators);
    }
  }

  cout << answer << endl;
  Input.close();

  // Part 2

  Input.open("2024/Day7Input.txt");
  answer = 0;

  while (getline(Input, line)) {
    long long value = stoll(line.substr(0, line.find(':')));

    string equation = line.substr(line.find(':') + 1);
    vector<int> operands;
    istringstream iss(equation);
    int x;

    while (iss >> x) {
      operands.push_back(x);
    }
    string operators(operands.size() - 1, '+');

    int iterations = pow(3, operands.size() - 1);
    for (int i = 0; i < iterations; i++) {
      long long result = operands[0];
      for (int j = 0; j < operators.size(); j++) {
        if (operators[j] == '+') {
          result += operands[j + 1];
        } else if (operators[j] == '*') {
          result *= operands[j + 1];
        } else {
          result = concatenate(result, operands[j + 1]);
        }
      }
      if (result == value) {
        answer += value;
        break;
      }
      incrementOperators2(operators);
    }
  }

  cout << answer << endl;

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Execution time: " << duration.count() << "ms" << endl;
}

// int calculate(vector<int>& operands, string& operators) {
//   long long result = operands[0];
//   for (int j = 0; j < operators.size(); j++) {
//     if (operators[j] == '+') {
//       result += operands[j + 1];
//     } else {
//       result *= operands[j + 1];
//     }
//   }
//   return result;
// }

void incrementOperators(string &ops) {
  for (int i = ops.size()-1; i >= 0; i--) {
    if (ops[i] == '+') {
      ops[i] = '*';
      break;
    }
    ops[i] = '+';
  }
}

long long concatenate(long long x, int y) {
  string a = to_string(x);
  string b = to_string(y);
  string c = a + b;
  return stoll(c);
}

void incrementOperators2(string &ops) {
  for (int i = ops.size()-1; i >= 0; i--) {
    if (ops[i] == '+') {
      ops[i] = '*';
      break;
    }
    if (ops[i] == '*') {
      ops[i] = '|';
      break;
    }
    ops[i] = '+';
  }
}