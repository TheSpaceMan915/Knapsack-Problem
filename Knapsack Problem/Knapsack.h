
#ifndef Knapsack_h      //предотвращение вызова заголов. файла больше одного раза
#define Knapsack_h
#include <string>

using namespace std;
#pragma once


struct KnapsackItem     //создаю структуру моего предмета из рюкзака
{
    string name;
    int value;
    int weight;
    double ratio;
};

KnapsackItem* ReadFile(string , int );

void Bublsort(KnapsackItem* , int);

void Fmain(KnapsackItem* , int, int);

void PrintFile(int, int, KnapsackItem*);

void menu();

KnapsackItem* AddNewItems(int&, int, int);


#endif