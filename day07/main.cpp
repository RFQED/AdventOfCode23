#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>
#include <tuple>
#include <map>


using namespace std;
vector<string> split_input_line(string line, string delim);
std::tuple<int, int> classify_string(const string& s);
bool comparePairs(const pair<string, int>& a, const pair<string, int>& b);

int part1();
int part2();

int part1(){
    //  32T3K 765
    //  T55J5 684
    //  KK677 28
    //  KTJJT 220
    //  QQQJA 483
    string filename = "inputs.txt";

    fstream input_file;
    input_file.open(filename, ios::in);

    string line;
    vector<string> l;
    int hand_num = 0;
    vector<pair<string, int>> hands;

    while (std::getline(input_file, line)) {
        l = split_input_line(line, " ");
        hands.push_back(std::make_pair(l[0], stoi(l[1])));
        hand_num++;
    }  
    input_file.close();

    vector<pair<string, int>> five_kind;
    vector<pair<string, int>> four_kind;
    vector<pair<string, int>> full_house;
    vector<pair<string, int>> three_kind;
    vector<pair<string, int>> two_pair;
    vector<pair<string, int>> one_pair;
    vector<pair<string, int>> high_card;

    for (auto & hand : hands) {
        auto [max_count, second_max_count] = classify_string(hand.first);
        // Classify based on frequencies
        if (max_count == 5) five_kind.push_back(hand);
        else if (max_count == 4) four_kind.push_back(hand);
        else if (max_count == 3 && second_max_count == 2) full_house.push_back(hand);
        else if (max_count == 3) three_kind.push_back(hand);
        else if (max_count == 2 && second_max_count == 2) two_pair.push_back(hand);
        else if (max_count == 2) one_pair.push_back(hand);
        else{
            high_card.push_back(hand);
        }
    }

    std::cout << " size of each class \n";
    std::cout << " five = "  << five_kind.size() <<  " \n";
    std::cout << " four = "  << four_kind.size() <<  " \n";
    std::cout << " full_house = "  << full_house.size() <<  " \n";
    std::cout << " three = "  << three_kind.size() <<  " \n";
    std::cout << " two = "  << two_pair.size() <<  " \n";
    std::cout << " one = "  << one_pair.size() <<  " \n";
    std::cout << " high = "  << high_card.size() <<  " \n";

    // std::cout << "Before sorting \n";
    // for (const auto& three : three_kind) {
    //     cout << three.first << " = " << three.second << endl;
    // }

    // Sort the vector using the custom comparison function
    sort(five_kind.begin(), five_kind.end(), comparePairs);
    sort(four_kind.begin(), four_kind.end(), comparePairs);
    sort(full_house.begin(), full_house.end(), comparePairs);
    sort(three_kind.begin(), three_kind.end(), comparePairs);
    sort(two_pair.begin(), two_pair.end(), comparePairs);
    sort(one_pair.begin(), one_pair.end(), comparePairs);
    sort(high_card.begin(), high_card.end(), comparePairs);

    // std::cout << "After sorting \n";
    // for (const auto& three : three_kind) {
    //     cout << three.first << " = " << three.second << "\n";
    // }
    // std::cout << "\n ";

    std::vector<pair<string, int>> all_hands;
    all_hands.insert(all_hands.end(), high_card.begin(), high_card.end());
    all_hands.insert(all_hands.end(), one_pair.begin(), one_pair.end());
    all_hands.insert(all_hands.end(), two_pair.begin(), two_pair.end());
    all_hands.insert(all_hands.end(), three_kind.begin(), three_kind.end());
    all_hands.insert(all_hands.end(), full_house.begin(), full_house.end());
    all_hands.insert(all_hands.end(), four_kind.begin(), four_kind.end());
    all_hands.insert(all_hands.end(), five_kind.begin(), five_kind.end());

    long total = 0;
    for(int i = 0; i < all_hands.size(); i++){
        std::cout << all_hands[i].first << " " <<  all_hands[i].second << "\n";
        total += (all_hands[i].second * (i+1));
    }
    std::cout << total << "\n";


    return 0;
}

int part2(){


    return 0;

}

int main() {
    part1();
    //part2();
}

bool comparePairs(const pair<string, int>& a, const pair<string, int>& b) {
    map<char, int> rank = {
        {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
        {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
        {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}
    };

    for (int i = 0; i < a.first.length() && i < b.first.length(); ++i) {
        if (rank[a.first[i]] != rank[b.first[i]]){
            bool result = rank[a.first[i]] < rank[b.first[i]];
            return rank[a.first[i]] < rank[b.first[i]];
        }
    }
    return a.first.length() < b.first.length();
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


std::tuple<int, int> classify_string(const string& s) {
    map<char, int> freq;

    // Count the frequency of each character
    for (char ch : s) {
        freq[ch]++;
    }

    int maxCount = 0, secondMaxCount = 0;
    for (auto& p : freq) {
        if (p.second > maxCount) {
            secondMaxCount = maxCount;
            maxCount = p.second;
        } else if (p.second > secondMaxCount) {
            secondMaxCount = p.second;
        }
    }

    return {maxCount, secondMaxCount};
}