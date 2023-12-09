#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


using namespace std;
vector<string> split_input_line(string line, string delim);


int part1();
int part2();

int part1(){
    // LLR

    // AAA = (BBB, BBB)
    // BBB = (AAA, ZZZ)
    // ZZZ = (ZZZ, ZZZ)

    //   think a map of pairs is the best data type

    map<string, pair<string, string>> maze;

    string filename = "inputs.txt";

    fstream input_file;
    input_file.open(filename, ios::in);

    int line_num = 0;
    string line;
    vector<string> l;
    vector<string> vals;
    string map = "";

    while (std::getline(input_file, line)) {
        if (line_num == 0) {
            map = line;
            line_num++;
            continue;
        }
        if (line_num == 1){
            line_num++;
            continue;
        }

        l = split_input_line(line, " = ");
        string index = l[0];
        string values = l[1].erase(0,1).erase(l[1].size()-1,1);
        vals = split_input_line(values, ", ");
        maze[index] = std::make_pair(vals[0], vals[1]);

        line_num++;
    }
    input_file.close();

    pair<string, string> next_step = maze.find("AAA")->second;
    bool continue_loop = true;
    int step_count = 0;
    while(continue_loop){
        for (int i = 0; i < map.length(); i++){
            //std::cout << " on the " << i << "th element of " << map.length() << "\n"; 
            char direction = map[i]; 
            //std::cout << "Going " << map[i] << "\n";
            string next = "";

            if (direction == 'L'){
                next = next_step.first;
            }
            if (direction == 'R'){
                next = next_step.second;
            }
            //std::cout << " next step is " << next << "\n";
            next_step = maze.find(next)->second;
            //std::cout << " this results in " << next_step.first << " " << next_step.second << "\n";
            step_count++;
            if (next == "ZZZ"){
                std::cout << "Reached ZZZ! \n";
                continue_loop = false;
                break; 
            } 
        }
    }
    std::cout << "step count == " << step_count << "\n";


    return 0;
}



int part2(){
    // i think we have to follow every thread until we step to zzz at the same time for each thread
    // assuming this is possible we can solve each maze and use the 
    // path length for each maze to work out when they'll all reach the end at hte same time, stepping forward by 
    // the path length for each until we hit a common value rather than endless maze solve.
    // So -> solve path for each of the different threads 
    // count, n, the required steps for each thread
    // find the lowest common multiple of n?


    // LLR

    // AAA = (BBB, BBB)
    // BBB = (AAA, ZZZ)
    // ZZZ = (ZZZ, ZZZ)

    //   think a map of pairs is the best data type

    map<string, pair<string, string>> maze;

    string filename = "inputs.txt";

    fstream input_file;
    input_file.open(filename, ios::in);

    int line_num = 0;
    string line;
    vector<string> l;
    vector<string> vals;
    string map = "";
    
    vector<string> starting_point;

    while (std::getline(input_file, line)) {
        if (line_num == 0) {
            map = line;
            line_num++;
            continue;
        }
        if (line_num == 1){
            line_num++;
            continue;
        }

        l = split_input_line(line, " = ");
        string index = l[0];
        string values = l[1].erase(0,1).erase(l[1].size()-1,1);
        if (index[2] == 'A'){
            starting_point.push_back(index);
        }
        
        vals = split_input_line(values, ", ");
        maze[index] = std::make_pair(vals[0], vals[1]);

        line_num++;
    }

    std::cout << "number of starting points = " << starting_point.size() << "\n";

    input_file.close();

    for (int i = 0; i < starting_point.size(); i++){
        pair<string, string> next_step = maze.find(starting_point[i])->second;
        std::cout << "starting at " << starting_point[i] << "\n";
        bool continue_loop = true;
        int step_count = 0;
        while(continue_loop){
            for (int j = 0; j < map.length(); j++){
                char direction = map[j]; 
                string next = "";

                //std::cout << " now on " << next_step.first << " " << next_step.second << "\n";

                if (direction == 'L'){
                    next = next_step.first;
                }
                if (direction == 'R'){
                    next = next_step.second;
                }
                next_step = maze.find(next)->second;
                //std::cout << " this results in " << next_step.first << " " << next_step.second << "\n";
                step_count++;

                if (next[2] == 'Z'){
                    std::cout << "Reached Z! \n";
                    continue_loop = false;
                    break; 
                } 
            }
            //cin.get(); // debug 
        }
        std::cout << "Starting Point " << i << " has a step count == " << step_count << "\n";

    }

    return 0;
}

int main() {
    //part1();
    part2();
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