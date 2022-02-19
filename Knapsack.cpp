#include "Knapsack.h"
#include "Knap.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>


Knapsack::Knapsack(const char* fileName)
{
    std::fstream data_file;

    data_file.open(fileName, std::ios::in);

    if (!data_file.is_open()){
        std::cout<<"Error while opening the file "<<fileName<<". Terminating program.\n";
        exit(1);
    }

    int el_num, cap;
    data_file >> el_num;
    data_file >> cap;

    capacity = cap;
    items.resize(el_num);

    for (int i = 0; i < el_num; i++){
        data_file >> items[i].weight;
        data_file >> items[i].val;

        items[i].relVal = (float) items[i].val / (float) items[i].weight;
        items[i].ID = i+1;
    }


    data_file.close();

}

Knapsack::Knapsack(){
    capacity = input_sanitizer("Specify capacity of your knapsack:\t");
    int el_num = input_sanitizer("Specify number of elements available:\t");

    items.resize(el_num);

    int weight, value;

    for (int i = 0; i < el_num; i++){

        value = input_sanitizer("Specify value of the object " + std::to_string(i + 1) + ":\t");
        weight = input_sanitizer("Specify weight of the object " + std::to_string(i + 1) + ":\t");

        items[i].val = value;
        items[i].weight = weight;
        items[i].relVal = (float) value / (float) weight;
        items[i].ID = i+1;

        std::cout<<'\n';
    }
}

Knapsack::Knapsack(std::vector<Knap> &it, int cap) {
    items = it;
    capacity = cap;
}

int Knapsack::input_sanitizer(const std::string &message){
    int result;
    std::string buf;
    do{
        std::cout << message;
        std::cin >> buf;

        try {
            result = std::stoi(buf);
            if (result < 0)
                std::cout << "Inserted value has to be a positive integer! Please, try again.\n";
        }
        catch(...){
            std::cout << "Inserted value has to be a positive integer! Please, try again.\n";
            result = -1;
        }

    } while (result < 0);

    return result;
}

void Knapsack::knapsack_print(const int* elements){
    int value = 0, weight = 0, i=0;


    std::cout << "Objects in the knapsack:\n";
    for (auto &a: items){
        if (elements[i++] == 1){
            std::cout << "Value:\t\t" << a.val << '\n';
            std::cout << "Weight:\t\t" << a.weight << '\n';
            std::cout << "ID number:\t" << a.ID << "\n\n";

            value += a.val;
            weight += a.weight;
        }
    }

    std::cout << "Summary value of objects in the knapsack:\t" << value << '\n';
    std::cout << "Summary weight of objects in the knapsack:\t" << weight << "\n\n";
}

void Knapsack::elements_print(){
    int value = 0, weight = 0;

    std::cout << "Available objects:\n";
    for (auto &a: items){
        std::cout << "Value:\t\t" << a.val << '\n';
        std::cout << "Weight:\t\t" << a.weight << '\n';
        std::cout << "ID number:\t" << a.ID << "\n\n";

        value += a.val;
        weight += a.weight;
    }

    std::cout << "Summary value of objects in the knapsack:\t" << value << '\n';
    std::cout << "Summary weight of objects in the knapsack:\t" << weight << "\n\n";
}

