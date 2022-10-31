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

//function that return our final vector with results
vector<double> finalResult(const myFunction2& func,
                 vector<string> inputFromUser,
                 const map<string, myFunction>& map1){
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
    mathFuncMap["BoothFunction"] = [](domainVector values){
        if(-10>values.front() || values.front()>10 || -10>values.back() || values.back()>10) throw invalid_argument("Inputs x,y values must be higher or equal -10 and equal or lower than 10");
        return pow((values.front() + (2 * (values.back())) - 7), 2) + pow(((2 * values.front()) + values.back() - 5), 2);};
    mathFuncMap["HimmelblauFunction"] = [](domainVector values){
        if(-5>values.front() || values.front()>5 || -5>values.back() || values.back()>5) throw invalid_argument("Inputs x,y values must be higher or equal -5 and equal or lower than 5");
        return pow(((pow(values.front(), 2)) + (values.back()) + 11), 2) + pow((values.front() + (pow(values.back(), 2)) - 7), 2);};
    mathFuncMap["MatyasFunction"] = [](domainVector values){
        if(-10>values.front() || values.front()>10 || -10>values.back() || values.back()>10) throw invalid_argument("Inputs x,y values must be higher or equal -10 and equal or lower than 10");
        return 0.26*(pow(values.front(), 2) + pow(values.back(), 2)) - 0.48 * (values.front() * values.back());};
    mathFuncMap["Bealefunction"] = [](domainVector values) {
        if (-4.5 > values.front() || values.front() > 4.5 || -4.5 > values.back() || values.back() > 4.5)
            throw invalid_argument("Inputs x,y values must be higher or equal -4.5 and equal or lower than 4.5");
        return pow(1.5 - values.front() + (values.front() * values.back()), 2) +
               pow(2.25 - values.front() + pow(values.front() * values.back(), 3), 2) +
               pow(2.625 - values.front() + (pow(values.front() * values.back(), 3)), 2);};
    //Functions that look for lowest points randomly:
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
    executionFuncMap["Climb"] = [](const function<double(vector<double>)>& func, domainVector domain){
        double xLowestDomainValue = domain.at(0);
        double xHighestDomainValue = domain.at(1);
        double yLowestDomainValue = domain.at(2);
        double yHighestDomainValue = domain.at(3);
        double iterations = domain.at(4);
        uniform_real_distribution<double> x(xLowestDomainValue, xHighestDomainValue);
        uniform_real_distribution<double> y(yLowestDomainValue,yHighestDomainValue);
        domainVector current_p = {x(mtGenerator), y(mtGenerator)};
        domainVector new_p;
        for(int i = 0; i < iterations; i++){
            uniform_real_distribution<double> dist(-1.0/128.0, 1.0/128);
            double newX = current_p[0] + dist(mtGenerator);
            double newY = current_p[1] + dist(mtGenerator);
            if(xLowestDomainValue > newX || xHighestDomainValue < newX || yLowestDomainValue > newY || yHighestDomainValue < newY){
            }else{
                new_p = {newX, newY};
                if(func(current_p) > func(new_p)){
                    current_p = new_p;
                }
            }
        }
        domainVector finalValues;
        finalValues.clear();
        finalValues.push_back(current_p.at(0));
        finalValues.push_back(current_p.at(1));
        finalValues.push_back(func(current_p));
        return finalValues;
    };
    executionFuncMap["Annealing"] = [](const function<double(vector<double>)>& func, domainVector domain){
        return domain;
    };
    try{
        //create vector with results for selected math function and execution function
      vector<double> results = finalResult(executionFuncMap.at(inputValues.at(1)), inputValues, mathFuncMap);
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