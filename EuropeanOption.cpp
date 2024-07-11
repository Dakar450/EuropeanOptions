// EuropeanOption.cpp
// source file for EuropeanOption class

#include "EuropeanOption.hpp"
#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <iostream>
using namespace std;

void EuropeanOption::init()
{	// Initialise all default values
	// Default values
	r = 0.05;
	sig = 0.2;
	K = 110.0;
	T = 0.5;
	b = r;			// Black and Scholes stock option model (1973)
	optType = "C";	// European Call Option (this is the default type)
}

void EuropeanOption::copy(const EuropeanOption& other)
{
	r = other.r;
	sig = other.sig;
	K = other.K;
	T = other.T;
	b = other.b;
	optType = other.optType;
}

double EuropeanOption::n(double x) const
{
	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	return pdf(myNormal, x);
}

double EuropeanOption::N(double x) const
{ // The approximation to the cumulative normal distribution
	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	return cdf(myNormal, x);
}

double EuropeanOption::CallPrice(double S) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + sig * sig * 0.5) * T) / tmp;
	double d2 = d1 - tmp;
	return (S * exp((b - r) * T) * N(d1)) - (K * (exp(-r * T) * N(d2)));
}

double EuropeanOption::PutPrice(double S) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + sig * sig * 0.5) * T) / tmp;
	double d2 = d1 - tmp;
	return (K * exp(- r * T) * N(-d2)) - (S * (exp((b - r) * T) * N(-d1)));
}

double EuropeanOption::CallDelta(double S) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	return exp((b - r) * T) * N(d1);
}

double EuropeanOption::PutDelta(double S) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	return exp((b - r) * T) * (N(d1) - 1.0);
}

double EuropeanOption::CallGamma(double S) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	return (n(d1) * exp((b - r) * T)) / (S * tmp);
}

double EuropeanOption::PutGamma(double S) const
{
	return CallGamma(S);
}

double EuropeanOption::CallVega(double S) const 
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	return (S * sqrt(T) * exp((b - r) * T) * n(d1));
}

double EuropeanOption::PutVega(double S) const
{
	return CallVega(S);
}

double EuropeanOption::CallTheta(double S) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;
	double t1 = (S * exp((b - r) * T) * n(d1) * sig * 0.5) / sqrt(T);
	double t2 = (b - r) * (S * exp((b - r) * T) * N(d1));
	double t3 = r * K * exp(-r * T) * N(d2);
	return -(t1 + t2 + t3);
}

double EuropeanOption::PutTheta(double S) const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;
	double t1 = (S * exp((b - r) * T) * n(d1) * sig * 0.5) / sqrt(T);
	double t2 = (b - r) * (S * exp((b - r) * T) * N(-d1));
	double t3 = r * K * exp(-r * T) * N(-d2);
	return t2 + t3 - t1;
}

// Default Constructor
EuropeanOption::EuropeanOption() 
{
	init();
}

EuropeanOption::EuropeanOption(const EuropeanOption& other)
{
	copy(other);
}

EuropeanOption::EuropeanOption(const string& optionType)
{
	init();
	optType = optionType;
}

EuropeanOption::EuropeanOption(const struct EuropeanOptionData& other)
{
	r = other.r;
	sig = other.sig;
	K = other.K;
	T = other.T;
	b = other.b;
	optType = other.optType;
}

// Destructor
EuropeanOption::~EuropeanOption() {};

EuropeanOption& EuropeanOption::operator = (const EuropeanOption& other) 
{
	if (this == &other)
	{
		return *this;
	}
	copy(other);
	return *this;
}

double EuropeanOption::Price(double S) const
{
	if (optType == "C")
	{
		return CallPrice(S);
	}
	else
	{
		return PutPrice(S);
	}
}

double EuropeanOption::Delta(double S) const
{
	if (optType == "C")
	{
		return CallDelta(S);
	}
	else
	{
		return PutDelta(S);
	}
}

double EuropeanOption::Gamma(double S) const
{
	if (optType == "C")
	{
		return CallGamma(S);
	}
	else
	{
		return PutGamma(S);
	}
}

double EuropeanOption::Vega(double S) const
{
	if (optType == "C")
	{
		return CallVega(S);
	}
	else
	{
		return PutVega(S);
	}
}

double EuropeanOption::Theta(double S) const
{
	if (optType == "C")
	{
		return CallTheta(S);
	}
	else
	{
		return PutTheta(S);
	}
}

void EuropeanOption::toggle() 
{
	if (optType == "C")
		optType = "P";
	else
		optType = "C";
}