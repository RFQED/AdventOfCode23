#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<string> split_input_line(string line, string delim);

int main(){

  std::cout << "Opening file... \n";

  fstream input_file;
  input_file.open("inputs.txt", ios::in);

  int running_total = 0;

  if (input_file.is_open()){
    string line;

    while (getline(input_file, line)){
      std::cout << "line == " << line << "\n";

      vector<string> input_line = split_input_line(line, ":");
      vector<string> game = split_input_line(input_line[1], ";");
      
      
      for (int i = 0; i < game.size(); i++){
        std::cout << "game[" << i << "] == '" << game[i] << "'\n";

        vector<string> set = split_input_line(game[i], ",");
        map<string, string> colour_and_count;

        for (int j=0; j < set.size(); j++){
          std::cout << "set [" << j << "] == '" << set[j].erase(0, 1) << "'\n";
          vector<string> cubes = split_input_line(set[j], " ");

          colour_and_count.insert({ cubes[0], cubes[1] }); 
        }

        for(auto it = colour_and_count.cbegin(); it != colour_and_count.cend(); ++it)
        {
            std::cout << " '" << it->first << "' = '" << it->second << "'\n";
        }

      }
    }
  }
  std::cout << "Final result == " << running_total << "\n";
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


bool check_if_colour_count_possible (string line){

return true;
}