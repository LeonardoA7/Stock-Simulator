// NAME: Leonardo Alfaro
// WISC ID: 9082565608
#ifndef STOCKHOLDER_HEADER
#define STOCKHOLDER_HEADER

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "Stock.h"
#include <map>
#include <functional>
#include <algorithm>
using namespace std;
class Stockholder {
private:
public:
	string name;
	map<string, pair<Stock*, int>> portfolio;
	float cash;
	Stockholder(string _name);
	Stockholder();
	bool Purchase(Stock* stock, int count);
	bool Sell(string short_name, int count);
	float NetWorth();
	void Print();
	struct PortfolioValue {
		float total_value;
		void operator()(pair<string, pair<Stock*, int>> n) { total_value += (n.second.first->new_value * n.second.second); };
	};
};
#endif
