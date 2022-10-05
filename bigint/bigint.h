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
	BigInt() {
		this->num.push_back(0);
	};
	BigInt(int num) {
		while (num % 10 == 0) {
			this->num.push_back((num % 10));
			num /= 10;
		}
		this->num.push_back((num % 10));
	}
	BigInt(std::string str) { // бросать исключение std::invalid_argument при ошибке
		for (int i{ (int)str.size() - 1 } ; i >= 0; --i)
			this->num.push_back(str[i] - '0');
	}
	BigInt(const BigInt& num) {
		this->num = num.num;
	}
	~BigInt() {
		//Empty?
	}

		BigInt& operator=(const BigInt& num) {  //возможно присваивание самому себе!
		if (*this == num) return *this;
		this->num = num.num; return *this;
	}

	BigInt operator~() const {

	}

	BigInt& operator++() { //++i

	}
	const BigInt operator++(int) const { //i++

	}
	BigInt& operator--() {

	}
	const BigInt operator--(int) const {

	}

	BigInt& operator+=(const BigInt&) { //a = a + b return a

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
	for (char i = d.num.size() - 1; i >= 0; i--)
	//for (char i : d.num)
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
