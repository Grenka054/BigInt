#pragma once
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <ostream>
#include <algorithm>

class BigInt {

public:
	std::vector<char> num;
	bool negative;
	BigInt() {
		this->num.push_back(0);
		this->negative = false;
	}

	BigInt(int num) {
		this->negative = false;
		if (num < 0) this->negative = true;
		num = abs(num);
		while (num / 10 != 0) {
			this->num.push_back((num % 10));
			num /= 10;
		}
		this->num.push_back((num % 10));
	}

	BigInt(std::string str) { // ������� ���������� std::invalid_argument ��� ������
		this->negative = false;
		if (str[0] == '-') this->negative = true;
		for (int i{ (int)str.size() - 1 }; i >= 0; --i) {
			if (str[i] - '0' <= 9 && str[i] - '0' >= 0)
				this->num.push_back(str[i] - '0');
			else if (i == 0 && str[0] == '-') continue;
			else throw std::invalid_argument("String contains extra characters.");
		}
	}

	BigInt(const BigInt& num) {
		this->num = num.num;
		this->negative = num.negative;
	}

	~BigInt() {
		//Empty?
	}

	BigInt& operator=(const BigInt& num) {  //�������� ������������ ������ ����!
		if (*this == num) return *this;
		this->num = num.num;
		this->negative = num.negative;
		return *this;
	}

	BigInt operator~() const {

	}

	BigInt& operator++() { //++i
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
					++this->num[i + 1];
				}
				else break;
			}
		}
		return *this;
	}

	const BigInt operator++(int) { //i++ //const ������ ������
		BigInt temp = *this;
		++(*this);
		return temp;
	}

	BigInt& operator--() {
		this->negative = !this->negative;
		++(*this);
		this->negative = !this->negative;
		return *this;
	}

	const BigInt operator--(int) { //const ������ ������
		BigInt temp = *this;
		--(*this);
		return temp;
	}

	BigInt& operator+=(const BigInt& num) { //a = a + b return a
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
			const BigInt* min, * max;
			if (this->negative) {
				min = this;
				max = &num;
				//b-a
			}
			else {
				//a-=b
				*this -= num;
			}
		}
		return *this;
	}

	BigInt& operator*=(const BigInt& num) {

	}

	BigInt& operator-=(const BigInt& num) {
		if (this->negative == num.negative) {
			return *this += num;
		}
		//if ()
	}

	BigInt& operator/=(const BigInt& num) {

	}

	BigInt& operator^=(const BigInt&) {

	}

	BigInt& operator%=(const BigInt&) {

	}

	BigInt& operator&=(const BigInt&) {

	}

	BigInt& operator|=(const BigInt&) {

	}

	BigInt operator+() {  // unary + // *1
		this->negative = false;
	}

	BigInt operator-() {  // unary - // * -1
		this->negative = true;
	}

	bool operator==(const BigInt& num) const {
		return (this->num == num.num && this->negative == num.negative);
	}

	bool operator!=(const BigInt& num) const {
		return !(*this == num);
	}

	bool operator<(const BigInt& num) const {
		if (this->negative == num.negative) {
			if (this->num.size() == num.num.size())
				for (int i = num.num.size() - 1; i >= 0; i--) {
					if (this->num[i] > num.num[i])
						return false;
				}
			else return this->negative && this->num.size() > num.num.size();
		}
		if (this->negative) return true;
		return false;

	}

	bool operator>(const BigInt& num) const {
		if (this->negative == num.negative) {
			if (this->num.size() == num.num.size())
				for (int i = num.num.size() - 1; i >= 0; i--) {
					if (this->num[i] < num.num[i])
						return false;
				}
			else return this->negative && this->num.size() < num.num.size();
		}
		if (num.negative) return true;
		return false;
	}
	bool operator<=(const BigInt& num) const {
		return (*this < num || *this == num);
	}
	bool operator>=(const BigInt& num) const {
		return (*this > num || *this == num);
	}

	operator int() const {
		int res = 0;
		for (size_t i = 0; i < this->num.size(); i++)
		{
			res += this->num[i] * int(pow(10, i));
		}
		if (this->negative) res *= -1;
		return res;
	}
	operator std::string() const {
		std::string res = "";
		if (this->negative) res = "-";
		for (int i = this->num.size() - 1; i >= 0; i--)
		{
			res += this->num[i] + '0';
		}
		return res;
	}

	size_t size() const { // size in bytes
		return this->num.size() + sizeof(this->negative);
	}
};

std::ostream& operator<<(std::ostream& os, const BigInt& d) {
	if (d.negative) std::cout << "-";
	for (char i = d.num.size() - 1; i >= 0; i--)
		std::cout << +d.num[i];
	return os;
}

BigInt operator+(const BigInt&, const BigInt&);  //with +=, copy BigInt
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);
