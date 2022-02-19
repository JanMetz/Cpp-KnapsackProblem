#ifndef MAIN_CPP_KNAP_H
#define MAIN_CPP_KNAP_H

struct Knap{
    int val;
    int weight;
    double relVal;      //relative value which is value/weight

    int ID;

    friend bool operator<(const Knap &Lhs, const Knap &Rhs);
};


#endif //MAIN_CPP_KNAP_H
