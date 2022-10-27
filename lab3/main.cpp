#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <functional>

//#define ITERATIONS 1000000

using namespace std;
using domainVector = vector<double>;
using myFunction = function<double(vector<double>)>;
using myFunction2 = function<vector<double>(function<double(vector<double>)>,domainVector)>;

random_device randomDevice;
mt19937 mtGenerator(randomDevice());

vector<double> finalResult(const myFunction2& func,
                 vector<string> inputFromUser,
                 const map<string, myFunction>& map1,
                 const map<string, myFunction2>& map2){
    string execFunctionName = inputFromUser.at(1);
    string mathFunctionName = inputFromUser.at(2);
    double xMin = stod(inputFromUser.at(3));
    double xMax = stod(inputFromUser.at(4));
    double yMin = stod(inputFromUser.at(5));
    double yMax = stod(inputFromUser.at(6));
    double iterations = stod(inputFromUser.at(7));
    vector<double> points = func(map1.at(inputFromUser.at(2)), {xMin, xMax, yMin, yMax, iterations});
    return points;
}

int main(int argc, char** argv){
    //input:
    vector<string> inputValues(argv, argc + argv);
    //mathFunctions:
    map<string, myFunction> mathFuncMap;
    mathFuncMap["BoothFunction"] = [](vector<double> values){
        if(-10>values.front() || values.front()>10 || -10>values.back() || values.back()>10) throw invalid_argument("Input x value must be higher of equal -10 and y value must be 10 or lower.");
        return pow((values.front() + (2 * (values.back())) - 7), 2) + pow(((2 * values.front()) + values.back() - 5), 2);};
    mathFuncMap["HimmelblauFunction"] = [](vector<double> values){
        if(-5>values.front() || values.front()>5 || -5>values.back() || values.back()>5) throw invalid_argument("Input x value must be higher of equal -5 and y value must be 5 or lower.");
        return pow(((pow(values.front(), 2)) + (values.back()) + 11), 2) + pow((values.front() + (pow(values.back(), 2)) - 7), 2);};
    mathFuncMap["MatyasFunction"] = [](vector<double> values){
        if(-10>values.front() || values.front()>10 || -10>values.back() || values.back()>10) throw invalid_argument("Input x value must be higher of equal -10 and y value must be 10 or lower.");
        return 0.26*(pow(values.front(), 2) + pow(values.back(), 2)) - 0.48 * (values.front() * values.back());};
    mathFuncMap["Bealefunction"] = [](vector<double> values) {
        if (-5 > values.front() || values.front() > 4.5 || -4.5 > values.back() || values.back() > 5)
            throw invalid_argument("Input x value must be higher of equal -10 and y value must be 10 or lower.");
        return pow(1.5 - values.front() + (values.front() * values.back()), 2) +
               pow(2.25 - values.front() + pow(values.front() * values.back(), 3), 2) +
               pow(2.625 - values.front() + (pow(values.front() * values.back(), 3)), 2);};
    //Functions that look for lowest points:
    map<string, myFunction2>executionFuncMap;
    executionFuncMap["BruteForce"] = [](const function<double(vector<double>)>& func, domainVector domain){
        double lowestValue = numeric_limits<double>::max();
        double xLowestDomainValue = domain.at(0);
        double xHighestDomainValue = domain.at(1);
        double yLowestDomainValue = domain.at(2);
        double yHighestDomainValue = domain.at(3);
        double iterations = domain.at(4);
        vector<double> finalValues;
        for (int i = 0; i < iterations; i++) {
            uniform_real_distribution<double> x(xLowestDomainValue, xHighestDomainValue);
            uniform_real_distribution<double> y(yLowestDomainValue, yHighestDomainValue);
            domainVector randomVlues = {x(mtGenerator), y(mtGenerator)};
            double temp = func(randomVlues);
            if (lowestValue > temp) {
                lowestValue = temp;
                finalValues.clear();
                finalValues.push_back(randomVlues.at(0));
                finalValues.push_back(randomVlues.at(1));
                finalValues.push_back(temp);
            }
        }
        return finalValues;
    };
    try{
        string execFunctionName = inputValues.at(1);
        string mathFunctionName = inputValues.at(2);
        string xMin = inputValues.at(3);
        string xMax = inputValues.at(4);
        string yMin = inputValues.at(5);
        string yMax = inputValues.at(6);
        string iterations = inputValues.at(6);

      vector<double> results = finalResult(executionFuncMap.at(inputValues.at(1)), inputValues, mathFuncMap, executionFuncMap);
        cout << "x: " << results[0] << endl;
        cout << "y: " << results[1] << endl;
        cout << "Lowest found value: " << results[2] << endl;
    }catch(out_of_range e) {
        cout << "Available functions:" << endl;
        cout << "Matyas function(-10<=x,y<10)" << endl;
        cout << "Himmelblau's function(-5<=x,y<5)" << endl;
        cout << "Booth function(-10<=x,y<10)" << endl;
        cout << "Beale function(-4.5<=x,y<4.5)" << endl;
    }
    return 0;
}