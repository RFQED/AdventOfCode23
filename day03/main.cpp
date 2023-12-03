#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

std::vector< std::vector<char> > square_matrix( std::size_t m ){
   return std::vector< std::vector<char> >( m, std::vector<char>(m) ) ;
}

bool is_digit(char x);
bool is_symbol(char x);


using namespace std;

int main(){
  std::cout << "Opening file... \n";
  
  int x_length = 0;
  int y_length = 0;

  fstream input_file;
  input_file.open("inputs.txt", ios::in);

  string line_in_loop;

  while (getline(input_file, line_in_loop)){
    ++y_length;
  }
  // closing file as i dont want to run into problems with being at the end of the file and not knowing
  input_file.close();

  string line_find_length;
  input_file.open("inputs.txt", ios::in);
  getline(input_file, line_find_length); 
  x_length = line_find_length.length();
  input_file.close();

  std::cout << "x axis length " << x_length << "\n";
  std::cout << "y axis length " << y_length << "\n";

  auto A = square_matrix(x_length);

  int running_total = 0;

  input_file.open("inputs.txt", ios::in);
  if (input_file.is_open()){
    string line;
    int row_num = 0;
    while (getline(input_file, line)){
      //std::cout << "line == " << line << "\n";
      for(int i=0; i<x_length; i++){
        A[row_num][i] = line[i];
      }
    row_num++;
   }

   // std::cout << "Final result == " << running_total << "\n";
  }

  bool num_found = false;
  char sec_val;
  char thrd_val;
  for(int i = 0 ; i < x_length ; ++i ){
    for( int j = 0 ; j < y_length; ++j ){


      std::cout << A[i][j];
      int val = A[i][j];

      if (is_digit(val)){
        num_found = true;

        sec_val = A[i+1][j];
        thrd_val = A[i+2][j];
      }

      if (num_found){


      }



      num_found = false;
    }
    std::cout << "\n";
  }

    return 0;
}

bool is_digit(char x){
  if ((x > 48) && (x < 58)){
    return true;
  }
  else{
    return false;
  }
}

bool is_symbol(char x){
  if (x == 46){
    return false;
  }
  else if((x > 48) && (x < 58)){
    return false;
  }
  else{
    return true;
  }
}