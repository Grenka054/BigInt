#include <iostream>
#include "bigint.h"

int main()
{
    using namespace std;
    BigInt nullnum{ };
    BigInt fivehundnum{500};
    cout << fivehundnum.num;
}
