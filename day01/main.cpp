#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>
#include<ctype.h>

using namespace std;

int main() {

  std::cout << "Opening file... \n";

  fstream input_file;
  input_file.open("inputs.txt", ios::in);

  int running_total = 0;
  
  if (input_file.is_open()){
    string line;

    while(getline(input_file, line)){

      std::cout << line << "\n";

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
      std::cout << "first digit found is " << firstChar << "\n";
      std::cout << "last digit found is " << lastChar << "\n";

      string resulting_number = firstChar + lastChar;
      std::cout << "resulting number = " << resulting_number << "\n"; 
      
    }

    // combine the first and last to one number
    
    
  }

  return 0;

}
