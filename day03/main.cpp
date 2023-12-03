#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>


std::vector< std::vector<char> > square_matrix( std::size_t m ){
   return std::vector< std::vector<char> >( m, std::vector<char>(m) ) ;
}

bool is_digit(int x);
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
  bool symbol_found = false;
  int sec_val;
  bool is_sec_val;
  int thrd_val;
  bool is_thrd_val;
  int start_i;
  int end_i;
  int start_j;
  int end_j;

  // 2D Array Layout
  //  Arr[0][0]  Arr[0][1]  Arr[0][2]
  //  Arr[1][0]  Arr[1][1]  Arr[1][2]
  //  Arr[2][0]  Arr[2][1]  Arr[2][2]


  for(int i = 0 ; i < y_length ; ++i ){
    for( int j = 0 ; j < x_length; ++j ){

      //std::cout << A[i][j];
      int val = A[i][j] - '0';

      if (is_digit(val)){
        num_found = true;
        start_i = i;
        end_i = i;

        sec_val = A[i][j+1] - '0';
        if (is_digit(sec_val)){
          thrd_val = A[i][j+2] - '0';
          is_sec_val = true;
          end_j = j+1;
          if (is_digit(thrd_val)){
            end_j = j+2;
            is_thrd_val = true;
          }
        }
      }
      if (num_found){
        std::cout << "num found " << val << " is 2nd val = " << sec_val << " is 3rd val " << thrd_val << " \n ";
        // check if first row
        if (i == 0){
          std::cout << "on first row \n";
          for (int l = start_i; l < end_i+1; l++){
            std::cout << "in loop over l \n";
            for (int m = j; m < j+2; m++){
              std::cout << "in loop over m \n";

              if (is_symbol(A[l][m])){
                symbol_found = true;
                std::cout << "symbol found at l = " << l << " m = " << m << " = " << A[l][m] << "\n";
              }
            }
          }          
        }
        for (int l = start_i-1; l < end_i+1; l++){
          for (int m=j-1; m < j+2; m++){
            if (is_symbol(A[l][m])){
              symbol_found = true;
              std::cout << "symbol found at l = " << l << " m = " << m << " = " << A[l][m] << "\n";
            }
          }
        }

        if (symbol_found){
          int number;
          number = number + val; 

          if (is_sec_val) number = number + sec_val;
          if (is_thrd_val) number = number + thrd_val;

          std::cout << number << "\n";
        }
      }
      num_found = false;
    }
    std::cout << "\n";
  }
  return 0;
}

bool is_digit(int x){
  if ((x > -1) && (x < 10)){
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