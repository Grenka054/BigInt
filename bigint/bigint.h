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
		if (num < 0) this->negative = true;
		else this->negative = false;
		while (num / 10 != 0) {
			this->num.push_back((num % 10));
			num /= 10;
		}
		this->num.push_back((num % 10));
	}

	BigInt(std::string str) { // бросать исключение std::invalid_argument при ошибке
		this->negative = false;
		for (int i{ (int)str.size() - 1 }; i >= 0; --i) {
			if (str[i] - '0' <= 9 && str[i] - '0' >= 0)
				this->num.push_back(str[i] - '0');
			else if (str[i] == '-') this->negative = true;
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

	BigInt& operator=(const BigInt& num) {  //возможно присваивание самому себе!
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

	const BigInt operator++(int) { //i++ //const мешает справа
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

	const BigInt operator--(int) { //const мешает справа
		BigInt temp = *this;
		--(*this);
		return temp;
	}

	BigInt& operator+=(const BigInt& num) { //a = a + b return a
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
		return *this;
	}

	BigInt& operator*=(const BigInt&) {

	}

	BigInt& operator-=(const BigInt&) {

	}

	BigInt& operator/=(const BigInt&) {

	}

	BigInt& operator^=(const BigInt&) {

	}

	BigInt& operator%=(const BigInt&) {

	}

	BigInt& operator&=(const BigInt&) {

	}

	BigInt& operator|=(const BigInt&) {

	}

	BigInt operator+() const;  // unary + // *1
	BigInt operator-() const;  // unary - // * -1

	bool operator==(const BigInt& num) const {
		return (this->num == num.num);
	}
	bool operator!=(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;

	operator int() const;
	operator std::string() const;

	size_t size() const;  // size in bytes
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


std::ostream& operator<<(std::ostream& o, const BigInt& i);
