#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <functional>

#define TESTING_PROBES 1000000

using namespace std;
using myFunction = function<double(vector<double>)>;
using dVector = vector<double>;

random_device randomDevice;
mt19937 mtGenerator(randomDevice());

double bruteforce(const function<double(vector<double>)>& func, dVector domain){
    double lowestValue = numeric_limits<double>::max();
    double lowestDomain = domain.at(0);
    double highiestDomain = domain.at(1);
    for(int i = 0 ; i < TESTING_PROBES ; i++){
        uniform_real_distribution<double> randomValue(lowestDomain, highiestDomain);
        vector<double> randomValuesOfxy{randomValue(mtGenerator),randomValue(mtGenerator)};
        double temp = func(randomValuesOfxy);
        lowestValue > temp ? lowestValue = temp : false;
    }
    return lowestValue;
}

int main(int argc, char** argv){
    vector<string> inputValues(argv, argc + argv);
    map<string, myFunction> funcMap;
    funcMap["BoothFunction"] = [](vector<double> xyValues){
        if(xyValues.front()<-10 || xyValues.front()>10)
            throw invalid_argument("Input x value must be higher of equal -10 and y value must be 10 or lower.");
        return pow((xyValues.front()+2*(xyValues.back())-7),2)+pow((2*(xyValues.front())+xyValues.back()-5),2);};
    funcMap["Himmelblau's function"] = [](vector<double> xyValues){
        if(xyValues.front()<-5 || xyValues.front()>5)
            throw invalid_argument("Input x value must be higher of equal -5 and y value must be 5 or lower.");
        return pow((pow(xyValues.front(),2)+(xyValues.back())+11),2)+pow((xyValues.front()+pow(xyValues.back(),2)-7),2);};
    funcMap["Matyas function"] = [](vector<double> xyValues){
        if(xyValues.front()<-10 || xyValues.front()>10)
            throw invalid_argument("Input x value must be higher of equal -10 and y value must be 10 or lower.");
        return 0.26*(pow(xyValues.front(),2)+pow(xyValues.back(),2))-0.48*(xyValues.front()*xyValues.back());};
    try{
        cout << bruteforce(funcMap.at(inputValues.at(1)), {stod(inputValues.at(2)), stod(inputValues.at(3))});
    }catch(out_of_range e) {

    }
    return 0;
}