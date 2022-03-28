
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
            getline(fin,arr_Item[i].name);       //для ввода попробовать gets
            fin >> arr_Item[i].value;
            fin >> arr_Item[i].weigt;
            fin.get();
        }
       
        //cout << arr_Item[0].name << endl;

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
                fout << " "<< endl;
            }
        }

        fout << " " << endl;
        fout << "Total weight is: ";
        fout << totalweigt << endl;
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
                cout << "Try again" << endl;
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