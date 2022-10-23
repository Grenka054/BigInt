#include <iostream>
#include <cassert>
#include "bigint.h"

int main()
{
	using namespace std;
	assert((BigInt)-132 / (BigInt)18 == (BigInt)-7);
	assert((BigInt)132 / (BigInt)7 == (BigInt)18);
	bool exceptionThrown = false;
	try { (BigInt)132 / (BigInt)0; } catch (overflow_error&) { exceptionThrown = true; }
	assert(exceptionThrown);
	BigInt b57{ -57 };
	b57 *= (BigInt)-121;
	assert(b57 == (BigInt)6897);
	assert((BigInt)57 * (BigInt)121 == (BigInt)6897);
	assert((BigInt)57 * (BigInt)-121 == (BigInt)-6897);
	assert((BigInt)-1210 * (BigInt)5700 == (BigInt)-6897000);
	BigInt b0{ };
	assert(b0 == (BigInt)0);
	BigInt b500{ 500 };
	BigInt m500{ -500 };
	BigInt m800{ "-800" };
	BigInt m800_2(m800);
	b0 = b0;
	assert(b0 == (BigInt)"0");
	b0 = b500;
	assert(b0 == (BigInt)"500");
	assert(m500 == (BigInt)"-500");
	assert(b500 == (BigInt)"500");
	assert(m800 == (BigInt)"-800");
	assert(m800_2 == (BigInt)"-800");
	++m800_2;
	assert(m800_2 == (BigInt)"-799");
	++m800_2;
	assert(m800_2 == (BigInt)"-798");
	assert(m800 == (BigInt)"-800");
	++b500;
	assert(b500 == (BigInt)"501");
	++b500;
	assert(b500 == (BigInt)"502");
	BigInt bignum{ "-254000000000000900" };
	assert(bignum++ == (BigInt)"-254000000000000900");
	assert(bignum == (BigInt)"-254000000000000899");
	BigInt temp = bignum++;
	assert(bignum == temp + (BigInt)"1");
	--bignum;
	assert(bignum == (BigInt)"-254000000000000899");
	BigInt d10{ 10 };
	cout << d10-- << "  " << d10 << endl;
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
	assert(int((BigInt)"20") == 20);
	assert(int((BigInt)"-205478") == -205478);
	assert(string((BigInt)"20") == "20");
	assert(string((BigInt)"-205478") == "-205478");

}
