#include "BigInt.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <ostream>
#include <cmath>

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
	this->num = num.num;
	this->negative = num.negative;
}

BigInt::~BigInt() {
	//Empty? // !
}

BigInt& BigInt::operator=(const BigInt& num) {
	if (*this == num) return *this;
	this->num = num.num;
	this->negative = num.negative;
	return *this;
}

BigInt BigInt::operator~() const {
	return *this; // bitwise NOT !
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

const BigInt BigInt::operator--(int) const { //const мешает справа
	BigInt temp = *this;
	--(const_cast<BigInt&>(*this));
	return temp;
}

BigInt& BigInt::operator+=(const BigInt& num) { //a = a + b return a
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
		{
			this->num[i] = max.num[i] - min.num[i];
		}
		for (size_t i = 0; i < max.num.size() - 1; i++)
		{
			if (this->num[i] < 0) {
				this->num[i] += 10;
				--this->num[i + 1];
			}
		}
		for (int i = max.num.size() - 1; i >= 0; i--)
			if (this->num[i] == 0)
				this->num.pop_back();
			else break;
		if ((*this).abs() == (BigInt)0) this->negative = false;
	}
	return *this;
}

BigInt& BigInt::operator*=(const BigInt& num) {
	BigInt res{ 0 };
	for (size_t i = 0; i < this->num.size(); i++)
	{
		BigInt temp{ };
		temp.num.clear();
		int tens = 0;
		for (size_t n = 0; n < i; n++)
			temp.num.push_back(0);
		for (size_t j = 0; j < num.num.size(); j++)
		{
			int product = this->num[i] * num.num[j];
			temp.num.push_back(tens + product % 10);
			tens = product / 10;
		}
		if (tens) temp.num.push_back(tens);
		res += temp;
		temp.num.clear();
	}
	res.negative = this->negative ^ num.negative;
	*this = res;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& num) {
	return *this += -num;
}

BigInt& BigInt::operator/=(const BigInt& num) {
	if (num == (BigInt)0) throw std::overflow_error("Divide by zero exception");

	BigInt dividend = this->abs(), divisor = num.abs(), res{};
	for (BigInt i = dividend - divisor; !i.negative; i -= divisor)
		++res;
	res.negative = this->negative ^ num.negative;
	*this = res;
	return *this;
}

BigInt& BigInt::operator^=(const BigInt& num) {
	return *this; // !
}

BigInt& BigInt::operator%=(const BigInt& num) {
	return *this -= *this / num;
}

BigInt& BigInt::operator&=(const BigInt& num) {
	return *this; // !
}

BigInt& BigInt::operator|=(const BigInt& num) {
	return *this; // !
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
	if (this->negative == num.negative) {
		if (this->num.size() == num.num.size())
			for (int i = num.num.size() - 1; i >= 0; i--) {
				if (this->num[i] > num.num[i])
					return false;
				if (this->num[i] < num.num[i])
					return true;
			}
		else return (this->negative && this->num.size() > num.num.size()) ||
			(!this->negative && this->num.size() < num.num.size());
	}
	if (this->negative) return true;
	return false;

}

bool BigInt::operator>(const BigInt& num) const {
	if (this->negative == num.negative) {
		if (this->num.size() == num.num.size())
			for (int i = num.num.size() - 1; i >= 0; i--) {
				if (this->num[i] < num.num[i])
					return false;
				if (this->num[i] > num.num[i])
					return true;
			}
		else return (this->negative && this->num.size() < num.num.size()) ||
			(!this->negative && this->num.size() > num.num.size());
	}
	if (num.negative) return true;
	return false;
}

bool BigInt::operator<=(const BigInt& num) const {
	return (*this < num || *this == num);
}

bool BigInt::operator>=(const BigInt& num) const {
	return (*this > num || *this == num);
}

BigInt::operator int() const {
	int res = 0;
	for (size_t i = 0; i < this->num.size(); i++)
	{
		res += this->num[i] * int(pow(10, i));
	}
	if (this->negative) res *= -1;
	return res;
}

BigInt::operator std::string() const {
	std::string res = "";
	if (this->negative) res = "-";
	for (int i = this->num.size() - 1; i >= 0; i--)
	{
		res += this->num[i] + '0';
	}
	return res;
}

size_t BigInt::size() const { // size in bytes
	return this->num.size() + sizeof(this->negative);
}

BigInt BigInt::abs() const {
	BigInt res = *this; res.negative = false;
	return res;
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
	if (i.get_negative()) std::cout << "-";
	for (char j = i.get_num().size() - 1; j >= 0; j--)
		std::cout << +i.get_num()[j];
	return o;
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
