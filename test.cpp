#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "products.h"

using namespace std;
using namespace Shop;

void log(ofstream& file, const string& msg) {
    cout << msg;
    file << msg;
}

int main() 
{
    ofstream file("log.txt");
    log(file, "=== Tests began ===\n");
    log(file, "====================\n\n");

    int passed = 0;
    int total = 0;

    total++;
    log(file, "\nTEST 1: Constructor & isEmpty\n");
    Products test;
    if (test.isEmpty()) {
        log(file, "  [PASS] Created empty list\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] Created NOT empty list\n");
    }

    total++;
    log(file, "\nTEST 2: operator+=\n");
    test += make_pair("Banana", "I.LOVE.CITY.OF.LOVE");
    test += make_pair("Apple", "Fresh fruit");
    
    if (!test.isEmpty() && test.getTotalElementCount() == 2) {
        log(file, "  [PASS] Two objects were successfully added\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] Objects were not added correctly\n");
    }

    total++;
    log(file, "\nTEST 3: operator[] search\n");
    
    if (test["Banana"] == true && test["Apple"] == true) {
        log(file, "  [PASS] Search found existing products\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] Search didn't find existing products\n");
    }

    total++;
    if (test["Grape"] == false) {
        log(file, "  [PASS] Search correctly returned false for non-existent product\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] Search returned true for non-existent product\n");
    }

    total++;
    log(file, "\nTEST 4: operator%= edit\n");
    test %= make_pair("Banana", "New description");
    
    if (test["Banana"] == true) {
        log(file, "  [PASS] Product still exists after edit\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] Product missing after edit\n");
    }

    total++;
    log(file, "\nTEST 5: operator-=\n");
    test -= "Banana";
    
    if (test["Banana"] == false && test.getTotalElementCount() == 1) {
        log(file, "  [PASS] Product successfully deleted\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] Product was not deleted correctly\n");
    }

    total++;
    log(file, "\nTEST 6: operator! clear\n");
    !test;
    
    if (test.isEmpty()) {
        log(file, "  [PASS] All products cleared\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] Products still exist after clear\n");
    }

    total++;
    log(file, "\nTEST 7: getTotalElementCount\n");
    
    Products test2;
    test2 += make_pair("One", "First");
    test2 += make_pair("Two", "Second");
    test2 += make_pair("Three", "Third");
    
    if (test2.getTotalElementCount() == 3) {
        log(file, "  [PASS] getTotalElementCount returns correct count (3)\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] getTotalElementCount returned " + 
            to_string(test2.getTotalElementCount()) + ", expected 3\n");
    }

    total++;
    log(file, "\nTEST 8: operator==\n");
    
    Products a, b;
    a += make_pair("X", "X-ray");
    a += make_pair("Y", "Yankee");
    
    b += make_pair("X", "X-ray");
    b += make_pair("Y", "Yankee");
    
    if (a == b) {
        log(file, "  [PASS] operator== correctly identifies equal lists\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] operator== failed for equal lists\n");
    }

    total++;
    log(file, "\nTEST 9: operator!=\n");
    
    Products c;
    c += make_pair("Z", "Zebra");
    
    if (a != c) {
        log(file, "  [PASS] operator!= correctly identifies different lists\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] operator!= failed for different lists\n");
    }

    total++;
    log(file, "\nTEST 10: operator<\n");
    
    if (c < a) {
        log(file, "  [PASS] operator< correctly identifies smaller list\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] operator< failed: 1 < 2 should be true\n");
    }

    total++;
    log(file, "\nTEST 11: operator>\n");
    
    if (a > c) {
        log(file, "  [PASS] operator> correctly identifies larger list\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] operator> failed: 2 > 1 should be true\n");
    }

    total++;
    log(file, "\nTEST 12: operator<=\n");
    
    if (c <= a && a <= a) {
        log(file, "  [PASS] operator<= works correctly\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] operator<= test failed\n");
    }

    total++;
    log(file, "\nTEST 13: operator>=\n");
    
    if (a >= c && a >= a) {
        log(file, "  [PASS] operator>= works correctly\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] operator>= test failed\n");
    }

    total++;
    log(file, "\nTEST 14: ProductException (duplicate)\n");
    
    Products dupTest;
    dupTest += make_pair("Unique", "First");
    
    try {
        dupTest += make_pair("Unique", "Second");
        log(file, "  [FAIL] No exception thrown for duplicate\n");
    }
    catch (const ProductException& e) {
        log(file, "  [PASS] Caught expected exception: ");
        log(file, e.what());
        log(file, "\n");
        passed++;
    }
    catch (...) {
        log(file, "  [FAIL] Caught wrong exception type\n");
    }

    total++;
    log(file, "\nTEST 15: out_of_range exception (delete nonexistent)\n");
    
    try {
        dupTest -= "Ghost";
        log(file, "  [FAIL] No exception thrown for deleting nonexistent\n");
    }
    catch (const out_of_range& e) {
        log(file, "  [PASS] Caught expected out_of_range: ");
        log(file, e.what());
        log(file, "\n");
        passed++;
    }
    catch (...) {
        log(file, "  [FAIL] Caught wrong exception type\n");
    }

    total++;
    log(file, "\nTEST 16: out_of_range exception (edit nonexistent)\n");
    
    try {
        dupTest %= make_pair("Ghost", "Boo!");
        log(file, "  [FAIL] No exception thrown for editing nonexistent\n");
    }
    catch (const out_of_range& e) {
        log(file, "  [PASS] Caught expected out_of_range: ");
        log(file, e.what());
        log(file, "\n");
        passed++;
    }
    catch (...) {
        log(file, "  [FAIL] Caught wrong exception type\n");
    }

    total++;
    log(file, "\nTEST 17: Copy constructor\n");
    
    Products original;
    original += make_pair("Keep", "This");
    original += make_pair("Me", "That");
    
    Products copy(original);
    
    if (copy.getTotalElementCount() == 2 && copy["Keep"] && copy["Me"]) {
        log(file, "  [PASS] Copy constructor works\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] Copy constructor failed\n");
    }

    total++;
    log(file, "\nTEST 18: toString()\n");
    
    string str = original.toString();
    if (!str.empty() && str.find("Keep") != string::npos) {
        log(file, "  [PASS] toString() returns non-empty string with product names\n");
        passed++;
    }
    else {
        log(file, "  [FAIL] toString() failed\n");
    }

    log(file, "\n====================\n");
    log(file, "=== TESTS COMPLETED ===\n");
    log(file, "====================\n");
    log(file, "Total tests: " + to_string(total) + "\n");
    log(file, "Passed: " + to_string(passed) + "\n");
    log(file, "Failed: " + to_string(total - passed) + "\n");
    log(file, "Success rate: " + to_string(passed * 100 / total) + "%\n");
    log(file, "====================\n");

    file.close();
    return 0;
}