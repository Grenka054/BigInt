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
	BigInt(std::string); // throw std::invalid_argument
	BigInt(const BigInt&);
	~BigInt();
	/* assignment operator */
	
	BigInt& operator=(const BigInt&);  //�������� ������������ ������ ����!

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
	BigInt& operator%=(const BigInt&); // throw
	BigInt& operator^=(const BigInt&);
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

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

	static void set_grid_size(long long size);

	static long long get_grid_size();

private:
	std::vector<char> num;
	bool negative;
	static long long BIT_GRID_SIZE;
};

/* operations */
BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i);
std::istream& operator>>(std::istream& o, BigInt& i);

