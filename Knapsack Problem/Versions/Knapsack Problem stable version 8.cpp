﻿
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct KnapsackItem
{
    string name;
    int value;
    int weigt;
    double ratio;
};

//функция для чтения списка с вещами,весами

KnapsackItem* ReadFile(string filename, int number)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cout << "Error of reading the file";
    }
    else
    {
        KnapsackItem* arr_Item = new KnapsackItem[number];
        for (int i = 0; i < number; i++)
        {
            getline(fin, arr_Item[i].name);       //для ввода попробовать gets
            fin >> arr_Item[i].value;
            fin >> arr_Item[i].weigt;
            fin.get();
        }

        fin.close();

        return arr_Item;            /*смысла в delete после return нет,
                                    после return  происходит выход из функции */
    }
}

//пузырьковая сортировка

void bublsort(KnapsackItem* arr, int number)
{
    for (int i = 1; i < number; ++i)     //цикл устанавливает кол-во итераций
    {
        for (int j = 0; j < number - i; j++)     //цикл идёт по элем. массива и сравн. сосед. элем.
        {
            if (arr[j].ratio < arr[j + 1].ratio)
            {
                KnapsackItem z = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = z;
            }
        }
    }
}

//главная функция

void fmain(KnapsackItem* arr, int number, int capacity)
{

    //вычисляю отношение цены к весу
    for (int i = 0; i < number; i++)
    {
        //static_cast преобразует int в double
        arr[i].ratio = static_cast<double> (arr[i].value) / arr[i].weigt;
    }

    bublsort(arr, number);          //сортирую массив

}

KnapsackItem* AddNewItems(int &totalweigt, int capacity)
{
    cout << "Would you like to add new items?" << endl;
    cout << "1 - Yes, 2 - No" << endl;

    bool answer;
    cin >> answer;

    if (answer)
    {

        int newnumber;

        cout << "How many items would you like to add?" << endl;
        cin >> newnumber;
        cin.ignore(32767, '\n');

        KnapsackItem* arr_Newitems = new KnapsackItem[newnumber];

        for (int j = 0; j < newnumber; j++)
        {
            getline(cin, arr_Newitems[j].name);

            cin >> arr_Newitems[j].value;
            cin.ignore(32767, '\n');

            cin >> arr_Newitems[j].weigt;
            cin.ignore(32767, '\n');

            if (totalweigt + arr_Newitems[j].weigt > capacity)
            {
                cout << "Enter weight less than " << capacity - totalweigt << endl;

                cin >> arr_Newitems[j].weigt;
                cin.ignore(32767, '\n');

                totalweigt += arr_Newitems[j].weigt;
            }
            else
            {
                totalweigt += arr_Newitems[j].weigt;
            }

            fmain(arr_Newitems, newnumber, capacity);
        }

        return arr_Newitems;

    }
}

//функция вывода в файл

void PrintFile(int number, int capacity, KnapsackItem* arr)
{
    int totalweigt = 0;

    ofstream fout("Things.txt");
    if (!fout)
    {
        cerr << "error";
        exit(1);
    }
    else
    {

        for (int i = 0; i < number; i++)
        {
            if (totalweigt + arr[i].weigt <= capacity)
            {
                totalweigt = totalweigt + arr[i].weigt;
                fout << "You've got in your knapsack:" << endl;
                fout << arr[i].name << endl;
                fout << arr[i].weigt << endl;
                fout << " " << endl;
            }
            else
            {
                fout << "There's no room for your:" << endl;
                fout << arr[i].name << endl;
                fout << arr[i].weigt << endl;
                fout << " " << endl;
            }
        }

        if (totalweigt < capacity)
        {
            KnapsackItem* arr_NewIt = AddNewItems(totalweigt, capacity);
        }

        else
        {
            fout << " " << endl;
            fout << "Total weight is: ";
            fout << totalweigt << endl;
        }

    }

    fout.close();
}


void menu()
{
    int choice;

    int number, capacity, numberstr;
    KnapsackItem* arr_Items;

    do
    {
        system("cls");
        cout << "What would you like to do?" << endl;
        cout << "1. Pack up the knapsack for university" << endl;
        cout << "2. Pack up the knapsack for girls" << endl;
        cout << "3. Pack up the knapsack for travelling" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            numberstr = 4;

            cout << "Enter the number of items: ";
            cin >> number;

            if (number > numberstr)
            {
                cout << "Sorry you can't take more than 4 items" << endl;
                cout << "Enter your number again" << endl;
                cin >> number;
            }

            cout << "Enter the maximum weight capacity: ";
            cin >> capacity;

            arr_Items = ReadFile("University.txt", number);

            fmain(arr_Items, number, capacity);

            PrintFile(number, capacity, arr_Items);
            break;

        case 2:
            cout << "Enter the number of items: ";
            cin >> number;

            cout << "Enter the maximum weight capacity: ";
            cin >> capacity;

            arr_Items = ReadFile("Girls.txt", number);

            fmain(arr_Items, number, capacity);

            PrintFile(number, capacity, arr_Items);
            break;

        case 3:
            cout << "Enter the number of items: ";
            cin >> number;

            cout << "Enter the maximum weight capacity: ";
            cin >> capacity;

            arr_Items = ReadFile("Travelling.txt", number);

            fmain(arr_Items, number, capacity);

            PrintFile(number, capacity, arr_Items);
            break;
        }

    } while (choice != 4);
}
