#include "LeakDetector.hpp"
#include <iostream>
using namespace std;
class Err
{
public:
    Err(int n)
    {
        if (n == 0)
            throw 1000;//直接跳到catch的部分
        data = new int[n];
    }
    ~Err()
    {
        delete[] data;
    }
private:
    int *data;
};
int main()
{
    int *a=new int;
    int *b=new int;
    try
    {
        Err *e = new Err(0);
        delete e;
    }
    catch (int &ex)
    {
        cout << "Exception catch:  " << ex <<  endl;
    };
    return (0);
}


