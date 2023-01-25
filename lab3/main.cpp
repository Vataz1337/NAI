#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <functional>
#include <cmath>
#include <ctime>

# define M_PI           3.14159265358979323846  /* pi */

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

vector<uniform_real_distribution<double>> setUp(domainVector domain){
    double xLowestDomainValue = domain.at(0);
    double xHighestDomainValue = domain.at(1);
    double yLowestDomainValue = domain.at(2);
    double yHighestDomainValue = domain.at(3);
    uniform_real_distribution<double> x(xLowestDomainValue, xHighestDomainValue);
    uniform_real_distribution<double> y(yLowestDomainValue, yHighestDomainValue);
    vector<uniform_real_distribution<double>> result = {x, y};
    return result;
}

void printResults(domainVector results){
    cout << "x: " << results[0] << endl;
    cout << "y: " << results[1] << endl;
    cout << "Lowest found value: " << results[2] << endl;
    cout << "Time: " << results[3] << endl;
}

int main(int argc, char** argv){
    //input:
    vector<string> inputValues(argv, argc + argv);
    //mathFunctions:
    map<string, myFunction> mathFuncMap;
    mathFuncMap["Booth_function"] = [](domainVector values){
        if(-10>values.front() || values.front()>10 || -10>values.back() || values.back()>10) throw invalid_argument("Inputs x,y values must be higher or equal -10 and equal or lower than 10");
        return pow((values.front() + (2 * (values.back())) - 7), 2) + pow(((2 * values.front()) + values.back() - 5), 2);};
    mathFuncMap["Himmelblau_function"] = [](domainVector values){
//        if(-5>values.front() || values.front()>5 || -5>values.back() || values.back()>5) throw invalid_argument("Inputs x,y values must be higher or equal -5 and equal or lower than 5");
        return pow(pow(values.at(0),2)+values.at(1)-11,2) + pow(values.at(0)+pow(values.at(1),2)-7,2);};
    mathFuncMap["Matyas_function"] = [](domainVector values){
        if(-10>values.front() || values.front()>10 || -10>values.back() || values.back()>10) throw invalid_argument("Inputs x,y values must be higher or equal -10 and equal or lower than 10");
        return 0.26*(pow(values.front(), 2) + pow(values.back(), 2)) - 0.48 * (values.front() * values.back());};
    mathFuncMap["Beale_function"] = [](domainVector values) {
        if (-4.5 > values.front() || values.front() > 4.5 || -4.5 > values.back() || values.back() > 4.5)
            throw invalid_argument("Inputs x,y values must be higher or equal -4.5 and equal or lower than 4.5");
        return pow(1.5 - values.front() + (values.front() * values.back()), 2) +
               pow(2.25 - values.front() + pow(values.front() * values.back(), 3), 2) +
               pow(2.625 - values.front() + (pow(values.front() * values.back(), 3)), 2);};
    mathFuncMap["Tcamel_function"] = [](domainVector values) {
        double firstPart = 2*pow(values.front(),2);
        double secondPart = 1.05*pow(values.front(),4);
        double thirdPart = (pow(values.front(),6))/6;
        double fourthPart = values.front()*values.back();
        double fifthPart = pow(values.back(),2);
        return (firstPart-secondPart+thirdPart+fourthPart+fifthPart);
    };
    //Functions that look for lowest points randomly:
    map<string, myFunction2>executionFuncMap;
    executionFuncMap["BruteForce"] = [](const function<double(vector<double>)>& func, domainVector domain){
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        double lowestValue = numeric_limits<double>::max();
        double iterations = domain.at(4);
        uniform_real_distribution<double> x = setUp(domain).at(0);
        uniform_real_distribution<double> y = setUp(domain).at(1);
        vector<double> finalValues;
        for (int i = 0; i < iterations; i++) {
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
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        finalValues.push_back(cpu_time_used);
        return finalValues;
    };
    executionFuncMap["Climb"] = [](const function<double(vector<double>)>& func, domainVector domain){
        clock_t start, end;
        double cpu_time_used;
        start = clock();
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
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        finalValues.push_back(cpu_time_used);
        return finalValues;
    };
    executionFuncMap["Annealing"] = [](const function<double(vector<double>)>& func, domainVector domain){
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        double iterations = domain.at(4);
        uniform_real_distribution<double> distx = setUp(domain).at(0);
        uniform_real_distribution<double> disty = setUp(domain).at(1);
        double x = distx(mtGenerator);
        double y = disty(mtGenerator);
        domainVector current_p = {x, y};
        double currentResult = func(current_p);
        normal_distribution<double> randomiser(0, 1);
        uniform_real_distribution<double> step(-1.0 / 128, 1.0 / 128);
        domainVector newPoints;
//        domainVector v = {currentResult};
        for(int k=1;k<iterations;k+=1){
            double a = x + step(mtGenerator);
            double b = y + step(mtGenerator);
            newPoints = {a, b};
            double newResult = func(newPoints);
            if(currentResult>=newResult){
                currentResult = newResult;
                x = a;
                y = b;
            }else{
                double modifier2 = randomiser(mtGenerator);
                double Tk = 1.0/log(k);
                if(modifier2 < exp(-1 * (fabs(newResult - currentResult) / Tk))){
                    currentResult = newResult;
                    x = a;
                    y = b;
                }
            }
        }
        domainVector finalValues;
        finalValues.clear();
        finalValues.push_back(newPoints.at(0));
        finalValues.push_back(newPoints.at(1));
        finalValues.push_back(currentResult);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        finalValues.push_back(cpu_time_used);
        return finalValues;
    };
    try{
        //create vector with results for selected math function and execution function
        //results = finalResult(executionFuncMap.at(inputValues.at(1)), inputValues, mathFuncMap);

        double bruteForceSum = 0;
        double climbSum = 0;
        double annealingSum = 0;
        double bruteForceTime = 0;
        double climbTime = 0;
        double annealingTime = 0;

        for(int i = 0; i < 25; i++){
            cout << inputValues.at(2) << endl;
            cout << "-------------------------------------------------------------------------------------------------------" << endl;
            cout << "BruteForce:" << endl;
            vector<double> results1 = finalResult(executionFuncMap.at("BruteForce"), inputValues, mathFuncMap);
            printResults(results1);
            bruteForceSum += results1.at(2);
            bruteForceTime += results1.at(3);
            cout << "-------------------------------------------------------------------------------------------------------" << endl;
            cout << "Climb:" << endl;
            vector<double> results2 = finalResult(executionFuncMap.at("Climb"), inputValues, mathFuncMap);
            printResults(results2);
            climbSum += results2.at(2);
            climbTime += results2.at(3);
            cout << "-------------------------------------------------------------------------------------------------------" << endl;
            cout << "annealing:" << endl;
            vector<double> results3 = finalResult(executionFuncMap.at("Annealing"), inputValues, mathFuncMap);
            printResults(results3);
            annealingSum += results3.at(2);
            annealingTime += results3.at(3);
        }
        cout << endl << "Iterations: " << inputValues.at(7) << endl;
        cout <<  "Avarage sum for BruteForce: " << bruteForceSum/25 << endl;
        cout << "Avarage time for BruteForce: " << bruteForceTime/25 << endl;
        cout << "Avarage sum for Climb: " << climbSum/25 << endl;
        cout << "Avarage time for Climb: " << climbTime/25 << endl;
        cout << "Avarage sum for Annealing: " << annealingSum/25 << endl;
        cout << "Avarage time for Annealing: " << annealingTime/25 << endl;
    }catch(out_of_range e) {
        cout << "Available functions:" << endl;
        cout << "Matyas function(-10<=x,y<10)" << endl;
        cout << "Himmelblau's function(-5<=x,y<5)" << endl;
        cout << "Booth function(-10<=x,y<10)" << endl;
        cout << "Beale function(-4.5<=x,y<4.5)" << endl;
        cout << "Hölder_table_function(-10<=x,y<10)" << endl;
    }
    return 0;
}