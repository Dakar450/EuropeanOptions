// Global Function
// MeshGenerate can create mesh array

#ifndef MeshGenerate_HPP
#define MeshGenerate_HPP

#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <iostream>
using namespace std;


vector<double> MeshArray(double begin, double end, int n)
{
	vector<double> vec;
	double h = (end - begin) / (n-1);
	for (int i = 0; i < n; i++)
	{
		vec.push_back(begin + h * i);
	}
	return vec;
}

vector < vector < boost::tuple<double, double> >> MeshMatrix(double begin, double end, int n, double begin1, double end1, int n1)
{
	vector < vector < boost::tuple < double,double>> > matrix;
	double h = (end - begin) / (n-1);
	double h1 = (end1 - begin1) / (n1 - 1);
	for (int i = 0; i < n; i++)
	{
		vector<boost::tuple<double, double>> vec;
		for (int j = 0; j < n1; j++) {
			//boost::tuple<int, double, std::string> myTuple(42, 3.14, "hello");
			vec.push_back(boost::make_tuple(begin+h*i,begin1+h1*j));
		}
		matrix.push_back(vec);
	}
	return matrix;
}


#endif