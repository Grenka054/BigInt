#include "BigInt.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

long long BigInt::BIT_GRID_SIZE = 256;

void BigInt::set_grid_size(long long size) {
	BIT_GRID_SIZE = size;
}

long long BigInt::get_grid_size() {
	return BIT_GRID_SIZE;
}

std::vector<char> dec_to_bin(const BigInt& num) {
	BigInt temp = num.abs();
	static std::vector<BigInt> pows = { BigInt(1) };
	std::vector<char> bin(BigInt::get_grid_size());
	while (pows.size() < BigInt::get_grid_size()) {
		pows.push_back(pows[pows.size() - 1] * BigInt(2));
	}
	for (long long i = BigInt::get_grid_size() - 1; i >= 0; i--) //go to pows of 2
	{
		if (pows[i] > temp) {
			if (num.get_negative()) bin[i] = 1; //neg
			else bin[i] = 0;
		}
		else {
			if (num.get_negative()) bin[i] = 0; //neg
			else bin[i] = 1;
			temp -= BigInt(pows[i]);
		}
	}
	if (temp > BigInt(0)) std::cerr << "\nWARNING!" << std::string(num) << " does not fit on the " 
		<< BigInt::get_grid_size() << " bit grid.Possible data loss\n";
	if (num.get_negative()) {
		for (long long i = 0; i < pows.size(); i++)
		{
			if (bin[i])	bin[i] = 0;
			else { bin[i] = 1; break; }
		}
	}
	return bin;
}

BigInt bin_to_dec(std::vector<char> num) {
	bool negatvie = false;
	if (num[num.size() - 1] == 1) {
		negatvie = true;
		//-1
		for (long long i = 0; i < num.size(); i++)
		{
			if (num[i]) { num[i] = 0; break; }
			else num[i] = 1;
		}
		//neg
		for (long long i = num.size() - 1; i >= 0; i--)
		{
			if (num[i]) num[i] = 0;
			else num[i] = 1;
		}
	}
	BigInt b_int{ num[0] }, pow{ 1 };
	for (size_t i = 1; i < num.size(); i++)
	{
		pow *= BigInt(2);
		if (num[i]) b_int += pow;
	}
	if (negatvie) b_int *= BigInt(-1);
	return b_int;
}

std::vector<char> BigInt::get_num() const {
	return this->num;
}

bool BigInt::get_negative() const {
	return this->negative;
}

BigInt::BigInt() {
	this->num.push_back(0);
	this->negative = false;
}

BigInt::BigInt(int num) {
	*this = BigInt(long long(num));
}

BigInt::BigInt(long long num) {
	this->negative = false;
	if (num < 0) this->negative = true;
	num = std::abs(num);
	while (num / 10 != 0) {
		this->num.push_back((num % 10));
		num /= 10;
	}
	this->num.push_back((num % 10));
}

BigInt::BigInt(std::string str) {
	this->negative = false;
	if (str[0] == '-') this->negative = true;
	for (int i{ (int)str.size() - 1 }; i >= 0; --i) {
		if (str[i] - '0' <= 9 && str[i] - '0' >= 0)
			this->num.push_back(str[i] - '0');
		else if (i == 0 && (str[0] == '-' || str[0] == '+')) continue;
		else throw std::invalid_argument("String contains extra characters.");
	}
}

BigInt::BigInt(const BigInt& num) {
	this->num.clear();
	this->num = num.num;
	this->negative = num.negative;
}

BigInt::~BigInt() {
	this->num.clear();
}

BigInt& BigInt::operator=(const BigInt& num) {
	if (*this == num) return *this;
	this->num.clear();
	this->num = num.num;
	this->negative = num.negative;
	return *this;
}

BigInt BigInt::operator~() const {
	std::vector<char> thisBin{ dec_to_bin(*this) };
	for (size_t i = 0; i < thisBin.size(); i++)
		thisBin[i] = ~thisBin[i];
	BigInt res = bin_to_dec(thisBin);
	thisBin.clear();
	return res;
}

BigInt& BigInt::operator++() { //++i
	if (this->negative) {
		--this->num[0];
		for (size_t i = 0; i < this->num.size(); i++)
		{
			if (this->num[i] < 0) {
				this->num[i] = 9;
				--this->num[i + 1];
			}
			else {
				if (this->num[this->num.size() - 1] == 0)
					this->num.pop_back();
				break;
			}
		}
	}
	else {
		++this->num[0];
		for (size_t i = 0; i < this->num.size(); i++)
		{
			if (this->num[i] > 9) {
				this->num[i] = 0;
				if (this->num.size() < i + 1)
					this->num.push_back(0);
				if (i + 1 >= this->num.size())
					this->num.push_back(1);
				else
					++this->num[i + 1];
			}
			else break;
		}
	}
	return *this;
}

const BigInt BigInt::operator++(int) const { //i++
	BigInt temp = *this;
	++(const_cast<BigInt&>(*this));
	return temp;
}

BigInt& BigInt::operator--() {
	this->negative = !this->negative;
	++(*this);
	this->negative = !this->negative;
	return *this;
}

const BigInt BigInt::operator--(int) const {
	BigInt temp = *this;
	--(const_cast<BigInt&>(*this));
	return temp;
}

BigInt& BigInt::operator+=(const BigInt& num) {
	if (this->negative == num.negative) {
		int ten = 0, i;
		for (i = 0; i < this->num.size(); ++i) {
			char second = i < num.num.size() ? num.num[i] : 0;
			int sum = ten + second + this->num[i];
			ten = sum > 9 ? 1 : 0;
			sum %= 10;
			this->num[i] = sum;
		}
		for (; i < num.num.size(); ++i) {
			int sum = num.num[i] + ten;
			ten = sum > 9 ? 1 : 0;
			sum %= 10;
			this->num.push_back(sum);
		}
		if (ten)
			this->num.push_back(1);
	}
	else {
		BigInt min, max;
		if ((*this).abs() <= num.abs()) {
			min = (*this).abs();
			max = num.abs();
			if (this->negative) this->negative = false;
			else this->negative = true;
		}
		else {
			min = num.abs();
			max = (*this).abs();
			if (*this < num) this->negative = true;
			else this->negative = false;
		}
		if ((*this).abs() == num.abs()) this->negative = false;
		for (size_t i = min.num.size(); i < max.num.size(); i++) {
			min.num.push_back(0);
			if (i >= this->num.size()) this->num.push_back(0);
		}
		for (size_t i = 0; i < max.num.size(); i++)
			this->num[i] = max.num[i] - min.num[i];
		for (size_t i = 0; i < max.num.size() - 1; i++)
		{
			if (this->num[i] < 0) {
				this->num[i] += 10;
				--this->num[i + 1];
			}
		}
		for (long long i = max.num.size() - 1; i >= 1; i--)
			if (this->num[i] == 0)
				this->num.pop_back();
			else break;
		if ((*this).abs() == BigInt(0)) this->negative = false;
	}
	return *this;
}

BigInt& BigInt::operator*=(const BigInt& num) {
	BigInt res{ 0 };
	for (size_t i = 0; i < this->num.size(); i++)
	{
		if (!this->num[i]) continue;
		BigInt temp{ };
		temp.num.clear();
		int tens = 0;
		for (size_t n = 0; n < i; n++)
			temp.num.push_back(0);
		for (size_t j = 0; j < num.num.size(); j++)
		{
			int product = this->num[i] * num.num[j];
			product += tens;
			temp.num.push_back(product % 10);
			tens = product / 10;
		}
		if (tens) temp.num.push_back(tens);
		res += temp;
		temp.num.clear();
	}
	res.negative = (this->negative != num.negative);
	while (res.num.size() > 1) //000 -> 0
	{
		if (!res.num[res.num.size() - 1]) res.num.erase(res.num.begin());
		else break;
	}
	if(res.num == std::vector<char>{0}) res.negative = false;
	*this = res;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& num) {
	return *this += -num;
}

BigInt& BigInt::operator/=(const BigInt& num) {
	if (num == BigInt(0)) throw std::overflow_error("Divide by zero");
	if (this->abs() < num.abs()) { //faster
		*this = BigInt(0);
		return *this;
	}
	BigInt dividend = this->abs(), divisor = num.abs(), res{};
	long long null_amount = this->num.size() - num.num.size();
	BigInt pow10{ 1 };
	for (int i = 0; i < null_amount; i++)
		pow10 *= BigInt(10);
	while (divisor * pow10 > dividend) {
		--null_amount;
		pow10.num.erase(pow10.num.begin());
		if (pow10.num.empty()) break;
	}
	while (dividend >= divisor) {
		BigInt temp;
		for (BigInt x = 1; x <= BigInt(10); x++)
		{
			if (pow10 * divisor * x > dividend) {
				temp = (x - BigInt(1)) * pow10; break;
			}
		}
		dividend -= temp * divisor;
		res += temp;
		pow10.num.erase(pow10.num.begin());
		if (pow10.num.empty()) {
			pow10.num.push_back(0); break;
		}
	}
	res.negative = (this->negative != num.negative);
	if (res.num[res.num.size() - 1] == 0) res.negative = false;
	*this = res;
	return *this;
}

BigInt& BigInt::operator%=(const BigInt& num) {
	if (num == BigInt(0)) throw std::overflow_error("Divide by zero");
	bool neg = this->negative;
	if (this->abs() < num.abs()) return *this; //faster
	BigInt dividend = this->abs(), divisor = num.abs();
	long long null_amount = this->num.size() - num.num.size();
	BigInt pow10{ 1 };
	for (int i = 0; i < null_amount; i++)
		pow10 *= BigInt(10);
	while (divisor * pow10 > dividend) {
		--null_amount;
		pow10.num.erase(pow10.num.begin());
		if (pow10.num.empty()) break;
	}
	while (dividend >= divisor) {
		BigInt temp;
		for (BigInt x = 1; x <= BigInt(10); x++)
			if (pow10 * divisor * x > dividend) {
				temp = (x - BigInt(1)) * pow10; break;
			}
		dividend -= temp * divisor;
		pow10.num.erase(pow10.num.begin());
		if (pow10.num.empty()) {
			pow10.num.push_back(0); break;
		}
	}
	*this = dividend;

	if (!this->num[this->num.size() - 1]) this->negative = false;
	else this->negative = neg;
	return *this;
}

BigInt& BigInt::operator^=(const BigInt& num) {
	std::vector<char> thisBin{ dec_to_bin(*this) }, numBin{ dec_to_bin(num) };
	for (size_t i = 0; i < thisBin.size(); i++)
		thisBin[i] ^= numBin[i];
	*this = bin_to_dec(thisBin);
	thisBin.clear(); numBin.clear();
	return *this;
}

BigInt& BigInt::operator&=(const BigInt& num) {
	std::vector<char> thisBin{ dec_to_bin(*this) }, numBin{ dec_to_bin(num) };
	for (size_t i = 0; i < thisBin.size(); i++)
		thisBin[i] &= numBin[i];
	*this = bin_to_dec(thisBin);
	thisBin.clear(); numBin.clear();
	return *this;
}

BigInt& BigInt::operator|=(const BigInt& num) {
	std::vector<char> thisBin{ dec_to_bin(*this) }, numBin{ dec_to_bin(num) };
	for (size_t i = 0; i < thisBin.size(); i++)
		thisBin[i] |= numBin[i];
	*this = bin_to_dec(thisBin);
	thisBin.clear(); numBin.clear();
	return *this;
}

BigInt BigInt::operator+() const {  // unary + // *1
	BigInt temp = *this;
	return temp;
}

BigInt BigInt::operator-() const {  // unary - // * -1
	BigInt temp = *this;
	temp.negative = !temp.negative;
	return temp;
}

bool BigInt::operator==(const BigInt& num) const {
	return (this->num == num.num && this->negative == num.negative);
}

bool BigInt::operator!=(const BigInt& num) const {
	return !(*this == num);
}

bool BigInt::operator<(const BigInt& num) const {
	if (this->negative != num.negative) return this->negative; // different signes -> is left negative
	if (this->num.size() != num.num.size()) return (this->negative == this->num.size() > num.num.size());
	for (long long i = num.num.size() - 1; i >= 0; i--) {
		if (this->num[i] < num.num[i]) return !this->negative;
		if (this->num[i] > num.num[i]) return this->negative;
	}
	return false; // equal
}

bool BigInt::operator>(const BigInt& num) const {
	return(num < *this);
}

bool BigInt::operator<=(const BigInt& num) const {
	return (*this < num || *this == num);
}

bool BigInt::operator>=(const BigInt& num) const {
	return (*this > num || *this == num);
}

BigInt::operator int() const {
	if (*this > BigInt(INT32_MAX) || *this < BigInt(INT32_MIN))
		throw std::out_of_range("The number " + std::string(*this) + " is out of range int");
	int res = 0;
	for (size_t i = 0; i < this->num.size(); i++)
		res += this->num[i] * int(pow(10, i));
	if (this->negative) res *= -1;
	return res;
}

BigInt::operator long long int() const {
	if (*this > BigInt(INT64_MAX) || *this < BigInt(INT64_MIN))
		throw std::out_of_range("The number " + std::string(*this) + " is out of range long long int");
	long long res = 0;
	for (size_t i = 0; i < this->num.size(); i++)
		res += this->num[i] * long long(pow(10, i));
	if (this->negative) res *= -1;
	return res;
}

BigInt::operator std::string() const {
	std::string res = "";
	if (this->negative) res = "-";
	for (long long i = this->num.size() - 1; i >= 0; i--)
		res += this->num[i] + '0';
	return res;
}

size_t BigInt::size() const { // size in bytes
	return this->num.size() + sizeof(this->negative);
}

BigInt BigInt::abs() const {
	BigInt res = *this; res.negative = false;
	return res;
}

BigInt operator+(const BigInt& a, const BigInt& b) { //with +=, copy BigInt
	BigInt temp = a;
	return temp += b;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
	BigInt temp = a;
	return temp -= b;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
	BigInt temp = a;
	return temp *= b;
}

BigInt operator/(const BigInt& a, const BigInt& b) {
	BigInt temp = a;
	return temp /= b;
}

BigInt operator^(const BigInt& a, const BigInt& b) {
	BigInt temp = a;
	return temp ^= b;
}

BigInt operator%(const BigInt& a, const BigInt& b) {
	BigInt temp = a;
	return temp %= b;
}

BigInt operator&(const BigInt& a, const BigInt& b) {
	BigInt temp = a;
	return temp &= b;
}

BigInt operator|(const BigInt& a, const BigInt& b) {
	BigInt temp = a;
	return temp |= b;
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
	if (i.get_negative()) o << "-";
	for (long long j = i.get_num().size() - 1; j >= 0; j--)
		o << +i.get_num()[j];
	return o;
}

std::istream& operator>>(std::istream& o, BigInt& i) {
	std::string str;
	while (true) {
		o >> str;
		if (!str.compare("exit")) break;
		try { i = BigInt(str); break; }
		catch (std::invalid_argument) {
			std::cerr << "Error: String contains extra characters\n"
				"Enter \"exit\" to skip reading or try again:  ";
		}
	}
	return o;
}