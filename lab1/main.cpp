#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using myFunction = function<double(vector<double>)>;

void printValues(vector<double> numb, myFunction fun){
    cout << fun(numb) << endl;
}

int main(int argc, char **argv) {
    map<string, myFunction> options;
    options["add"] = [](vector<double> numbers) { return numbers.front() + numbers.back(); };
    options["mod"] = [](vector<double> numbers) { return (int)numbers.front() % (int)numbers.back(); };
    options["sin"] = [](vector<double>numbers) { return sin(numbers.front()); };
try {
    vector<string> list(argv, argc + argv);
//    vector<double> numberes = {{stod(list.at(2)), stod(list.at(3))}};
    vector<double> numberes;
    for(int i = 2; i<argc; i++){
        numberes.push_back(stod(list.at(i)));
    }
    printValues(numberes, options.at(list.at(1)));
}
catch (out_of_range ofr){
    cout << "2.Wybierz jedna z trzech opcji: add, mod lub sin." << endl;
} catch (bad_function_call bfc) {
    cout << "3.Wybierz jedna z trzech opcji: add, mod lub sin." << endl;
}
    return 0;
}