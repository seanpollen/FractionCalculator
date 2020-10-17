#include <stdio.h>
#include <string>
#include <iostream>
//SEAN POLLEN 17smp3@queensu.ca
using namespace std;

class Fraction {
public:
	//Constructos
	Fraction();
	Fraction(int);
	Fraction(int, int);
	//Getters and Setters
	int numerator() const;
	int denominator() const;
	void setValues(int, int);
	//The following functions need direct access to modify variables, therefore they are member functions
	Fraction operator++(void);
	Fraction operator++(int);
	Fraction operator+=(Fraction);

private:
	int numer; //variables are private because good form is the key to success
	int denom;
};

class FractionException { //standard error function
public:
	FractionException(const string&);
	string what() const;
private:
	string message;
};

//Function to find the greatest common denominator
int gcd(int, int);

//unary functions
Fraction operator-(const Fraction&);

//binary operators
Fraction operator+(const Fraction&, const Fraction&);
Fraction operator-(const Fraction&, const Fraction&);
Fraction operator*(const Fraction&, const Fraction&);
Fraction operator/(const Fraction&, const Fraction&);

//logic operations
bool operator>(const Fraction&, const Fraction&);
bool operator>=(const Fraction&, const Fraction&);
bool operator<(const Fraction&, const Fraction&);
bool operator<=(const Fraction&, const Fraction&);
bool operator==(const Fraction&, const Fraction&);
bool operator!=(const Fraction&, const Fraction&);

//IO OPERATORS
ostream& operator<<(ostream&, const Fraction&);
istream& operator>>(istream&, Fraction&);