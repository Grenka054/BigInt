#pragma once
#include <cstring>
#include <string>
#include <iostream>

class BigInt {

public:
	std::string num;
	BigInt() {
		this->num = "0";
	};
	BigInt(int num) {
		this->num = std::to_string(num);
	}
	BigInt(std::string str) { // бросать исключение std::invalid_argument при ошибке
		this->num = str;
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

BigInt operator+(const BigInt&, const BigInt&);  //with +=, copy BigInt
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i);
