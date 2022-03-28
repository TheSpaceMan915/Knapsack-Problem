
#include <iostream>
#include <fstream>

#include <windows.h>
#include "Knapsack.h"




//функция для чтения списка с вещами,весами
KnapsackItem* readfile(string filename, int number)
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

void bublsort(KnapsackItem arr[], int number)        //пузырьковая сортировка
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
void fmain(KnapsackItem arr[], int number, int capacity,int &position)
{
    int totalweigt = 0;

    //вычисляю отношение цены к весу
    for (int i = 0; i < number; i++)
    {
        //static_cast преобразует int в double
        arr[i].ratio = static_cast<double> (arr[i].value) / arr[i].weigt;
    }

    bublsort(arr, number);          //сортировка пузырьком
   
    for (position ; position < number; position++)
    {
        if ((totalweigt + arr[position].weigt) <= capacity)      //упаковываю рюкзак
        {
            totalweigt += arr[position].weigt;
        }
        else
        {
            break;
        }
    }

    cout << "Total weight is: ";
    cout << totalweigt<< endl;
    char stop;
    cin >> stop;
}

void PrintFile(int position, int number,KnapsackItem arr[])
{
    ofstream fout("Things.txt");
    if (!fout)
    {
        cerr << "error";
        exit(1);
    }
    else
    {
        fout << "You've got in your knapsack:" << endl;
        for (int i = 0; i < position; i++)            
        {
            fout << arr[i].name << endl;
            fout << arr[i].ratio << endl;
        }

        fout << "There's no room for your:" << endl;
        for (position; position < number; position++)
        {
            fout << arr[position].name << endl;
            fout << arr[position].ratio << endl;
        }

    }

    fout.close();
}

void menu()
{
    int choice;
    
    int number, capacity;
    KnapsackItem* arr_Items;
    int position = 0;

    do
    {
        system("cls");
        cout << "What would you like to do?" << endl;
        cout << "1. Pack up the knapsack for university" << endl;
        cout << "2. Pack up the knapsack for the beach" << endl;
        cout << "3. Pack up the knapsack for travelling" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the number of items: ";
            cin >> number;

            cout << "Enter the maximum weight capacity: ";
            cin >> capacity;

            arr_Items = readfile("List.txt", number);

            fmain(arr_Items, number, capacity, position);

            PrintFile(position, number, arr_Items);
            break;

        case 2:
            cout << "Enter the number of items: ";
            cin >> number;

            cout << "Enter the maximum weight capacity: ";
            cin >> capacity;

            arr_Items = readfile("Beach.txt", number);

            //fmain(arr_Items, number, capacity);
            break;

        case 3:
            cout << "Enter the number of items: ";
            cin >> number;

            cout << "Enter the maximum weight capacity: ";
            cin >> capacity;

            arr_Items = readfile("Travelling.txt", number);

            //fmain(arr_Items, number, capacity);
            break;
        }

    } while (choice != 4);
}

int main()
{
    

    menu();

    return 0;
}

