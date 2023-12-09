#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;
vector<string> split_input_line(string line, string delim);
vector<int> split_input_line_ints(string line, string delim);


int part1();
int part2();

int part1(){
    //   think a map of pairs is the best data type
    string filename = "inputs_2.txt";

    fstream input_file;
    input_file.open(filename, ios::in);

    int line_num = 0;
    string line;
    vector<int> original;

    long long total = 0;

    while (std::getline(input_file, line)) {
        original = split_input_line_ints(line, " ");

        std::vector<std::vector<int>> diffs;
        diffs.push_back(original);

        // Generating difference levels
        while (true) {
            std::vector<int> currentLevel = diffs.back();
            std::vector<int> nextLevel;
            bool allZeros = true;
            for (int i = 0; i < currentLevel.size() - 1; i++) {
                int diff = currentLevel[i + 1] - currentLevel[i];
                nextLevel.push_back(diff);
                if (diff != 0) allZeros = false;
            }
            diffs.push_back(nextLevel);
            if (allZeros || nextLevel.empty()) break;
        }

        // Extrapolating the next number
        for (int level = diffs.size() - 2; level >= 0; level--) {
            diffs[level].push_back(diffs[level].back() + diffs[level + 1].back());
        }

        // The next number in the original sequence
        int nextNumber = diffs[0].back();
        std::cout << "The next number in the series is: " << nextNumber << std::endl;
        cin.get();

    }

    
    input_file.close();



    return 0;
}



int part2(){

    return 0;
}

int main() {
    part1();
    //    part2();
}

vector<string> split_input_line(string line, string delim){

  vector<string> game;
  string sub_string = "";

  if (!line.empty()) {
      int start = 0;
      do {
          // Find the index of occurrence
          int idx = line.find(delim, start);
          if (idx == string::npos) {
              break;
          }
          int length = idx - start;
          game.push_back(line.substr(start, length));
          start += (length + delim.size());
      } while (true);
      game.push_back(line.substr(start));
  }
  return game;
} 

vector<int> split_input_line_ints(string line, string delim){

  vector<int> game;
  string sub_string = "";

  if (!line.empty()) {
      int start = 0;
      do {
          // Find the index of occurrence
          int idx = line.find(delim, start);
          if (idx == string::npos) {
              break;
          }
          int length = idx - start;
          game.push_back(stoi(line.substr(start, length)));
          start += (length + delim.size());
      } while (true);
      game.push_back(stoi(line.substr(start)));
  }
  return game;
} 