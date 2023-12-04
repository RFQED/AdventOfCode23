#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <math.h>

using namespace std;

vector<string> split_input_line(string line, string delim);
void replace_all(std::string& s, std::string const& toReplace, std::string const& replaceWith);
int part1();
int part2();


int main(){
  //part1();
  part2();
}


int part1(){
  std::cout << "Opening file... \n";
  
  string filename = "inputs.txt";
  int running_total = 0;

  // Card   1: 13  4 61 82 80 41 31 53 50  2 | 38 89 26 79 94 50  2 74 31 92 80 41 13 97 61 82 68 45 64 39  4 53 90 84 54

  fstream input_file;
  input_file.open(filename, ios::in);
  if (input_file.is_open()){
    string line;
    int row_num = 0;
    while (getline(input_file, line)){
      replace_all(line, "  ", " ");

      vector<string> card = split_input_line(line, ":");
      vector<string> numbers = split_input_line(card[1], "|");
      vector<string> winning_numbers = split_input_line(numbers[0].erase(0, 1), " ");
      vector<string> card_numbers = split_input_line(numbers[1].erase(0, 1), " ");
      // removing the first char as its a space which gets split into a number to compare.

      int matches_per_card = 0;

      for (auto & winning_num : winning_numbers){
        for (auto & card_num : card_numbers){
          if (winning_num == card_num){
            matches_per_card++;
            //std::cout << "Found a matching pair " << winning_num << " and " << card_num << "\n";  
          }
        }
      }
      int points = pow(2, matches_per_card-1);
      running_total = running_total + points;
   }
  }

  std::cout << " Final sum is " << running_total << "\n";
  return 0;
}


int part2(){
  std::cout << "Opening file... \n";
  
  string filename = "inputs.txt";
  int running_total = 0;

  // Card   1: 13  4 61 82 80 41 31 53 50  2 | 38 89 26 79 94 50  2 74 31 92 80 41 13 97 61 82 68 45 64 39  4 53 90 84 54

  fstream input_file;
  input_file.open(filename, ios::in);
  if (input_file.is_open()){
    string line;
    int row_num = 0;
    while (getline(input_file, line)){
      replace_all(line, "  ", " ");

      vector<string> card = split_input_line(line, ":");
      vector<string> numbers = split_input_line(card[1], "|");
      vector<string> winning_numbers = split_input_line(numbers[0].erase(0, 1), " ");
      vector<string> card_numbers = split_input_line(numbers[1].erase(0, 1), " ");
      // removing the first char as its a space which gets split into a number to compare.

      int matches_per_card = 0;

      for (auto & winning_num : winning_numbers){
        for (auto & card_num : card_numbers){
          if (winning_num == card_num){
            matches_per_card++;
            //std::cout << "Found a matching pair " << winning_num << " and " << card_num << "\n";  
          }
        }
      }
      int points = pow(2, matches_per_card-1);
      running_total = running_total + points;
   }
  }

  std::cout << " Final sum is " << running_total << "\n";
  return 0;
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


void replace_all(std::string& s, std::string const& toReplace, std::string const& replaceWith) {
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    s.swap(buf);
}