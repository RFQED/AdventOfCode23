
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <climits>

using namespace std;

int part1();
int part2();

int part1(){
    std::string line;
    std::fstream file("inputs.txt");
    std::vector<long> seeds; // intial seed numbers

    // reading initial seed numbers
    getline(file, line);
    std::stringstream ss(line.substr(7, (line.end() - line.begin()) - 7));
    std::string val;

    while (getline(ss, val, ' ')) {
        if (val.size() > 0) {
            //std::cout << &seedword[0] << "\n";
            seeds.push_back(stol(&val[0], NULL, 10));
        }
    }

    int filler = 0;
    getline(file, line); // skip line

    // Each tuple in a vector is the conversion rule with: destination start, source start, range length
    std::vector<std::vector<std::tuple<long, long, long>>> filters(7);

    while (getline(file, line)) {
        if (line.size() == 0) {
            filler++;
            getline(file, line);
            continue;
        }

        std::stringstream linestream(line);
        std::string convert;

        // filter conversion maps

        long filterA = 0; long filterB = 0; long filterC = 0;

        while (getline(linestream, convert, ' ')) {
            if (convert.size() > 0) { 
                filterA = filterB;
                filterB = filterC;
                //std::cout << &convert[0] << "\n";

                filterC = stol(&convert[0], NULL, 10);
            }
        }
        filters[filler].push_back(std::make_tuple(filterA, filterB, filterC));
    }
    file.close();


    for (int i = 0; i < filters.size(); ++i) {
        sort(filters[i].begin(), filters[i].end());
    }

    // Apply conversion map to each seed
    for (int i = 0; i < seeds.size(); ++i) {
        for (int j = 0; j < filters.size(); ++j) {
            for (int k = 0; k < filters[j].size(); k++) {
                long destination = get<0>(filters[j][k]);
                long source = get<1>(filters[j][k]);
                long range = get<2>(filters[j][k]);
                                
                long a = seeds[i];
                if (a >= source && a <= source + range - 1) {                
                    a = (a - source) + destination;
                    seeds[i] = a;
                    break;
                }
            }
        }
    }


    long lowest = LONG_MAX;
    
    for (long seed : seeds) {
        lowest = std::min(lowest, seed);
    }

    std::cout << " total " << lowest << "\n";
    return 0;
}

int main() {
    part1();
}
