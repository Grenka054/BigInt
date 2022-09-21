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
	BigInt(const BigInt&) {

	}
	~BigInt() {
		
	}

	BigInt& operator_assign(const BigInt&) {  //возможно присваивание самому себе!

	}

	BigInt operator_neg() const {

	}

	BigInt& operator_inc() {

	}
	const BigInt operator_inc(int) const {

	}
	BigInt& operator_dec() {

	}
	const BigInt operator_dec(int) const {

	}

	BigInt& operator_plus_assign(const BigInt&) {

	}
	BigInt& operator_product_assign(const BigInt&) {

	}
	BigInt& operator_minus_assign(const BigInt&) {

	}
	BigInt& operator_div_assign(const BigInt&) {

	}
	BigInt& operator_xor_assign(const BigInt&) {

	}
	BigInt& operator_mod_assign(const BigInt&) {

	}
	BigInt& operator_and1_assign(const BigInt&) {

	}
	BigInt& operator_or1_assign(const BigInt&) {

	}

	BigInt operator+() const;  // unary +
	BigInt operator-() const;  // unary -

	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;

	operator int() const;
	operator std::string() const;

	size_t size() const;  // size in bytes
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i);
