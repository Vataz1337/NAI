#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <functional>

#define TESTING_PROBES 1000000

using namespace std;
using myFunction = function<double(vector<double>)>;
using domainVector = vector<double>;

random_device randomDevice;
mt19937 mtGenerator(randomDevice());

double bruteforce(const function<double(vector<double>)>& func, domainVector domain) {
    double lowestValue = numeric_limits<double>::max();
    double xLowestDomainValue = domain.at(0);
    double xHighestDomainValue = domain.at(1);
    double yLowestDomainValue = domain.at(2);
    double yHighestDomainValue = domain.at(3);
    for (int i = 0; i < TESTING_PROBES; i++) {
        uniform_real_distribution<double> x(xLowestDomainValue, xHighestDomainValue);
        uniform_real_distribution<double> y(yLowestDomainValue, yHighestDomainValue);
        domainVector randomVlues = {x(mtGenerator), y(mtGenerator)};
        double temp = func(randomVlues);
        if (lowestValue > temp) {
            lowestValue = temp;
        }
    }
    return lowestValue;
}

int main(int argc, char** argv){
    vector<string> inputValues(argv, argc + argv);
    map<string, myFunction> funcMap;
    funcMap["BoothFunction"] = [](vector<double> values){
        if(-10>values.front() || values.front()>10 || -10>values.back() || values.back()>10) throw invalid_argument("Input x value must be higher of equal -10 and y value must be 10 or lower.");
        return pow((values.front() + 2 * (values.back()) - 7), 2) + pow((2 * (values.front()) + values.back() - 5), 2);};
    funcMap["HimmelblauFunction"] = [](vector<double> values){
        if(-5>values.front() || values.front()>5 || -5>values.back() || values.back()>5) throw invalid_argument("Input x value must be higher of equal -5 and y value must be 5 or lower.");
        return pow((pow(values.front(), 2) + (values.back()) + 11), 2) + pow((values.front() + pow(values.back(), 2) - 7), 2);};
    funcMap["MatyasFunction"] = [](vector<double> values){
        if(-5>values.front() || values.front()>5 || -5>values.back() || values.back()>5) throw invalid_argument("Input x value must be higher of equal -10 and y value must be 10 or lower.");
        return 0.26*(pow(values.front(), 2) + pow(values.back(), 2)) - 0.48 * (values.front() * values.back());};
    try{
        cout << bruteforce(funcMap.at(inputValues.at(1)), {stod(inputValues.at(2)), stod(inputValues.at(3)), stod(inputValues.at(4)), stod(inputValues.at(5))});
    }catch(out_of_range e) {
        cout << "Available functions:" << endl;
        cout << "Matyas function(-10<=x,y<10)" << endl;
        cout << "Himmelblau's function(-5<=x,y<5)" << endl;
        cout << "Booth function(-10<=x,y<10)" << endl;
    }
    return 0;
}