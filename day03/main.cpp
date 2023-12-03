#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>


std::vector< std::vector<char> > square_matrix( std::size_t m ){
   return std::vector< std::vector<char> >( m, std::vector<char>(m) ) ;
}

bool checkSurrounding(const std::vector<std::vector<char>>& matrix, int x, int y);
bool isSymbol(char ch);
bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

std::pair<std::string, int> findNumber(const std::vector<std::vector<char>>& matrix, int x, int y_start) {
    std::string number = "";
    int y = y_start;

    // Move backwards to find the start of the number
    while (y >= 0 && isDigit(matrix[x][y])) {
        --y;
    }

    // Now y is the position just before the start of the number
    int start_pos = y + 1; // Start position of the number

    // Move forward to build the whole number
    for (int j = start_pos; j < matrix[x].size() && isDigit(matrix[x][j]); ++j) {
        number += matrix[x][j];
    }

    return {number, start_pos};
}


using namespace std;

int main(){
  std::cout << "Opening file... \n";
  
  int x_length = 0;
  int y_length = 0;

  string filename = "inputs.txt";

  fstream input_file;
  input_file.open(filename, ios::in);

  string line_in_loop;

  while (getline(input_file, line_in_loop)){
    ++y_length;
  }
  // closing file as i dont want to run into problems with being at the end of the file and not knowing
  input_file.close();

  string line_find_length;
  input_file.open(filename, ios::in);
  getline(input_file, line_find_length); 
  x_length = line_find_length.length();
  input_file.close();

  std::cout << "x axis length " << x_length << "\n";
  std::cout << "y axis length " << y_length << "\n";

  auto A = square_matrix(x_length);

  int running_total = 0;

  input_file.open(filename, ios::in);
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
  }

  bool num_found = false;
  bool symbol_found = false;

  for(int i = 0 ; i < y_length ; ++i ){
    for( int j = 0 ; j < x_length; ++j ){
      char val = A[i][j];
      if (isDigit(val)){
        bool symbol_found = checkSurrounding(A, i, j);

        if (symbol_found){
          auto [number, start_pos] = findNumber(A, i, j);
          if (!number.empty()) {
              std::cout << "Number found at (" << i << ", " << j << "): " << number << std::endl;
              running_total += std::stoi(number);
              std::cout << " Digit with adjacent symbol found at " << i << ", " << j << " " << number << "\n";
              std::cout << "  Running total = " << running_total << "\n";
          }
          
          // Skip the rest of the digits in this number
          j = start_pos + number.size() - 1;
        }
      }
    }
  } 
  std::cout << " final sum is " << running_total << "\n";
  return 0;
}

bool isSymbol(char ch) {
  if (ch == '#' || ch == '$' || ch == '%' || ch == '&' || ch == '*' || ch == '+' || ch == '-' || ch == '/' || ch == '=' || ch == '@'){
    return true;
  }
  return false;
}

bool checkSurrounding(const std::vector<std::vector<char>>& matrix, int x, int y) {
    if (matrix.empty() || matrix[0].empty()) return false;

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Check if x, y is out of bounds
    if (x < 0 || x >= rows || y < 0 || y >= cols) {
        std::cout << "Given coordinates are out of bounds." << std::endl;
        return false;
    }

    // Directions: Up, Down, Left, Right, and diagonals
    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

    for (int i = 0; i < 8; ++i) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        // Check if the new coordinates are within the bounds
        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
            if (isSymbol(matrix[newX][newY])) {
                return true;
            }
        }
    }

    return false;
}
