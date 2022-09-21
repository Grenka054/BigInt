#include <iostream>
#include "bigint.h"

int main()
{
    using namespace std;
    BigInt nullnum{ };
    cout << nullnum.num << endl;
    BigInt fivehundnum{500};
    BigInt eighthundnum{ "800" };
    BigInt eighthundnum2 (eighthundnum);
    nullnum = nullnum;
    cout << nullnum.num << endl;
    nullnum = fivehundnum;
    cout << nullnum.num << endl;
    cout << fivehundnum.num << endl;
    cout << eighthundnum.num << endl;
    cout << eighthundnum2.num << endl;
}
