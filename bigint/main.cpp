#include <iostream>
#include "bigint.h"

int main()
{
    using namespace std;
    BigInt nullnum{ };
    cout << nullnum << endl;
    BigInt fivehundnum{500};
    BigInt eighthundnum{ "-800" };
    BigInt eighthundnum2 (eighthundnum);
    nullnum = nullnum;
    cout << nullnum << endl; //0
    nullnum = fivehundnum;
    cout << nullnum << endl; //0
    cout << fivehundnum << endl; //500
    cout << "eighthundnum " << eighthundnum << endl; //800
    cout << eighthundnum2 << endl; //800
}
