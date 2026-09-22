#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "gnuplot-iostream.h"

const double x_0 = 1.272;
const double x_f = 1.35;

double original(double arg)
{
	return arg * cos(4 * arg) - 0.5;
}

double derivative(double arg)
{
	return cos(4 * arg) - 4 * arg * sin(4 * arg);
}

double second_derivative(double arg)
{
	return -8.0 * sin(4.0 * arg) - 16.0 * arg * cos(4.0 * arg);
}

double ch_m0nesy(double x_k_1)
{
	return x_k_1 - original(x_k_1) / derivative(x_k_1);
}

double s1mple(double x_0, double x_k_1)
{
	return x_k_1 - original(x_k_1) / derivative(x_0);
}

void print_list(std::list<double>& list)
{
	std::cout << "[";
	for (double v : list) {
		std::cout << std::fixed << std::setprecision(12) << v << ", ";
	}
	std::cout << "]" << "\n";
}

void draw()
{
	Gnuplot gp;
	std::vector<std::pair<double, double>> pts_f;
	std::vector<std::pair<double, double>> pts_df;
	std::vector<std::pair<double, double>> pts_ddf;
	for (double x = x_0; x <= x_f; x += 0.002) {
		pts_f.push_back(std::make_pair(x, original(x)));
		pts_df.push_back(std::make_pair(x, derivative(x)));
		pts_ddf.push_back(std::make_pair(x, second_derivative(x)));
	}

	gp << "set xlabel 'x'\n";
	gp << "set ylabel 'x'\n";
	gp << "set grid\n";
	gp << "plot '-' with lines title 'f(x)' lc rgb 'blue', "
		<< "'-' with lines title 'fd(x)' lc rgb 'green',"
		<< "'-' with lines title 'fdd(x)' lc rgb 'red'\n";

	gp.send1d(pts_f);
	gp.send1d(pts_df);
	gp.send1d(pts_ddf);

	std::cin.get();
}


int main()
{
	// fx = x*cos(4*x)-0.5
	// fx' = cos(4*x) - 4*x*sin(4*x)

	const int it_numb = 20; //3 5 10 20
	// cycle standart method
	std::list<double> stand;
	stand.push_back(x_0);
	for (int i = 0; i < it_numb; i++)
	{
		stand.push_back(ch_m0nesy(stand.back()));
	}
	print_list(stand);
	if (std::abs(original(stand.back())) <= 1e-12)
	{
		std::cout << "True" << "\n";
	}
	// cycle simlified method
	std::list<double> simple;
	simple.push_back(x_0);
	for (int i = 0; i < it_numb; i++)
	{
		simple.push_back(s1mple(x_0, simple.back()));
	}
	print_list(simple);
	if (std::abs(original(simple.back())) <= 1e-12)
	{
		std::cout << "True" << "\n";
	}
	draw();

}


