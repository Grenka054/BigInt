#include <iostream>
#include <cassert>
#include "bigint.h"
#include "TestEgor.cpp"

//#define StreamRead
//#define LLSupport
int main()
{
	using namespace std;
	BigInt temp;
	bool exceptionThrown = false;
#ifdef LLSupport
	long long a, b, res;
#else
	int a, b, res;
#endif // LLSupport

#ifdef StreamRead
	cout << "Enter a BigInt:  ";
	cin >> temp;
	cout << "You have entered a " << string(temp) << endl;
#endif // StreamRead
	cout << "Bitwise operations:" << endl;
	a = 780505, b = 98;
	temp = BigInt(a) | BigInt(b); // 18 sec
	assert(temp == BigInt(a | b));
	a = 100, b = 60;
	temp = BigInt(a) | BigInt(b);
	res = a | b;
	assert(temp == BigInt(res));
	temp = BigInt(a) & BigInt(b);
	res = a & b;
	assert(temp == BigInt(res));
	temp = BigInt(a) ^ BigInt(b);
	res = a ^ b;
	assert(temp == BigInt(res));
	a = 0, b = 0;
	res = a | b;
	temp = BigInt(a) | BigInt(b);
	assert(temp == BigInt(res));
	temp = BigInt(a) & BigInt(b);
	res = a & b;
	assert(temp == BigInt(res));
	temp = BigInt(a) ^ BigInt(b);
	res = a ^ b;
	assert(temp == BigInt(res));
	a = -2, b = 1;
	try { temp = BigInt(a) | BigInt(b); }
	catch (std::invalid_argument) { exceptionThrown = true; }
	assert(temp == BigInt(res));
	cout << "Done!" << endl;
	cout << "/ operations:" << endl;
	assert((BigInt)0 / (BigInt)18 == (BigInt)0);
	assert((BigInt)-132 / (BigInt)18 == (BigInt)-7);
	assert((BigInt)132 / (BigInt)7 == (BigInt)18);
	try { (BigInt)132 / (BigInt)0; }
	catch (overflow_error&) { exceptionThrown = true; }
	assert(exceptionThrown);
	exceptionThrown = false;
	cout << "Done!" << endl;
	cout << "% operations:" << endl;
	assert((BigInt)50 % (BigInt)-6 == (BigInt)2);
	assert((BigInt)-50 % (BigInt)6 == (BigInt)-2);
	assert((BigInt)-50 % (BigInt)-6 == (BigInt)(-50 % -6));
	assert((BigInt)50 % (BigInt)6 == (BigInt)(50 % 6));
	assert((BigInt)-1327992 % (BigInt)-1992 == (BigInt)(-1320));
	assert((BigInt)-12 % (BigInt)-3 == (BigInt)(0));
	assert((BigInt)-1220310080 % (BigInt)-44 == (BigInt)(0));
	assert((BigInt)26852 % (BigInt)1427506810 == (BigInt)(26852 % 1427506810));
	cout << "Done!" << endl;
	cout << "* operations:" << endl;
	assert((BigInt)-1079200180 * (BigInt)-840372435 == (BigInt)906930083119038300);
	assert((BigInt) -840372435 * (BigInt) - 1079200180 == (BigInt)906930083119038300);
	BigInt b57{ -57 };
	b57 *= (BigInt)-121;
	assert(b57 == (BigInt)6897);
	assert((BigInt)57 * (BigInt)121 == (BigInt)6897);
	assert((BigInt)57 * (BigInt)-121 == (BigInt)-6897);
	assert((BigInt)-1210 * (BigInt)5700 == (BigInt)-6897000);
	assert(string(BigInt("-125726606") * BigInt("2056734911")) == "-258586299801742066");
	cout << "Done!" << endl;
	cout << "Constructors:" << endl;
	BigInt b0{ };
	assert(b0 == (BigInt)0);
	BigInt b500{ 500 };
	BigInt m500{ -500 };
	BigInt m800{ "-800" };
	BigInt m800_2(m800);
	assert(m500 == (BigInt)"-500");
	assert(b500 == (BigInt)"500");
	assert(m800 == (BigInt)"-800");
	assert(m800_2 == (BigInt)"-800");
	cout << "Done!" << endl;
	cout << "Assignments:" << endl;
	b0 = b0;
	assert(b0 == (BigInt)"0");
	b0 = b500;
	cout << "Done!" << endl;
	cout << "++ operations:" << endl;
	assert(b0 == (BigInt)"500");
	++m800_2;
	assert(m800_2 == (BigInt)"-799");
	++m800_2;
	assert(m800_2 == (BigInt)"-798");
	assert(m800 == (BigInt)"-800");
	++b500;
	assert(b500 == (BigInt)"501");
	++b500;
	assert(b500 == (BigInt)"502");
	BigInt bigmnum{ "-254000000000000900000" };

	assert(bigmnum++ == (BigInt)"-254000000000000900000");
	assert(bigmnum == (BigInt)"-254000000000000899999");
	temp = bigmnum++;
	assert(bigmnum == temp + (BigInt)"1");
	--bigmnum;
	cout << "Done!" << endl;
	cout << "Conversion operations:" << endl;
	try { a = int(bigmnum); }
	catch (out_of_range&) { exceptionThrown = true; }
	assert(exceptionThrown);
	exceptionThrown = false;
	assert(int((BigInt)"20") == 20);
	assert(int((BigInt)"-205478") == -205478);
#ifdef LLSupport
	try { a = long long(bigmnum); }
	catch (out_of_range&) { exceptionThrown = true; }
	assert(exceptionThrown);
	assert(long long(BigInt("-25400000000000")) == -25400000000000);
	exceptionThrown = false;
#endif
	cout << "Done!" << endl;
	cout << "+/- operations:" << endl;
	assert(bigmnum == (BigInt)"-254000000000000899999");
	BigInt b999_1{ 999 }, b1{ 1 };
	b999_1 += (BigInt)999;
	assert(b999_1 == (BigInt)"1998");
	b1 += (BigInt)999;
	assert(b1 == (BigInt)"1000");
	b1 += (BigInt)999;
	assert(b1 == (BigInt)"1999");
	assert((BigInt)"1999" == (BigInt)"1999");
	assert((BigInt)"-1999" != (BigInt)"1999");

	b1 += (BigInt)"-8000";
	assert(b1 == (BigInt)"-6001");
	assert((BigInt)"159155568" + (BigInt)"250000534" == (BigInt)"409156102");
	assert((BigInt)"-159155568" + (BigInt)"250000534" == (BigInt)"90844966");
	assert((BigInt)"159155568" + (BigInt)"-250000534" == (BigInt)"-90844966");
	assert((BigInt)"-65416545413365116514" + (BigInt)"-31" == (BigInt)"-65416545413365116545");
	assert((BigInt)"159155568" - (BigInt)"-250000534" == (BigInt)"409156102");
	assert((BigInt)"-159155568" - (BigInt)"-250000534" == (BigInt)"90844966");
	assert((BigInt)"159155568" - (BigInt)"250000534" == (BigInt)"-90844966");
	assert((BigInt)"-65416545413365116514" - (BigInt)"31" == (BigInt)"-65416545413365116545");
	cout << "Done!" << endl;
	cout << "Relational operations:" << endl;
	assert((BigInt)2 < (BigInt)18);
	assert((BigInt)"1999" < (BigInt)"8000");
	assert(!((BigInt)"20" < (BigInt)"-1999"));
	assert(!((BigInt)"200000" < (BigInt)"-1999"));
	assert((BigInt)"-200000" < (BigInt)"-1999");
	assert(!((BigInt)"-200000" < (BigInt)"-99991999"));
	assert((BigInt)"-200000" < (BigInt)"0");
	assert(!((BigInt)"0" < (BigInt)"0"));

	assert((BigInt)2 > (BigInt)-18);
	assert((BigInt)"20" > (BigInt)"-1999");
	assert((BigInt)"200000" > (BigInt)"-1999");
	assert(!((BigInt)"-200000" > (BigInt)"-1999"));
	assert((BigInt)"-200000" > (BigInt)"-99991999");
	assert(!((BigInt)"-200000" > (BigInt)"0"));
	assert(!((BigInt)"0" > (BigInt)"0"));

	assert((BigInt)"-200000" <= (BigInt)"0");
	assert((BigInt)"0" <= (BigInt)"0");
	assert(!((BigInt)"-200000" >= (BigInt)"0"));
	assert((BigInt)"0" >= (BigInt)"0");
	assert(string((BigInt)"20") == "20");
	assert(string((BigInt)"-205478") == "-205478");
	cout << "Done!" << endl;
	return 0;
}
