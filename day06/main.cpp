#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>

using namespace std;
vector<string> split_input_line(string line, string delim);

int part1();
int part2();

int part1(){
    // Time:        50     74     86     85
    // Distance:   242   1017   1691   1252
    string filename = "inputs.txt";

    fstream input_file;
    input_file.open(filename, ios::in);

    // Read all lines to get the file length
    vector<string> lines;
    string line;
    while (getline(input_file, line)) {
        lines.push_back(line);
    }  
    input_file.close();
    regex re("/  +/g");

    vector<string> time = split_input_line(regex_replace(lines[0], re, " "), " ");
    vector<string> distance = split_input_line(regex_replace(lines[1], re, " "), " ");

    int total = 1;
    // MAKE A VECTOR OF TIMES 
    // DISTANCE = (I - MAX_TIME) * I 
    for (int i = 0; i < time.size(); i++){

        std::cout << time[i] << "\n";
        int max_time = stoi(time[i]);
        int max_distance = stoi(distance[i]);

        //vector<int> boats(max_time);
        int winning_boats = 0;

        // could do it a neat way where the first time you reach > max distance you break and go up to max distance and scan down 
        // then find n diff between min and max crossing points
        for (int j = 1; j <= max_time; j++ ){
            //std::cout << "    i is " << i << " j is " << j << " max distance was " << max_distance << " travelled distance is " <<  (max_time - j) * j << " \n";
            if (((max_time - j) * j) > max_distance){ 
                winning_boats++;
            }
        }
        std::cout << "#Winning boats = " << winning_boats << "\n";
        total = total * winning_boats;
    }

    std::cout << "Total Number = " << total << "\n";
    return 0;
}

int part2(){

    string filename = "inputs_2.txt";

    fstream input_file;
    input_file.open(filename, ios::in);

    // Read all lines to get the file length
    vector<string> lines;
    string line;
    while (getline(input_file, line)) {
        lines.push_back(line);
    }  
    input_file.close();

    vector<string> time;
    time.push_back(lines[0]);
    vector<string> distance;
    distance.push_back(lines[1]);

    int total = 1;
    
    long max_time = stol(time[0]);
    long max_distance = stol(distance[0]);

    //vector<int> boats(max_time);
    long winning_boats = 0;

    for (long i = 1; i <= max_time; i++ ){
        if (((max_time - i) * i) > max_distance){
            winning_boats++;
        }
    }
    std::cout << "#Winning boats = " << winning_boats << "\n";
    total = total * winning_boats;


    std::cout << "Total Number = " << total << "\n";
    return 0;

}

int main() {
    part1();
    //part2();

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
