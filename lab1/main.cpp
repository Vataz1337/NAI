#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using myFunction = function<float(int x, int y)>;

void printValues(const myFunction& func, int x, int y=0){
    cout << func(x, y) << endl;
}

int main(int argc, char **argv) {
    vector<string> list(argv, argc + argv);
    map<string, myFunction> options;
    options["add"] = [](int x, int y) { return x + y; };
    options["mod"] = [](int x, int y) { return x % y; };
    options["sin"] = [](int x, int y=0) { return sin(x); };
try {
    if (list.at(1)=="sin") {
        printValues(options[list.at(1)], stoi(list.at(2)));
    } else if (list.at(1)=="add" || list.at(1)=="mod") {
        printValues(options[list.at(1)], stoi(list.at(2)), stoi(list.at(3)));
    }else{
        cout << "1.Wybierz jedna z trzech opcji: add, mod lub sin." << endl;
    }
}catch (out_of_range ofr){
    cout << "2.Wybierz jedna z trzech opcji: add, mod lub sin." << endl;
} catch (bad_function_call bfc) {
    cout << "3.Wybierz jedna z trzech opcji: add, mod lub sin." << endl;
}
    return 0;
}