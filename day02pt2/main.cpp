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
      //logging std::cout << "    \n"; 
      //logging std::cout << "line == " << line << "\n";

      vector<string> input_line = split_input_line(line, ":");

      int game_num = std::stoi(input_line[0].erase(0,4));
      int max_red = 1;
      int max_green = 1;
      int max_blue = 1;

      vector<string> game = split_input_line(input_line[1], ";");
      
      for (int i = 0; i < game.size(); i++){
        //logging std::cout << "  game[" << i << "] == '" << game[i] << "'\n";
        vector<string> set = split_input_line(game[i], ",");
        map<string, int> colour_and_count; // string to int here

        for (int j=0; j < set.size(); j++){
          set[j].erase(0, 1);
          //logging std::cout << "    set [" << j << "] == '" << set[j] << "'\n";
          vector<string> cubes = split_input_line(set[j], " ");
          //colour_and_count.insert({ cubes[0], cubes[1] });  // set cubes[1] to be an int
          colour_and_count[cubes[1]] = std::stoi(cubes[0]); // Use color as key and convert count to int

          //logging std::cout << "          cubes 0 = " << cubes[0] << " cubes 1 = " << cubes[1] << "\n";
        }

        // Condition is that the bag only has 12 red cubes, 13 green cubes, and 14 blue cubes
        // can see if game is possible from these numbers
        // add up the IDs of the games that would have been possible
        //logging std::cout << "        map size = " << colour_and_count.size() << "\n";
        for(auto it = colour_and_count.cbegin(); it != colour_and_count.cend(); ++it){
          //logging std::cout << "      '" << it->first << "' = '" << it->second << "'\n";

          if (it->first == "red"){
            if (it->second > max_red){
              max_red = it->second;
              //logging std::cout << "        found new max red \n";

            }
          }
          if (it->first == "green"){
            if (it->second > max_green){
              //logging std::cout << "        found new max green \n";
              max_green = it->second;
            }
          }
          if (it->first == "blue"){
            if (it->second > max_blue){
              //logging std::cout << "        found new max blue \n";
              max_blue = it->second;
            }
          }
        }
        colour_and_count.clear();
      }

      //logging std::cout << line << "\n";
      //logging std::cout << "Max Red = " << max_red << " - Max Green " << max_green << " - Max Blue " << max_blue << "\n";
      int cubed = max_red * max_green * max_blue;
      //logging std::cout << cubed << "\n";
      //std::cout << "cubed = " << cubed << "\n";
      running_total += cubed;
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