#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

string replaceStringWithNum(string line);

int main(){

  std::cout << "Opening file... \n";

  fstream input_file;
  input_file.open("inputs.txt", ios::in);

  int running_total = 0;

  if (input_file.is_open()){
    string line;

    while (getline(input_file, line)){
      string firstChar;
      bool firstFound = false;
      string lastChar;
      bool lastFound = false;

      // replace the text with digits then continue
      line = replaceStringWithNum(line);

      for (int i = 0; i < line.length(); i++){
        if (!firstFound){
          if (isdigit(line[i])){
            firstChar = line[i];
            firstFound = true;
          }
        }
      }

      for (int i = line.length() - 1; i >= 0; i--){
        if (!lastFound){
          if (isdigit(line[i])){
            lastChar = line[i];
            lastFound = true;
          }
        }
      }

      string resulting_string = firstChar + lastChar;
      int resulting_num = std::stoi(resulting_string);
      running_total += resulting_num;
    }
  }
  std::cout << "Final result == " << running_total << "\n";
  return 0;
}

string replaceStringWithNum(string line)
{
  // replace the text with digits 
  // keep the start and end of the digit string
  // which could be used subsequently to find digits with
  map<string, string> number_map;
  number_map["one"] = "o1e";
  number_map["two"] = "t2o";
  number_map["three"] = "th3ee";
  number_map["four"] = "f4ur";
  number_map["five"] = "f5ve";
  number_map["six"] = "s6x";
  number_map["seven"] = "s7ven";
  number_map["eight"] = "e8ght";
  number_map["nine"] = "n9e";

  for (auto const &num : number_map){
    std::size_t found = line.find(num.first);
    while (found != std::string::npos) {
      line.replace(found, num.first.length(), num.second);
      found = line.find(num.first, found + num.second.length());
    }
  }

  return line;
}
