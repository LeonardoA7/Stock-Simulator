// NAME: Leonardo Alfaro
// WISC ID: 9082565608
#include <iostream>
#include "Stock.h"
#include "Stockholder.h"
#include <fstream>
using namespace std;
enum MAIN_MENU { LOG = 1, LIST = 2, ADVANCE = 3, EXIT = 4 };
enum USER_MENU { AVAILABLE = 1, MY = 2, PURCHASE = 3, SELL = 4, LOGOUT = 5};
void PrintMain();
void PrintUserMenu();
void Prompt();
int main() {
    int input = 0;
    int user_choice = 0;
    int style_choice = 0;
    fstream f;
    f.open("stocks.txt");
    int amount;
    f >> amount;
    map<string, Stock> stocks = map<string, Stock>();
    map<string, Stockholder> stockholders = map<string, Stockholder>();
    for (int i = 0; i < amount; i++) {
        Stock temp;
        f >> temp;
        stocks[temp.short_name] = temp;
    }
    do {
        PrintMain();
        cin >> input;
        while (!cin || input < 1 || input > 4) {
            if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
            cout << "Please enter a valid menu item: ";
            cin >> input;
        }
        string name;
        // now we have good input, handle the cases:
        switch (input) {
        case LOG:
        {
            Prompt();
            cin >> name;
            if (stockholders.find(name) == stockholders.end()) {
                // NOT FOUND
                Stockholder temp = Stockholder(name);
                stockholders[name] = temp;
            }
            Stockholder current = stockholders[name];
            do {
                PrintUserMenu();
                cin >> user_choice;
                while (!cin || user_choice < 1 || user_choice > 5) {
                    if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                    cout << "Please enter a valid menu item: ";
                    cin >> user_choice;
                }
                switch (user_choice) {
                case AVAILABLE:
                {
                    for (auto iter = stocks.begin(); iter != stocks.end(); iter++) {
                        iter->second.Print();
                    }
                    cout << "Enter any number to continue: " << endl;
                    int waste;
                    cin >> waste;
                    break;
                }
                case MY:
                {
                    current.Print();
                    int trash;
                    cout << "Please enter any number to continue: " << endl;
                    cin >> trash;
                    break;
                }
                case PURCHASE:
                {
                    string stock_name;
                    cout << "Please enter a stock's short name: " << endl;
                    cin >> stock_name;
                    if (stocks.find(stock_name) != stocks.end()) {
                        // FOUND
                        int shares;
                        cout << "How many shares would you like to purchase? " << endl;
                        cin >> shares;
                        Stock* temp = &stocks.find(stock_name)->second;
                        if (current.Purchase(temp, shares)) {
                            cout << "Congratulations! " << shares << " were purchased! " << endl;
                        }
                        else {
                            cout << "The stock could not be purchased " << endl;
                        }
                    }
                    else {
                        cout << "The stock could not be purchased" << endl;
                    }
                    break;
                }
                case SELL:
                {
                    string stock_name;
                    cout << "Please enter a stock's short name: " << endl;
                    cin >> stock_name;
                    if (current.portfolio.find(stock_name) != current.portfolio.end()) {
                        // FOUND
                        int shares;
                        cout << "How many shares would you like to sell? " << endl;
                        cin >> shares;
                        if (current.Sell(stock_name, shares)) {
                            cout << "Congratulations! " << shares << " were sold! " << endl;
                        }
                        else {
                            cout << "You do not have enough shares to sell" << endl;
                        }
                    }
                    else {
                        cout << "You do not own any shares of that stock! " << endl;
                    }
                        break;
                }
                case LOGOUT:
                    stockholders[name] = current;
                    break;
                }
              
            } while (user_choice != LOGOUT);
            break;
        }
        case LIST:
        {
            map<string, Stockholder> ::iterator it;
            for (it = stockholders.begin(); it != stockholders.end(); it++) {
                cout << it->second.name << endl;
            }
            int trash;
            cout << "Please enter any number to continue: " << endl;
            cin >> trash;
            break;
        }
        case ADVANCE:
        {
            map<string, Stock> ::iterator it;
            for (it = stocks.begin(); it != stocks.end(); it++) {
                it->second.AdvanceDay();
            }
            break;
        }
        case EXIT:
            break;
        }
    } while (input != EXIT);
    return 0;
}
void PrintMain() {
    cout << "Welcome to the Stock Portfolio Manager!" << endl
        << "[" << LOG << "] Log In" << endl
        << "[" << LIST << "] List Directory" << endl
        << "[" << ADVANCE << "] Advance a Day" << endl
        << "[" << EXIT << "] Exit Program" << endl
        << "Please enter a menu item: ";
}
void PrintUserMenu() {
    cout << "What would you like to do?" << endl
        << "[" << AVAILABLE << "] List Available Stocks" << endl
        << "[" << MY << "] List My Stocks" << endl
        << "[" << PURCHASE << "] Purchase Stocks" << endl
        << "[" << SELL << "] Sell Stocks" << endl
        << "[" << LOGOUT << "] Log Out (return to main menu)" << endl
        << "Please enter a menu item: ";
}
void Prompt() {
    cout << "Please Enter Your Name: " << endl;
}
