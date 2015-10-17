#include <iostream>
#include <cstdlib>

using namespace std;

class basic
{
    double** p;
    int x;
    int y;

public:
    basic(int x1 = 0, int y1 = 0)
    {
        cout << "Creating basic" << endl;
        x = x1;
        y = y1;
        alloc(x, y);
    }

    ~basic()
    {
        cout << "Deleting basic" << endl;
        free_mem(x, y);
    }

    void alloc(int x, int y)
    {
        p = new double* [x];
        for(int i = 0; i < x; i++)
            *(p + i) = new double[y];
    }

    void free_mem(int x, int y)
    {
        for(int i = 0; i < x; i++)
            delete[] * (p + i);
        delete[] p;
    }

    void show_all()
    {
        cout << "Showing object" << endl;
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++)
                cout << "a[" << i << "][" << j << "]"
                     << " = " << p[i][j] << endl;
        cout << endl;
    }

    void set_object()
    {
        double value;
        cout << "Setting object" << endl;
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++) {
                cout << "a[" << i << "][" << j << "]"
                     << " = ";
                cin >> value;
                p[i][j] = value;
            }
        cout << endl;
    }

    const basic& operator=(const basic& obj2)
    {
        cout << "Operator =" << endl;
        free_mem(x, y);
        x = obj2.x;
        y = obj2.y;
        alloc(x, y);
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++)
                (*this).p[i][j] = obj2.p[i][j];
        return *this;
    }

    void* operator new(size_t size)
    {
        cout << "Using overloaded new:" << size << endl;
        return malloc(size);
    }

    void* operator new [](size_t size) {
        cout << "Using overloaded new[]:" << size << endl;
        return malloc(size);
    }

    void
    operator delete(void* p)
    {
        cout << "Using overloaded delete:" << endl;
        free(p);
    }

    void operator delete [](void* p) {
        cout << "Using overloaded delete[]:" << endl;
        free(p);
    }

    /* const basic
     operator+(const basic& obj2)
     {
         int x_min, y_min, x_max, y_max;

         cout << "Operator +" << endl;
         if(x > obj2.x) {
             x_min = obj2.x;
             x_max = x;
         } else {
             x_min = x;
             x_max = obj2.x;
         }

         if(y > obj2.y) {
             y_min = obj2.y;
             y_max = y;
         } else {
             y_min = y;
             y_max = obj2.y;
         }

         basic temp(x_max, y_max);

         for(int i = 0; i < x_min; i++)
             for(int j = 0; j < y_min; j++)
                 temp.p[i][j] = p[i][j] + obj2.p[i][j];
                 //дописать дополнение разных элементов
         return temp;
     }*/

    /*void compare(const basic& obj2)
    {
        int x_min, y_min;

        if(x > obj2.x)
            x_min = obj2.x;
        else
            x_min = x;

        if(y > obj2.y)
            y_min = obj2.y;
        else
            y_min = y;

        for(int i = 0; i < x_min; i++) {
            for(int j = 0; j < y_min; j++)
                    if(p[i][j]< obj2.p[i][j]) {
                        cout << "obj1[" << i << "][" << j << "][" << k << "] < ";
                        cout << "obj2[" << i << "][" << j << "][" << k << "] " << endl;
                    } else if(p[i][j][k] > obj2.p[i][j][k]) {
                        cout << "obj1[" << i << "][" << j << "][" << k << "] > ";
                        cout << "obj2[" << i << "][" << j << "][" << k << "] " << endl;
                    } else {
                        cout << "obj1[" << i << "][" << j << "][" << k << "] = ";
                        cout << "obj2[" << i << "][" << j << "][" << k << "] " << endl;
                    }
        }
        cout << endl;
    }*/

    friend const basic
    operator+(const basic&, double);
    friend const basic operator+(double, const basic& );
};

const basic operator+(const basic& obj2, double d)
{
    basic temp(obj2.x, obj2.y);
    cout << "Operator + (friendly)" << endl;
    for(int i = 0; i < obj2.x; i++)
        for(int j = 0; j < obj2.y; j++)
            temp.p[i][j] = obj2.p[i][j] + d;
    return temp;
}

const basic operator+(double d, const basic& obj2)
{
    basic temp(obj2.x, obj2.y);
    cout << "Operator + (friendly)" << endl;
    for(int i = 0; i < obj2.x; i++)
        for(int j = 0; j < obj2.y; j++)
            temp.p[i][j] = obj2.p[i][j] + d;
    return temp;
}

int main()
{
    //пример для локального оператора =
    /*basic obj1(2, 1), obj2(2, 2);
    obj1.set_object();
    obj1.show_all();
    obj2.set_object();
    obj2.show_all();
    obj1 = obj2;
    obj1.show_all();*/

//пример для локальных new & delete
    /*basic* ptr;
    ptr = new basic;
    ptr->show_all();
    delete ptr;*/

//пример для локальных new[] & delete[]
    /*basic* ptr2;
    ptr2 = new basic [2];
    for(int i = 0; i < 2; i++)
        ptr2->show_all();
    delete[] ptr2;*/

//пример для локального оператора = (дописать код)
    /*basic obj11(1, 1), obj12(2, 2);
    obj11.set_object();
    obj11.show_all();
    obj12.set_object();
    obj12.show_all();
    obj1 + obj2;
    obj1.show_all();*/

//пример для дружественного оператора =
    basic obj2(2, 1), obj21;
    double d = 8.56;
    obj2.set_object();
    obj2.show_all();
    obj21 = d+obj2 + d ;
    obj21.show_all();
    return 0;
}
