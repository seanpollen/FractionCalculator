#include "fraction_17smp3.h"
//Sean Pollen - 17smp3@queensu.ca

//CONSTRUCTORS
Fraction::Fraction() : numer(0), denom(1) { }
Fraction::Fraction(int n) : numer(n), denom(1) { }
Fraction::Fraction(int n, int d) {
	bool negative = false;
	if (d == 0)
		throw FractionException("You cannot do that my guy");
	
		//a logic expression to determine if the fraction is positive or negative 
	if (((d < 0 && n > 0) || (d > 0 && n < 0)) && (n != 0))
		negative = true;
	
	//simplify the fraction by calling the GCD function
	numer = abs(n / gcd(n, d));
	denom = abs(d / gcd(n, d));
	
	//adjust the sign if needed
	if (negative == true)
		numer *= -1;
}

//ACCESSORS
int Fraction::numerator() const { return numer; }
int Fraction::denominator() const { return denom; }

//UTILITY FUNCTIONS
int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

//SETTER FUNCTION USED IN INPUT
void Fraction::setValues(int n, int d) {
	this->numer = n;
	this->denom = d;
}

FractionException::FractionException(const string& m) : message(m) { }
string FractionException::what() const {
	return message;
}
//BINARY OPERATIONS
Fraction operator+(const Fraction& a, const Fraction& b) {
	int n = (a.numerator() * b.denominator()) + (b.numerator() * a.denominator()); //this is gross but it works
	int d = a.denominator() * b.denominator();
	return Fraction(n, d);
}
Fraction operator-(const Fraction& a, const Fraction& b) {
	int n = (a.numerator() * b.denominator()) - (b.numerator() * a.denominator()); //this is gross but it works
	int d = a.denominator() * b.denominator();
	return Fraction(n, d); //copy constructors are used for most of this program since then I don't have to simplify again
}
Fraction operator*(const Fraction& a, const Fraction& b) {
	return Fraction(a.numerator() * b.numerator(), a.denominator() * b.denominator());
}
Fraction operator/(const Fraction& a, const Fraction& b) {
	return Fraction(a.numerator() * b.denominator(), a.denominator() * b.numerator()); //flip the second fraction and multiply
}
bool operator>(const Fraction& a, const Fraction& b) {
	if ((a - b).numerator() > 0) //a positive difference logically implies a is greater than b
		return true;
	else
		return false;
}
bool operator>=(const Fraction& a, const Fraction& b)
{
	if (a > b || a == b) //this is a combination of other functions
		return true;
	else
		return false;
}
bool operator<=(const Fraction& a, const Fraction& b)
{
	if (a < b || a == b) //this is a combination of other functions
		return true;
	else
		return false;
}
bool operator<(const Fraction& a, const Fraction& b)
{
	if ((a - b).numerator() < 0) //if the difference is negative it implies a is less than b
		return true;
	else
		return false;
}
bool operator==(const Fraction& a, const Fraction& b) {
	if ((a - b).numerator() == 0) //if the difference of the fractions is zero they are equal
		return true;
	else
		return false;
}
bool operator!=(const Fraction& a, const Fraction& b){
	if (a == b) //if they are not equal they are not equal....
		return false;
	else
		return true;
}

//UNARY OPERATIONS
Fraction operator-(const Fraction& a) {
	return Fraction(a.numerator()*-1, a.denominator()); //invert the numerator
}
Fraction Fraction::operator++(int i) {
	const Fraction prev(*this); //stores the original value of the fraction before incrementing
	this->numer = this->numer + this->denom;
	return prev;
}
Fraction Fraction::operator++() {// ++ used as postfix not done
	this->numer = this->numer + this->denom;
	return *this;
}
Fraction Fraction::operator+=(Fraction a) {//addition equals
	if (this->denom == a.denominator()) {
		this->numer = this->numer + a.numerator();
	}
	else {
		this->numer = ((this->numer * a.denominator()) + (this->denom * a.numerator()));
		this->denom = (this->denom * a.denominator());
	}
	return Fraction(this->numer, this->denom);
}

//I/O OPERATIONS
ostream& operator<<(ostream& out, const Fraction& f) {
	out << f.numerator() << "/" << f.denominator();
	return out;
}
istream& operator>>(istream& in, Fraction& f) {
	string value;
	in >> value; //copy the input into a string to be parsed

	size_t found = value.find("/"); 

	if (found != string::npos) { 
		int n = atoi(value.substr(0, found).c_str());; //atoi function sns when it encounters the first non numerical character
		int d = atoi(value.substr(found + 1).c_str()); //thises two lines effectively split the numerator and denom into two values 
		if (n == 0 && d != 0) {
			f.setValues(0, 1);
		}
		else
			f.setValues(n, d);
	}
	else if (!value.empty()) {
		if (atoi(value.c_str()) == 0) //for the case where no denominator is specified
			f.setValues(0, 1);
		else
			f.setValues(atoi(value.c_str()), 1);
	return in;
}

}