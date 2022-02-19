#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include "Knapsack.h"
#include "Knap.h"


#define ull unsigned long long

bool* dec2bin(ull dec, ull comb_num);
void brute_force_alg(Knapsack knapsack, char flag);
void greedy_alg(Knapsack knapsack, char flag);
void dynamic_alg(Knapsack knapsack, char flag);

void runtime_tester();

int main()
{
    Knapsack knapsack("data_file.txt");
    //Knapsack knapsack;


    knapsack.elements_print();

    std::cout << "Knapsack capacity:\t\t" << knapsack.capacity << '\n';
    std::cout << "Number of objects available:\t" << knapsack.items.size() << "\n\n";


    brute_force_alg(knapsack, 'V');
    greedy_alg(knapsack, 'V');
    dynamic_alg(knapsack, 'V');

    runtime_tester();

}

void runtime_tester()
{
    clock_t st, nd;
    srand(time(nullptr));
    double ex = 0;

    std::fstream results;
    results.open("results.txt", std::ios::out);
    results << "Name\tEl_num\tCapacity\tTime" << '\n';


    std::vector<Knap> items;
    for (int cap = 10; cap < 160; cap += 10){
        for (int el_num = 10; el_num < 28; el_num += 2){
            items.clear();
            items.resize(el_num);
            for (int j = 0; j < el_num; j++){
                items[j].ID = j + 1;

                items[j].val = (rand() % 20) + 1;
                items[j].weight = (rand() % 20) + 1;
                items[j].relVal = (float) items[j].val / (float) items[j].weight;
            }


            Knapsack knapsack(items, cap);
            st = clock();
            brute_force_alg(knapsack, 'I');
            nd = clock();
            ex = (double)(nd - st) / CLOCKS_PER_SEC;
            results << "Brute Force\t" << el_num << '\t' << cap << '\t' << ex << '\n';
        }
    }

    for (int cap = 10; cap < 160; cap += 10){

        for (int el_num = 40000; el_num < 300000; el_num += 20000){
            items.clear();
            items.resize(el_num);
            for (int j = 0; j < el_num; j++){
                items[j].ID = j + 1;

                items[j].val = (rand() % 20) + 1;
                items[j].weight = (rand() % 20) + 1;
                items[j].relVal = (float) items[j].val / (float) items[j].weight;
            }

            Knapsack knapsack(items, cap);
            st = clock();
            greedy_alg(knapsack, 'I');
            nd = clock();
            ex = (double)(nd - st) / CLOCKS_PER_SEC;
            results << "Greedy Algo\t" << el_num << '\t' << cap << '\t' << ex << '\n';


            st = clock();
            dynamic_alg(knapsack, 'I');
            nd = clock();
            ex = (double)(nd - st) / CLOCKS_PER_SEC;
            results << "Dynamic Algo\t" << el_num << '\t' << cap << '\t' << ex << '\n';
        }
    }
    results.close();
}

void brute_force_alg(Knapsack knapsack, char flag){
    int curr_weight = 0, curr_value = 0, max_value = 0;
    int *elements;
    bool** bin_combinations;

    ull comb_num = (1u << knapsack.items.size()) - 1;
    bin_combinations = new bool*[comb_num];
    elements = new int[knapsack.items.size()];

    int j;
    for (ull i = 0; i < comb_num; i++){
        bin_combinations[i] = dec2bin(i+1, knapsack.items.size());
        j = 0;

        for (auto &a: knapsack.items){
            if (bin_combinations[i][j++]){
                curr_weight += a.weight;
                curr_value += a.val;
            }
        }

        if (curr_value > max_value && curr_weight <= knapsack.capacity){
            max_value = curr_value;

            for (ull x = 0; x < knapsack.items.size(); x++)
                elements[x] = bin_combinations[i][x];
        }


        curr_weight = 0;
        curr_value = 0;

        delete[]bin_combinations[i];
    }

    if (flag == 'V'){
        std::cout << "Brute-force algorithm:\n";
        knapsack.knapsack_print(elements);
    }


    delete[]elements;
    delete[]bin_combinations;

}

void greedy_alg(Knapsack knapsack, char flag){
    std::sort(knapsack.items.begin(), knapsack.items.end());

    int curr_weight = 0, *elements;

    elements = new int[knapsack.items.size()];

    for (ull i = 0; i < knapsack.items.size(); i++){
        if (knapsack.items[i].weight + curr_weight <= knapsack.capacity){
            curr_weight += knapsack.items[i].weight;
            elements[i] = 1;
        }
        else
            elements[i] = 0;

    }

    if (flag == 'V'){
        std::cout << "Greedy algorithm:\n";
        knapsack.knapsack_print(elements);
    }

    delete []elements;
}

void dynamic_alg(Knapsack knapsack, char flag){
    ull el_num = knapsack.items.size() + 1;
    int cap = knapsack.capacity + 1;

    int** dynamic_matrix;

    dynamic_matrix = new int* [el_num+1];

    for (ull i = 0; i < el_num; i++)
        dynamic_matrix[i] = new int[cap+1];

    for (ull i = 0; i < el_num; i++)
        for (int j = 0; j < cap; j++)
            dynamic_matrix[i][j] = 0;

    for (ull i = 1; i < el_num; i++){

        for (ull j = 1; j < cap; j++){

            if (knapsack.items[i-1].weight > j)
                dynamic_matrix[i][j] = dynamic_matrix[i - 1][j];

            else{
                dynamic_matrix[i][j] = std::max(dynamic_matrix[i - 1][j], dynamic_matrix[i - 1][j - knapsack.items[i-1].weight] + knapsack.items[i-1].val);
            }

        }
    }

    ull tmp = el_num;
    int j = cap-1;
    int *elements = new int[el_num];

    while(tmp > 1 && j >0){
        tmp--;

        if (dynamic_matrix[tmp][j] > dynamic_matrix[tmp - 1][j]){
            elements[tmp-1] = 1;
            j -= knapsack.items[tmp-1].weight;
        }

    }

    if (flag == 'V'){
        std::cout << "Dynamic algorithm:\n";
        knapsack.knapsack_print(elements);
    }

    delete []elements;

    for (ull i = 0; i < el_num; i++)
        delete []dynamic_matrix[i];

    delete []dynamic_matrix;

}

bool *dec2bin(ull dec, ull comb_num){
    bool* bin = new bool[comb_num];

    for (int i = 0; i < comb_num; i++)
        bin[i] = false;

    int r, x=0;
    while (dec != 0){
        r = dec % 2;
        if (r == 1)
            bin[x++] = true;
        else
            bin[x++] = false;
        dec /= 2;

    }

    return bin;
}