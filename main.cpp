#include <iostream>
#include <cstdlib>

using namespace std;

class basic
{
    double** p;
    int x;
    int y;

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

public:
    /*basic(int x1 = 0, int y1 = 0)
    {
        cout << "Creating basic" << endl;
        x = x1;
        y = y1;
        alloc(x, y);
    }*/

    basic()
    {
        cout << "Creating basic" << endl;
        x = 0;
        y = 0;
        p = 0;
        // alloc(x, y);
    }

    ~basic()
    {
        cout << "Deleting basic" << endl;
        free_mem(x, y);
    }
    
    basic operator()(int, int);

    void show_all()
    {
        cout << "Showing object" << endl << "X : " << x << endl << "Y : " << y << endl;
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

    //префиксная версия возвращает значение после инкремента
    const basic&
    operator++()
    {
        cout << "Prefix increment operator" << endl;
        for(int i = 0; i < (*this).x; i++)
            for(int j = 0; j < (*this).y; j++)
                ++(*this).p[i][j];
        return *this;
    }

    //постфиксная версия возвращает значение до инкремента
    const basic operator++(int)
    {
        basic temp;
        temp = (*this);
        cout << "Postfix increment operator" << endl;
        for(int i = 0; i < (*this).x; i++)
            for(int j = 0; j < (*this).y; j++)
                ++(*this).p[i][j];
        return temp;
    }

    const basic operator+(const basic& obj2)
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

        if(x == x_max && y == y_max)
            for(int i = x_min; i < x_max; i++)
                for(int j = y_min; j < y_max; j++)
                    temp.p[i][j] = p[i][j];

        if(obj2.x == x_max && obj2.y == y_max)
            for(int i = x_min; i < x_max; i++)
                for(int j = y_min; j < y_max; j++)
                    temp.p[i][j] = obj2.p[i][j];

        if(obj2.x == x_max && y == y_max) {
            for(int i = 0; i < x_min; i++)
                for(int j = y_min; j < y_max; j++)
                    temp.p[i][j] = p[i][j];

            for(int i = x_min; i < x_max; i++)
                for(int j = 0; j < y_min; j++)
                    temp.p[i][j] = obj2.p[i][j];
        }

        if(x == x_max && obj2.y == y_max) {
            for(int i = 0; i < x_min; i++)
                for(int j = y_min; j < y_max; j++)
                    temp.p[i][j] = obj2.p[i][j];

            for(int i = x_min; i < x_max; i++)
                for(int j = 0; j < y_min; j++)
                    temp.p[i][j] = p[i][j];
        }
        return temp;
    }

    bool operator<(const basic& obj2)
    {
        double sum1 = 0, sum2 = 0;
        cout << "Local operator <" << endl;
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++)
                sum1 += p[i][j];
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++)
                sum2 += obj2.p[i][j];
        if(sum1 < sum2)
            return true;
        else
            return false;
    }

    //дописать ()
    basic operator()(int a, int b)
    {
        cout << "Operator ()" << endl;
        x = a;
        y = b;
        alloc(x, y);
        // set_object();
        return *this;
    }

    double*& operator[](int i)
    {
        cout << "Operator []" << endl;
        if(i < 0 || i >= x)
            return p[0];
        return p[i];
    }

    friend const basic operator+(const basic&, double);
    friend const basic operator+(double, const basic&);

    friend ostream& operator<<(ostream& s, basic& obj);

    friend const basic& operator--(basic& obj);
    friend const basic operator--(basic& obj, int);

    friend bool operator>(const basic& obj, double d);
    friend bool operator>(double d, const basic& obj);
};

//оператор > (сумма ячеек сравнивается с double)
bool operator>(const basic& obj, double d)
{
    double temp = 0;
    for(int i = 0; i < obj.x; i++)
        for(int j = 0; j < obj.y; j++)
            temp += obj.p[i][j];
    if(temp > d)
        return true;
    else
        return false;
}

bool operator>(double d, const basic& obj)
{
    double temp = 0;
    for(int i = 0; i < obj.x; i++)
        for(int j = 0; j < obj.y; j++)
            temp += obj.p[i][j];
    if(d > temp)
        return true;
    else
        return false;
}

//префиксная версия возвращает значение после инкремента
const basic& operator--(basic& obj)
{
    cout << "Prefix decrement operator" << endl;
    for(int i = 0; i < obj.x; i++)
        for(int j = 0; j < obj.y; j++)
            --obj.p[i][j];
    return obj;
}

//постфиксная версия возвращает значение до инкремента
const basic operator--(basic& obj, int)
{
    basic temp;
    temp = obj;
    cout << "Postfix decrement operator" << endl;
    for(int i = 0; i < obj.x; i++)
        for(int j = 0; j < obj.y; j++)
            --obj.p[i][j];
    return temp;
}

ostream& operator<<(ostream& s, basic& obj)
{
    s << "Operator <<" << endl;
    s << "Matrix size:" << endl;
    s << "X : " << obj.x << endl;
    s << "Y : " << obj.y << endl;
    s << "Matrix elements are:" << endl;
    for(int i = 0; i < obj.x; i++)
        for(int j = 0; j < obj.y; j++)
            s << "a[" << i << "][" << j << "]"
              << " = " << obj.p[i][j] << endl;
    return s;
}

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
    //пример для оператора <<
    /*basic obj2(2, 1), obj21;
    double d = 8.56;
    obj2.set_object();
    obj2.show_all();
    obj21 = d + obj2 + d;
    obj21.show_all();
    cout << obj21;*/

    //пример для дружественных операторов декремента (--)
    /*basic obj111(1, 2), obj222;
    obj111.set_object();
    cout << "obj111" << endl << obj111;
    obj222 = --obj111;
    cout << "obj111" << endl << obj111;
    cout << "obj222" << endl << obj222;
    obj222 = obj111--;
    cout << "obj111" << endl << obj111;
    cout << "obj222" << endl << obj222;*/

    //пример для дружественного оператора >
    /*basic obj123(1, 2), obj321(2, 1);
    double d1, d2;

    obj123.set_object();
    cout << obj123;
    cout << "Enter value (double): ";
    cin >> d1;
    if(obj123 > d1)
        cout << "obj123 > d1" << endl;
    else
        cout << "obj123 <= d1" << endl;

    obj321.set_object();
    cout << obj321;
    cout << "Enter value (double): ";
    cin >> d2;
    if(d2 > obj321)
        cout << "d2 > obj321" << endl;
    else
        cout << "d2 <= obj321" << endl;*/

    //пример для локальных операторов инкремента (++)
    /*basic obj333(1, 2), obj444;
    obj333.set_object();
    cout << "obj333" << endl << obj333;
    obj444 = ++obj333;
    cout << "obj333" << endl << obj333;
    cout << "obj444" << endl << obj444;
    obj444 = obj333++;
    cout << "obj333" << endl << obj333;
    cout << "obj444" << endl << obj444;*/

    //пример для локального оператора <
    /*basic obj555(1, 2), obj666(2, 1);
    obj555.set_object();
    cout << obj555;
    obj666.set_object();
    cout << obj666;

    if(obj555 < obj666)
        cout << "obj555 < obj666" << endl;
    else
        cout << "obj555 >= obj666" << endl;*/

    //пример для оператора +(локального)
    /*basic objl_1(2, 1), objl_2(1, 2), obj_sum;
    objl_1.set_object();
    cout << objl_1;
    objl_2.set_object();
    cout << objl_2;
    obj_sum = objl_1 + objl_2;
    cout << obj_sum << endl;*/

    //пример для оператора ()
    basic obj1_3;
    obj1_3(1, 2, 3);
    // cout<<*obj1_3<<endl;
    // delete obj1_3;

    //пример для оператора индексирования []
    /*basic cobj(1,3);
    cobj.set_object();
    cout<<cobj[0][2]<<endl;
    cout<<cobj[3][1]<<endl;
    cout<<cobj[-1][1]<<endl;*/

    return 0;
}
