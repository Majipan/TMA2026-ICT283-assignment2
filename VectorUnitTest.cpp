#include "Vector.h"
#include <iostream>

using namespace std;

int main()
{
    cout << ">>> Test default constructor by creating new Vector" << endl;
    cout << "Vector<int> numbers;" << endl;
    Vector<int> numbers;
    cout << endl << "----------------------------------------" << endl << endl;


    cout << ">>> Test constructor overload with 10 capacity" << endl;
    cout << "Vector<int>* numbers2 = new Vector<int>(10);" << endl;
    Vector<int>* numbers2 = new Vector<int>(10);
    cout << "vector.Size() = " << numbers2->Size() << endl;
    cout << endl << "----------------------------------------" << endl << endl;


    cout << ">>> Test destructor" << endl;
    cout << "delete numbers2;" << endl << "numbers2 = nullptr;" << endl;
    delete numbers2;
    numbers2 = nullptr;
    cout << endl << "----------------------------------------" << endl << endl;


    cout << ">>> Test getter Size()" << endl;
    cout << "vector.Size() = " << numbers.Size() << endl;
    cout << endl << "----------------------------------------" << endl << endl;


    cout << ">>> Test Vector Insert at the back" << endl;
    cout << "Vector size: " << numbers.Size() << endl << "Inserting values..." << endl;
    numbers.Insert(0, 111);
    numbers.Insert(1, 333);
    numbers.Insert(2, 444);
    numbers.Insert(3, 555);
    cout << "Size of vector now: " << numbers.Size() << endl;
    for (int i = 0; i < numbers.Size(); ++i)
    {
        cout << numbers[i] << endl;
    }
    cout << endl << "----------------------------------------" << endl << endl;


    cout << ">>> Test insert in the middle moving some elements" << endl;
    numbers.Insert(1, 222);
    cout << "Size of vector now: " << numbers.Size() << endl;
    for (int i = 0; i < numbers.Size(); ++i)
    {
        cout << numbers[i] << endl;
    }
    cout << endl << "----------------------------------------" << endl << endl;


    cout << ">>> Test [] operator to obtain value" << endl;
    cout << "vector[0]: " << numbers[0] << endl;
    cout << "vector[2]: " << numbers[2] << endl;
    cout << "vector[4]: " << numbers[4] << endl;
    cout << endl << "----------------------------------------" << endl << endl;


    cout << ">>> Test [] operator to set value" << endl;
    cout << "vector[4] = 345;" << endl;
    numbers[4] = 345;
    cout << "vector[4]: " << numbers[4] << endl;
    cout << endl << "----------------------------------------" << endl << endl;


    cout << ">>> Test Delete" << endl;
    cout << "Size of vector now: " << numbers.Size() << endl;
    cout << "Delete index 3, value: " << numbers[3] << endl;
    numbers.Delete(3);
    cout << "Size of vector now: " << numbers.Size() << endl;
    for (int i = 0; i < numbers.Size(); ++i)
    {
        cout << numbers[i] << endl;
    }
    cout << endl << "----------------------------------------" << endl << endl;


    cout << ">>> Test vector.Clear()" << endl;
    numbers.Clear();
    cout << "Size of vector now: " << numbers.Size() << endl;
    cout << endl << "----------------------------------------" << endl << endl;

    return 0;
}
