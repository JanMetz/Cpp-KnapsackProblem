#ifndef MAIN_CPP_KNAPSACK_H
#define MAIN_CPP_KNAPSACK_H

#include "Knap.h"
#include <string>
#include <vector>


class Knapsack{
public:
    std::vector<Knap> items;
    int capacity;

    void knapsack_print(const int* elements);
    void elements_print();
    static int input_sanitizer(const std::string &message);

    explicit Knapsack(const char* fileName);
    Knapsack();
    Knapsack(std::vector<Knap> &it, int cap);
};


#endif //MAIN_CPP_KNAPSACK_H
