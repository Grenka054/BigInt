#include <iostream>
#include "bigint.h"

int main()
{
	using namespace std;
	BigInt nullnum{ };
	cout << nullnum << endl;
	BigInt fivehundnum{ 500 };
	BigInt eighthundnum{ "-800" };
	BigInt eighthundnum2(eighthundnum);
	nullnum = nullnum;
	cout << "nullnum " << nullnum << endl; //0
	nullnum = fivehundnum;
	cout << "nullnum " << nullnum << endl; //0
	cout << "fivehundnum " << fivehundnum << endl; //500
	cout << "eighthundnum " << eighthundnum << endl; //-800
	cout << "eighthundnum2 " << eighthundnum2 << endl; //-800
	++eighthundnum2;
	cout << "eighthundnum2++ " << eighthundnum2 << endl; //-799
	++eighthundnum2;
	cout << "eighthundnum2++++ " << eighthundnum2 << endl; //-798
	cout << "eighthundnum " << eighthundnum << endl; //-800
	++fivehundnum;
	cout << "fivehundnum++ " << fivehundnum << endl; //501
	++fivehundnum;
	cout << "fivehundnum++++ " << fivehundnum << endl; //502
	BigInt bignum{ "-254000000000000900" };
	cout << bignum++ << "   " << bignum << endl;
	--bignum;
	cout << bignum << std::endl;
	BigInt decnum{ 10 };
	cout << decnum-- << "  " << decnum << endl;
	BigInt b999_1{ 999 }, b999_2{ 999 }, b1{1};
	cout << b999_1 << " += " << b999_2 << " = ";
	b999_1 += b999_2;
	cout << b999_1 << endl;
	cout << b1 << " += " << b999_2 << " = ";
	b1 += b999_2;
	cout << b1 << endl;
	b1 += b999_2;
	cout << b1 << endl;
}
