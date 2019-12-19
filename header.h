//
// Created by Tomas on 10/3/2019.
//

#ifndef HASH_HEADER_H
#define HASH_HEADER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include<numeric>
#include <chrono>
#include <bitset>

#define RANDOM_LENGTH 5
#define RANDOM_COUNT 1000000
#define SIMILAR_LENGHT 5
#define SIMILAR_COUNT 100000

void read(std::string &data, char *string);
void testRandomWords();
void testSimilar();

// paimta i� https://github.com/objprog/paskaitos2019/wiki/Laiko-matavimas
class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
    Timer() : start{std::chrono::high_resolution_clock::now()} {}
    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const {
        return std::chrono::duration<double>
                (std::chrono::high_resolution_clock::now() - start).count();
    }
};


#endif //HASH_HEADER_H
