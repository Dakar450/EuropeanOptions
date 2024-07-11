// EuropeanOption.hpp
// header file for European class

# ifndef EuropeanOption_HPP
# define EuropeanOption_HPP

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class EuropeanOption
{
private:

	void init();	// Initialise all default values
	void copy(const EuropeanOption& other);

	// 'Kernel' functions for option calculations
	double CallPrice(double S) const;
	double CallDelta(double S) const;
	double CallGamma(double S) const;
	double CallVega(double S) const;
	double CallTheta(double S) const;
	double PutPrice(double S) const;
	double PutDelta(double S) const;
	double PutGamma(double S) const;
	double PutVega(double S) const;
	double PutTheta(double S) const;


	// Gaussian functions
	double n(double x) const;
	double N(double x) const;


public:

	// Member data public for convenience; anyway, the format will 
	// not change for a plain option.
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double b;		// Cost of carry
	string optType;	// Option name (call, put)


public:	// Public functions
	EuropeanOption();							// Default call option
	EuropeanOption(const EuropeanOption& other);	// Copy constructor
	EuropeanOption(const string& optionType);	// Create option type
	EuropeanOption(const struct EuropeanOptionData& other); // Create with parameters
	virtual ~EuropeanOption();

	EuropeanOption& operator = (const EuropeanOption& other);

	// Functions that calculate option price and sensitivities
	double Price(double S) const;
	double Delta(double S) const;
	double Gamma(double S) const;
	double Vega(double S) const;
	double Theta(double S) const;

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)

};

struct EuropeanOptionData
{
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double b;		// Cost of carry
	string optType;	// Option name (call, put)
};

# endif