#include "BigInt.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <windows.h>
#include <cassert>

using namespace std;

constexpr int CNT_OF_REPEATS_BENCHMARKING = 50000;
constexpr int CNT_OF_ONE_BLOCK_BENCHMARKING = 1000;

std::vector<char> oper_lst{ '+', '-', '*', '/', '%', '|', '&', '^' };

std::vector<int> sign_lst{ 1, -1 };
#define LONG_LONG_SUPPORT true

#define CALCULATE
#define DEBUG_LOG

bool exsistOper(char oper) {
	return std::find(oper_lst.begin(), oper_lst.end(), oper) != oper_lst.end();
}

bool exsistSign(int sign) {
	return std::find(sign_lst.begin(), sign_lst.end(), sign) != sign_lst.end();
}

#ifdef LONG_LONG_SUPPORT
#define CHECKEXPR(a,b,c) test_twoL(a,b,c)
#else
#define CHECKEXPR(a,b,c) test_twoI(a,b,c)
#endif
#ifdef DEBUG_LOG
#define LOG(a){a;}
#else
#define LOG(a){0;};
#endif
#ifdef CALCULATE
#define TEST_RUN
#include <sys/timeb.h>
typedef _timeb sys_time_t;
inline long long time_to_msec(const sys_time_t& t) {
	return t.time * 1000LL + t.millitm;
}

sys_time_t T_st, T_end;
vector<long long> timers;
#endif

int generateBIGint();
int generateSMALLint();

bool test_twoL(BigInt&, char&, BigInt&);
bool test_twoI(BigInt&, char&, BigInt&);
bool test_two(string);


#define StreamRead
void test_extra()
{
	BigInt temp;
	bool exceptionThrown = false;
#ifdef LONG_LONG_SUPPORT
	long long a, b, res;
#else
	int a, b, res;
#endif // LONG_LONG_SUPPORT

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
	res = a | b;
	temp = BigInt(a) | BigInt(b);
	assert(temp == BigInt(res));
	cout << "Done!" << endl;
	cout << "* operations:" << endl;
	assert((BigInt)8166 * (BigInt)0 == BigInt(8166 * 0));
	assert((BigInt)0 * (BigInt)0 == BigInt(0 * 0));
	assert((BigInt)0 * (BigInt)24 == BigInt(0 * 24));
	assert((BigInt)-1079200180 * (BigInt)-840372435 == (BigInt)906930083119038300);
	assert((BigInt)-840372435 * (BigInt)-1079200180 == (BigInt)906930083119038300);
	BigInt b57{ -57 };
	b57 *= (BigInt)-121;
	assert(b57 == (BigInt)6897);
	assert((BigInt)57 * (BigInt)121 == (BigInt)6897);
	assert((BigInt)57 * (BigInt)-121 == (BigInt)-6897);
	assert((BigInt)-1210 * (BigInt)5700 == (BigInt)-6897000);
	assert(string(BigInt("-125726606") * BigInt("2056734911")) == "-258586299801742066");
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
#ifdef LONG_LONG_SUPPORT
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
}

int main() {
	test_extra();
	BigInt::set_grid_size(32);
	std::cout << "Using long long to check: " << (LONG_LONG_SUPPORT ? "True" : "False") << endl;
	std::cout << "Number of operation calls: " << CNT_OF_REPEATS_BENCHMARKING << endl;
	std::cout << "Number of operation calls in block: " << CNT_OF_ONE_BLOCK_BENCHMARKING << endl;
	std::cout << "Operations to be checked: ";
	for (auto oper : oper_lst)
		std::cout << oper << ' ';
	std::cout << endl;
	std::cout << "Checking using positive numbers: " << (exsistSign(1) ? "True" : "False") << endl;
	std::cout << "Checking using negative numbers: " << (exsistSign(-1) ? "True" : "False") << endl;
	std::cout << endl << endl;
	std::cout << "Press enter to start" << endl;
	cin.get();

#ifdef CALCULATE
	if (CNT_OF_ONE_BLOCK_BENCHMARKING > CNT_OF_REPEATS_BENCHMARKING) {
		throw invalid_argument("WRONG ATRIBUTES");
	}

	int numbers_types_count = 4 - (LONG_LONG_SUPPORT ? 0 : 3);

	srand(time(NULL));

	bool is_correct = true;

	size_t test_num = 0;
	do {
		_ftime(&T_st);
		for (size_t block_num = 0; block_num <= CNT_OF_ONE_BLOCK_BENCHMARKING && is_correct; block_num++) {
			if (test_num == CNT_OF_REPEATS_BENCHMARKING) {
				is_correct = false;
				break;
			}

			int fstNum, sndNum;
			LOG(std::cout << "(" << test_num << ") ";)

				stringstream expr_s;

			char oper = oper_lst[rand() % oper_lst.size()];

			switch (rand() % numbers_types_count)
			{
			case(0):
				fstNum = generateSMALLint();
				sndNum = generateSMALLint();
				break;
			case(1):
				fstNum = generateBIGint();
				sndNum = generateSMALLint();
				break;
			case(2):
				fstNum = generateBIGint();
				sndNum = generateBIGint();
				break;
			case(3):
				sndNum = generateBIGint();
				fstNum = generateSMALLint();
				break;
			}

			if ((oper == '/') || (oper == '&')) sndNum += 1;

			//make negative
			fstNum *= sign_lst[rand() % sign_lst.size()];
			sndNum *= sign_lst[rand() % sign_lst.size()];

			expr_s << fstNum << ' ' << oper << ' ' << sndNum;

			try { is_correct = test_two(expr_s.str()); }
			catch (...) {
				std::cout << "\tAn error occurred in the test. Continue testing" << endl;
			}
			test_num++;
		};
		_ftime(&T_end);
		timers.push_back(time_to_msec(T_end) - time_to_msec(T_st));
	} while (is_correct);


	long long total_time = 0;
	for (auto i : timers)
		total_time += i;

	std::cout << "Operations completed: " << test_num << endl;
	std::cout << total_time << "ms total work time (" << CNT_OF_REPEATS_BENCHMARKING << " cycles)" << endl;
	std::cout << total_time / timers.size() << "ms (" << CNT_OF_ONE_BLOCK_BENCHMARKING << " cycles)" << endl;
	std::cout << (double)total_time / timers.size() / CNT_OF_ONE_BLOCK_BENCHMARKING << "ms on 1 cycle" << endl;

#endif
	return 0;
}

bool test_two(string expr) {
	LOG(std::cout << "TESTING this: " << expr;)

		char* pos = strtok((char*)expr.c_str(), " ");
	BigInt* a = new BigInt((string(pos)));
	pos = strtok(NULL, " ");
	char oper = *pos;
	pos = strtok(NULL, " ");
	BigInt* b = new BigInt((string(pos)));

	bool is_correct = CHECKEXPR(*a, oper, *b);

	delete a;
	delete b;
	return is_correct;
}

bool test_twoL(BigInt& a, char& oper, BigInt& b) {

	BigInt my_ans{ 0 };
	long long correct_ans{ 0 };

	bool is_correct = false;

	switch (oper)
	{
	case('+'):
		correct_ans = (long long)a + (long long)b;
		my_ans = a + b;
		break;
	case('-'):
		correct_ans = (long long)a - (long long)b;
		my_ans = a - b;
		break;
	case('*'):
		correct_ans = (long long)a * (long long)b;
		my_ans = a * b;
		break;
	case('/'):
		correct_ans = (long long)a / (long long)b;
		my_ans = a / b;
		break;
	case('%'):
		correct_ans = (long long)a % (long long)b;
		my_ans = a % b;
		break;
	case('|'):
		correct_ans = (long long)a | (long long)b;
		my_ans = a | b;
		break;
	case('&'):
		correct_ans = (long long)a & (long long)b;
		my_ans = a & b;
		break;
	case('^'):
		correct_ans = (long long)a ^ (long long)b;
		my_ans = a ^ b;
		break;
	}

	is_correct = (BigInt)correct_ans == my_ans;
	LOG(std::cout << " = [" << my_ans << "] / {" << correct_ans << "} ";
	std::cout << (is_correct ? "CORRECT" : "!!WRONG!!");
	std::cout << endl;)
		return is_correct;
}

bool test_twoI(BigInt& a, char& oper, BigInt& b) {

	BigInt my_ans{ 0 };
	int correct_ans{ 0 };

	bool is_correct = false;

	switch (oper)
	{
	case('+'):
		correct_ans = (int)a + (int)b;
		my_ans = a + b;
		break;
	case('-'):
		correct_ans = (int)a - (int)b;
		my_ans = a - b;
		break;
	case('*'):
		correct_ans = (int)a * (int)b;
		my_ans = a * b;
		break;
	case('/'):
		correct_ans = (int)a / (int)b;
		my_ans = a / b;
		break;
	case('%'):
		correct_ans = (int)a % (int)b;
		my_ans = a % b;
		break;
	case('|'):
		correct_ans = (int)a | (int)b;
		my_ans = a | b;
		break;
	case('&'):
		correct_ans = (int)a & (int)b;
		my_ans = a & b;
		break;
	case('^'):
		correct_ans = (int)a ^ (int)b;
		my_ans = a ^ b;
		break;
	}

	is_correct = (BigInt)correct_ans == my_ans;
	LOG(std::cout << " = [" << my_ans << "] / {" << correct_ans << "} ";
	std::cout << (is_correct ? "CORRECT" : "!!WRONG!!");
	std::cout << endl;)
		return is_correct;
}


int generateBIGint() {
	return ((int)rand() + ((int)rand() << 16));
}

int generateSMALLint() {
	return ((int)rand());
}