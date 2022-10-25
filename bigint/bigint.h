#pragma once
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <ostream>
#include <algorithm>
#include <cmath>

class BigInt {
public:
	/* constructors */
	BigInt();
	BigInt(int);
	BigInt(long long);
	BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
	BigInt(const BigInt&);

	~BigInt();
	/* assignment operator */
	BigInt& operator=(const BigInt&);  //возможно присваивание самому себе!

	/* bitwise NOT */
	BigInt operator~() const;

	/* increments and decrements */
	BigInt& operator++();
	const BigInt operator++(int) const;
	BigInt& operator--();
	const BigInt operator--(int) const;

	/* operational assignments */
	BigInt& operator+=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator/=(const BigInt&); // throw
	BigInt& operator^=(const BigInt&); // throw
	BigInt& operator%=(const BigInt&); // throw
	BigInt& operator&=(const BigInt&); // throw
	BigInt& operator|=(const BigInt&); // throw

	/* unary operations */
	BigInt operator+() const;  // unary +
	BigInt operator-() const;  // unary -

	/* relational operations */
	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;
	
	/* conversion operators */
	operator int() const;
	operator long long int() const;
	operator std::string() const;

	/* size in bytes */
	size_t size() const;

	/* absolute value */
	BigInt abs() const;
	
	/* Properties */ 
	std::vector<char> get_num() const;
	bool get_negative() const;

private:
	std::vector<char> num;
	bool negative;
};

/* operations */
BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&); // throw
BigInt operator^(const BigInt&, const BigInt&); // throw
BigInt operator%(const BigInt&, const BigInt&); // throw
BigInt operator&(const BigInt&, const BigInt&); // throw
BigInt operator|(const BigInt&, const BigInt&); // throw


std::ostream& operator<<(std::ostream& o, const BigInt& i);