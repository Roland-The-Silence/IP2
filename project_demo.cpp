#include <iostream>
#include <string>
#include <list>
#include <cstring>
#include <memory>
#include "products.h"
#include <sstream>
using namespace std;
using namespace Shop;

int main()
{
    try 
    {
        Products table;
        //////////////////// Checking if isEmpty works ////////////////////
        if (table.isEmpty() == true) {
            cout << "List is empty" << endl << endl;
        }
        //////////////////// Checking if isEmpty works ////////////////////

        //////////////////// Checking if operator+= works ////////////////////
        table += make_pair("Apple", "the round fruit of a tree of the rose family, which typically has thin green or red skin and crisp flesh.");
        table += make_pair("Banana", "A banana is an elongated, edible fruit.");
        table += make_pair("Fish", "just a regular salmon.");
        cout << table.toString();
        //////////////////// Checking if operator+= works ////////////////////

        //////////////////// Checking if operator-= works ////////////////////
        table -= ("Apple");
        cout << table.toString();
        //////////////////// Checking if operator+= works ////////////////////

        //////////////////// Checking if operator%= works ////////////////////
        table %= make_pair("Banana", "probably edible.");
        cout << table.toString() << endl << endl;
        //////////////////// Checking if operator%= works ////////////////////

        //////////////////// Checking if operator[] works ////////////////////
        if (table["Banana"] == true) {
            cout << "Yeah, it exists" << endl << endl;
        };
        //////////////////// Checking if operator[] works ////////////////////

        //////////////////// Checking if operator! works ////////////////////
        !table;
        cout << table.toString() << endl << endl;
        //////////////////// Checking if operator! works ////////////////////

        //////////////////// Checking if getTotalElementCount works ////////////////////
        cout << "Total product count: " << table.getTotalElementCount() << endl << endl;
        if (table.isEmpty() == true) {
            cout << "THIS IS FOR REAL." << endl << endl;
        }
        //////////////////// Checking if getTotalElementCount works ////////////////////

        //////////////////// Checking if comparison operators work ////////////////////

        Products table2;
        Products table3;
        Products table4;
        Products table5;


        table2 += make_pair("Fridge", "your snacks is hiding there!!!");

        table3 += make_pair("Plane", "OH SHEEP");
        table3 += make_pair("Coconut", "i dunno, it is for acquired taste, but i think it is okay.");

        table4 += make_pair("Plane", "OH SHEEP");
        table4 += make_pair("Coconut", "i dunno, it is for acquired taste, but i think it is okay.");

        table5 += make_pair("Plane", "OH SHEEP");
        table5 += make_pair("Fruit", "contains a lot of cellulose that i need to eat a lot...");
        table5 += make_pair("Coconut", "i dunno, it is for acquired taste, but i think it is okay.");
        

        if (table3.operator==(table4) == true) {
            cout << "They are, INDEED, equal..." << endl << endl;
        }
  
        if (table3.operator!=(table4) == false) {
            cout << "YEAH, EQUAL." << endl << endl;
        }

        if (table3.operator<(table5) == true) {
            cout << "This is this and that is that... Oh, the second one is actually bigger \u00AF\\_(\u30C4)_/\u00AF" << endl << endl;
        }

        if (table3.operator<=(table4) == true) {
            cout << "This is this and that is that... Oh, the second one is actually bigger or the same size as the first one. \u00AF\\_(\u30C4)_/\u00AF" << endl << endl;
        }

        if (table3.operator>(table2) == true) {
            cout << "This is this and that is that... Oh, the first one is actually bigger. \u00AF\\_(\u30C4)_/\u00AF" << endl << endl;
        }

        if (table3.operator>=(table4) == true) {
            cout << "This is this and that is that... Oh, the first one is actually bigger or the same size as the second one. \u00AF\\_(\u30C4)_/\u00AF" << endl << endl;
        }

        //////////////////// Checking if comparison operators work ////////////////////
    }
    catch (const ProductException& e) {
        cout << "Some error occured: " << e.what() << endl;
    }
    return 0;
}