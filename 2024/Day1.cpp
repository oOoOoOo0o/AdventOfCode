#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
  ifstream Input("2024/Day1Input.txt");
  string line;

  vector<int> list1;
  vector<int> list2;

  while (getline(Input, line)) {
    string number = line.substr(0, line.find(' '));
    int x = stoi(number);
    list1.push_back(x);

    number = line.substr(line.find(' ') + 3);
    x = stoi(number);
    list2.push_back(x);
  }

  Input.close();

  sort(list1.begin(), list1.end());
  sort(list2.begin(), list2.end());

  // Part 1
  int totalDistance = 0;

  for (int i = 0; i < list1.size(); i++) {
    totalDistance += abs(list1.at(i) - list2.at(i));
  }

  cout << totalDistance << endl;

  // Part 2
  int similarityScore = 0;
  int j = 0;
  int count = 0;

  for (int i = 0; i < list1.size() && j < list2.size(); i++) {
    if (i == 0 || list1.at(i) != list1.at(i - 1)) {
      count = 0;
    }

    while (j < list2.size() && list2.at(j) < list1.at(i)) {
      j++;
    }

    while (j < list2.size() && list2.at(j) == list1.at(i)) {
      count++;
      j++;
    }

    similarityScore += list1.at(i) * count;
  }

  cout << similarityScore << endl;
}
