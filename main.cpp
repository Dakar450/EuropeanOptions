#include "EuropeanOption.hpp"
#include "MeshGenerate.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <cmath>
#include <fstream>
using namespace std;

int main() {
	EuropeanOption Option1;
	Option1.b = 0;
	Option1.r = 0.045;
	Option1.sig = 0.43;
	Option1.K = 122;
	Option1.T = 1.65;
	Option1.optType = "P";
	double S = 102;
	cout << Option1.Price(S) << ", " << Option1.Delta(S) << "," << Option1.Gamma(S);
	return 0;

}

	

	// Store Batch 1 to Batch 4 data in a vector.
	typedef boost::tuple<double, double, double, double, double> OptionTuple;
	vector<OptionTuple> vecBatch;
	vecBatch.push_back(boost::make_tuple(0.08, 0.3, 65.0, 0.25, 60.0));
	vecBatch.push_back(boost::make_tuple(0.0, 0.2, 100.0, 1.0, 100.0));
	vecBatch.push_back(boost::make_tuple(0.12, 0.5, 10.0, 1.0, 5.0));
	vecBatch.push_back(boost::make_tuple(0.08, 0.3, 100.0, 30.0, 100.0));
	ofstream fout("output.txt");

	// A.1.a
	cout << "A.1.a" << endl;
	fout << "A.1.a" << endl;
	for (int i = 0; i < vecBatch.size(); i++) 
	{
		EuropeanOption Option1;
		Option1.b = vecBatch[i].get<0>();
		Option1.r = vecBatch[i].get<0>();
		Option1.sig = vecBatch[i].get<1>();
		Option1.K = vecBatch[i].get<2>();
		Option1.T = vecBatch[i].get<3>();
		double S = vecBatch[i].get<4>();
		cout << "Batch" << i + 1 << ": Call Price = " << Option1.Price(S) << endl;
		fout << "Batch" << i + 1 << ": Call Price = " << Option1.Price(S) << endl;
		Option1.toggle();
		cout << "Batch" << i + 1 << ": Put Price = " << Option1.Price(S) << endl;
		fout << "Batch" << i + 1 << ": Put Price = " << Option1.Price(S) << endl;
		Option1.toggle();
		cout << endl;
	}
	cout << endl;
	fout << endl;

	// A.1.b
	cout << "A.1.b" << endl;
	fout << "A.1.b" << endl;
	for (int i = 0; i < vecBatch.size(); i++)
	{
		EuropeanOption Option1;
		Option1.b = vecBatch[i].get<0>();
		Option1.r = vecBatch[i].get<0>();
		Option1.sig = vecBatch[i].get<1>();
		Option1.K = vecBatch[i].get<2>();
		Option1.T = vecBatch[i].get<3>();
		double S = vecBatch[i].get<4>();
		// Compute the Put price based on Call price and Put-Call Parity Equation
		double CallPrice = Option1.Price(S);
		double KValue = Option1.K * exp((- Option1.r) * Option1.T);
		double PutPrice = CallPrice + KValue - S;
		cout << "Batch" << i + 1 << ": Call Price: " << CallPrice <<"; Put price calculated by Call-Put Parity is "<<PutPrice<< endl;
		fout << "Batch" << i + 1 << ": Call Price: " << CallPrice << "; Put price calculated by Call-Put Parity is " << PutPrice << endl;
		// Verify Put-Call Parity by both Put and Call prices
		Option1.toggle();
		double PutPrice1 = Option1.Price(S);
		double Parity = CallPrice + KValue - S - PutPrice1;
		cout << "Batch" << i + 1 << ": Put-Call Parity Verification, the result of C+Ke^(-rT)-P-S: " << Parity << endl;
		fout << "Batch" << i + 1 << ": Put-Call Parity Verification, the result of C+Ke^(-rT)-P-S: " << Parity << endl;
		Option1.toggle();
		cout << endl;
	}
	cout << endl;

	// A.1.c
	cout << "A.1.c" << endl;
	fout << "A.1.c" << endl;
	vector<double> vecS = MeshArray(10.0, 50.0, 41);
	for (int i = 0; i < vecBatch.size(); i++)
	{
		vector<double> vecCall, vecPut;
		EuropeanOption Option1;
		Option1.b = vecBatch[i].get<0>();
		Option1.r = vecBatch[i].get<0>();
		Option1.sig = vecBatch[i].get<1>();
		Option1.K = vecBatch[i].get<2>();
		Option1.T = vecBatch[i].get<3>();;
		for (int j = 0; j < vecS.size(); j++)
		{
			vecCall.push_back(Option1.Price(vecS[j]));
			Option1.toggle();
			vecPut.push_back(Option1.Price(vecS[j]));
			Option1.toggle();
		}
		for (int j = 0; j < vecCall.size(); j++)
		{
			cout << "Batch " << i + 1 << ": S = " << vecS[j] << ", C = " << vecCall[j] << ", P = " << vecPut[j] << endl;
			fout << "Batch " << i + 1 << ": S = " << vecS[j] << ", C = " << vecCall[j] << ", P = " << vecPut[j] << endl;
		}
	}
	cout << endl;
	
	// A.1.d
	cout << "A.1.d" << endl;
	fout << "A.1.d" << endl;
	cout << "Test parameter matrix of price S and Volatility sig" << endl;
	fout << "Test parameter matrix of price S and Volatility sig" << endl;
	vector < vector < boost::tuple<double, double> >> Parameters = MeshMatrix(10.0, 50.0, 41, 0.1,0.4,9);
	for (int i = 0; i < vecBatch.size(); i++)
	{
		vector<vector<double>> vecCall, vecPut;
		EuropeanOption Option1;
		Option1.b = vecBatch[i].get<0>();
		Option1.r = vecBatch[i].get<0>();
		Option1.sig = vecBatch[i].get<1>();
		Option1.K = vecBatch[i].get<2>();
		Option1.T = vecBatch[i].get<3>();
		double S = vecBatch[i].get<4>();
		for (int j = 0; j < Parameters.size(); j++)
		{
			vector<double> vecC, vecP;
			for (int i = 0; i < Parameters[j].size(); i++) 
			{
				Option1.sig = Parameters[j][i].get<1>();
				vecC.push_back(Option1.Price(Parameters[j][i].get<0>()));
				Option1.toggle();
				vecP.push_back(Option1.Price(Parameters[j][i].get<0>()));
				Option1.toggle();
			}
			vecCall.push_back(vecC);
			vecPut.push_back(vecP);
		}
		
		for (int j = 0; j < vecCall.size(); j++)
		{
			for (int i = 0; i < vecCall[j].size(); i++)
			{
				cout << "Batch " << i + 1 << ": S = " << Parameters[j][i].get<0>() <<", sig = "<< Parameters[j][i].get<1>() << ", C = " << vecCall[j][i] << ", P = " << vecPut[j][i] << endl;
				fout << "Batch " << i + 1 << ": S = " << Parameters[j][i].get<0>() << ", sig = " << Parameters[j][i].get<1>() << ", C = " << vecCall[j][i] << ", P = " << vecPut[j][i] << endl;
			}
		}
		
	}
	cout << endl;



	// Parameters 
	double S = 105.0;
	EuropeanOptionData data0{0.1, 0.36, 100.0, 0.5, 0.0, "C"};

	// A.2.a
	cout << "A.2.a" << endl;
	fout << "A.2.a" << endl;
	EuropeanOption Option0(data0);
	cout << "Call Delta: " << Option0.Delta(S) << ", Call Gamma: " << Option0.Gamma(S) << endl;
	fout << "Call Delta: " << Option0.Delta(S) << ", Call Gamma: " << Option0.Gamma(S) << endl;
	Option0.toggle();
	cout << "Put Delta: " << Option0.Delta(S) << ", Put Gamma: " << Option0.Gamma(S) << endl;
	fout << "Put Delta: " << Option0.Delta(S) << ", Put Gamma: " << Option0.Gamma(S) << endl;
	Option0.toggle();

	// A.2.b
	cout << "A.2.b" << endl;
	fout << "A.2.b" << endl;
	EuropeanOption Option2(data0);
	vector<double> CPrice;
	vector<double> CDelta;
	for (int j = 0; j < vecS.size(); j++)
	{
		double CallPrice = Option2.Price(vecS[j]);
		double CallDelta = Option2.Delta(vecS[j]);
		CPrice.push_back(CallPrice);
		CDelta.push_back(CallDelta);
	}

	for (int j = 0; j < vecS.size(); j++)
	{
		cout <<"S = " << vecS[j] << ", Value = " << CPrice[j] << ", Delta = " << CDelta[j] << endl;
		fout << "S = " << vecS[j] << ", Value = " << CPrice[j] << ", Delta = " << CDelta[j] << endl;
	}
	cout << endl;

	// A.2.c
	cout << "A.2.c" << endl;
	fout << "A.2.c" << endl;
	cout << "Test parameter matrix of price S and Volatility sig" << endl;
	fout << "Test parameter matrix of price S and Volatility sig" << endl;
	EuropeanOption Option3(data0);
	vector<vector<double>> vecDelta, vecGamma;
	for (int j = 0; j < Parameters.size(); j++)
	{
		vector<double> vecD, vecG;
		for (int i = 0; i < Parameters[j].size(); i++)
		{
			Option3.sig = Parameters[j][i].get<1>();
			vecD.push_back(Option3.Delta(Parameters[j][i].get<0>()));
			vecG.push_back(Option3.Gamma(Parameters[j][i].get<0>()));
		}
		vecDelta.push_back(vecD);
		vecGamma.push_back(vecG);
	}

	for (int j = 0; j < vecDelta.size(); j++)
	{
		for (int i = 0; i < vecDelta[j].size(); i++)
		{
			cout << "S = " << Parameters[j][i].get<0>() << ", sig = " << Parameters[j][i].get<1>() << ", Call Delta = " << vecDelta[j][i] << ", Call Gamma = " << vecGamma[j][i] << endl;
			fout << "S = " << Parameters[j][i].get<0>() << ", sig = " << Parameters[j][i].get<1>() << ", Call Delta = " << vecDelta[j][i] << ", Call Gamma = " << vecGamma[j][i] << endl;
		}
	}
	cout << endl;

	// A.2.d
	cout << "A.2.d" << endl;
	fout << "A.2.d" << endl;
	// calculate the A.2.a use this method
	cout << "Calculate A.2.a again" << endl;
	fout << "Calculate A.2.a again" << endl;
	vector<double> step{ 0.001,0.01,0.1 };
	for (int j = 0; j < step.size(); j++)
	{
		double S_up = S + step[j] * 0.5;
		double S_down = S - step[j] * 0.5;
		double NDelta = (Option0.Price(S_up) - Option0.Price(S_down))/step[j];
		double NGamma = 4*(Option0.Price(S_up) + Option0.Price(S_down) - 2 * Option0.Price(S)) / (step[j] * step[j]);
		cout << "Step: " << step[j] << ", Exact Delta: " << Option0.Delta(S) << ", Numerical Delta: " << NDelta << "Exact Gamma: " << Option0.Gamma(S) << ", Numerical Gamma: " << NGamma << endl;
		fout << "Step: " << step[j] << ", Exact Delta: " << Option0.Delta(S) << ", Numerical Delta: " << NDelta << "Exact Gamma: " << Option0.Gamma(S) << ", Numerical Gamma: " << NGamma << endl;
	}

	cout << "calculate A.2.b again" << endl;
	fout << "calculate A.2.b again" << endl;
	vector<double> CPrice1;
	vector<double> CDelta1;
	double step1 = 0.001;
	for (int j = 0; j < vecS.size(); j++)
	{
		double CallPrice = Option2.Price(vecS[j]);
		double S_up = S + step1 * 0.5;
		double S_down = S - step1 * 0.5;
		double NDelta = (Option0.Price(S_up) - Option0.Price(S_down)) / step1;
		double CallDelta = Option2.Delta(vecS[j]);
		CPrice1.push_back(CallPrice);
		CDelta1.push_back(CallDelta);
	}

	for (int j = 0; j < vecS.size(); j++)
	{
		cout << "S = " << vecS[j] << ", Value = " << CPrice1[j] << ", Numeric Delta = " << CDelta1[j] << endl;
		fout << "S = " << vecS[j] << ", Value = " << CPrice1[j] << ", Numeric Delta = " << CDelta1[j] << endl;
	}
	cout << endl;
	

	return 0;
}
