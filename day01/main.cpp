#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctype.h>

using namespace std;

int main() {

  std::cout << "Opening file... \n";

  fstream input_file;
  input_file.open("inputs.txt", ios::in);

  int running_total = 0;
  
  if (input_file.is_open()){
    string line;

    while(getline(input_file, line)){
      string firstChar;
      bool firstFound = false;
      string lastChar;
      bool lastFound = false;
      
      for (int i = 0; i < line.length(); i++){
	if (!firstFound){
	  if (isdigit(line[i])){
	    firstChar = line[i];
	    firstFound = true;
	  }
	}
      }

      for (int i = line.length() -1 ; i >= 0; i--){
	if (!lastFound){	
	  if (isdigit(line[i])){
	    lastChar = line[i];
	    lastFound = true;
	  }
	}
      }

      string resulting_string = firstChar + lastChar;
      int resulting_num = std::stoi(resulting_string);
      running_total+= resulting_num;
    }

  }
  std::cout << "Final result == " << running_total << "\n";
  return 0;

}
