// NAME: Leonardo Alfaro
// WISC ID: 9082565608
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "Stock.h"
#include <map>
#include <functional>
#include <algorithm>
#include "Stockholder.h"
using namespace std;
Stockholder::Stockholder() {

}
Stockholder::Stockholder(string _name) {
	name = _name;
	map<string, pair<Stock*, int>> portfolio = map<string, pair<Stock*, int>>();
	cash = 100000.0f;
}
bool Stockholder::Purchase(Stock* stock, int count) {
	float cost = stock->new_value * count;
	if (cost > cash) {
		return false;
	}
	else {
		pair<Stock*, int> temp;
		temp.first = stock;
		temp.second = count;
		portfolio[stock->short_name] = temp;
		cash -= cost;
		return true;
	}
}
bool Stockholder::Sell(string short_name, int count) {
	if (portfolio[short_name].second >= count) {
		float value = portfolio[short_name].first->new_value * count;
		cash += value;
		portfolio[short_name].second -= count;
		return true;
	}
	else {
		return false;
	}
}
void Stockholder::Print() {
	map<string, pair<Stock*, int>> ::iterator it;
	cout << name << " " << this->NetWorth() << endl;
	for (it = portfolio.begin(); it != portfolio.end(); it++) {
		cout << it->second.first->short_name << " " << it->second.first->long_name << " " <<
			it->second.first->new_value << " " << it->second.first->new_value - it->second.first->old_value << " " << it->second.second << endl;
	}
}
float Stockholder:: NetWorth() {
	PortfolioValue f = for_each(portfolio.begin(), portfolio.end(), PortfolioValue());
	float value = f.total_value + cash;
	return value;
}
struct PortfolioValue {
	float total_value;
	void operator()(pair<string, pair<Stock*, int>> n) { total_value += (n.second.first->new_value * n.second.second); };
};
