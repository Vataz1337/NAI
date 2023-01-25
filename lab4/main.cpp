#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>


using namespace std;

random_device randomDevice;
mt19937 rng(randomDevice());

vector<vector<int>> allBits;


bool generateRandomBool(){
    return uniform_int_distribution<>{0, 1}(rng);
}

vector<int> generate_genotype(int length){
    vector<int> bits;
    bits.reserve(length);
    for(int i = 0; i < length; i++){
        bits.push_back(int(generateRandomBool()));
    }
    return bits;
}

double binaryToDecimal(int n){
    int num = n;
    double dec_value = 0;
    int base = 1;
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
    return dec_value;
}

vector<double> genotype_into_fenotype(const vector<int>& bits){
    vector<double> fenotype;
    string temp;
    int pumper = 0;
    for(int i = 0; i < 2; i++){
        double result = 0;
        if(i==1)pumper = 54;
        for(int j = 0; j < 55; j++){
            temp += to_string(bits[j+pumper]);
                if(temp.length()==3){
                    result += binaryToDecimal(stoi(temp));
                    temp = "";
                }
        }
        if(bits.at(pumper))result = result * -1;
        int devider = uniform_int_distribution<>{1, 100}(rng);
        result = result/devider;
        fenotype.push_back(result);
    }
    return fenotype;
}

vector<double> populate(int ammount){
    vector<double> population;
    for(int i = 0; i < ammount; i++){
        vector<int> bits = generate_genotype(110);
        vector<double> fenotype = genotype_into_fenotype(bits);
        allBits.push_back(bits);
        population.push_back(fenotype[0]);
        population.push_back(fenotype[1]);
    }
    return population;
}

///-4.5 <= x, <= 4.5
double beale_function(double x, double y){
    return pow(1.5 - x + x * y, 2) +
           pow(2.25 -x + x * pow(y, 2),2) +
           pow(2.625 - x + x *  pow(y, 3), 2);
}

///-5 <= x, <= 5
//double himmelblau_function(double x, double y){
//    return pow(pow(x,2)+y-11,2) + pow(x+pow(y,2)-7,2);
//}

struct Data {
    vector<int> allBits;
    vector<double> population;
    double result{};
};

bool compare(const Data& a, const Data& b) {
    return a.result < b.result;
}

vector<Data> fitness(vector<double> population){
    vector<Data> data;
    vector<double> results;
    int chromos = 0;
    for(int i = 0; i < population.size(); i = i + 2){
        double x = population.at(i);
        double y = population.at(i+1);
        double result = beale_function(x, y);
        if (x >= -4.5 && x <= 4.5 && y >= -4.5 && y <= 4.5) result = 100000 - abs(result);
        else if(result>100000){
            while(result>100000){
                result = result/10;
            }
        }
        Data currentData;
        currentData.allBits = {allBits[chromos]};
        currentData.population = {x, y};
        currentData.result = result;
        data.push_back(currentData);
        chromos++;
    }
    sort(data.begin(), data.end(), compare);
    return data;
}

void print_results( const vector<Data>& data){
    for (auto i : data) {
        cout << "Chromo: ";
        for(auto j : i.allBits){
            cout << j;
        }
        cout << endl;
        cout << "population: " << i.population[0] << ", " << i.population[1] << endl;
        cout << "result: " << i.result << endl;
        cout << "------------------------------------------------------------------------------------------------------" << endl;
    }
}

vector<Data> naturalSelection(const vector<Data>& data) {
    vector<Data> survivors;
    double total_result = 0;
    for(auto & i : data) {
        total_result += i.result;
    }
    for(auto & i : data) {
        double survival_rate = i.result * 10/ total_result;
        double random_value = uniform_real_distribution<>{0, 1}(rng);
        if(random_value <= survival_rate) {
            survivors.push_back(i);
        }
    }
    return survivors;
}

void printChromos(const vector<int>& chromos){
    cout << endl;
    for(int chromo : chromos){
        cout << chromo;
    }
    cout << endl;
}

Data create_new_data(const vector<int>& chromos){
    Data newData;
    newData.allBits = chromos;
    vector<double> xy = genotype_into_fenotype(chromos);
    newData.population = xy;
    double result = beale_function(xy.at(0), xy.at(1));
    newData.result = result;

    return newData;
}

Data x_Point_mutation(const Data& parent, int times){
    cout << endl << "x_Point_mutation: " << endl;
    vector<int> newChromos = parent.allBits;
    cout << "Initial chromosome: ";
    printChromos(newChromos);
    cout << "Mutation on elements : ";
    for(int i = 0; i < times; i++){
        int randomIndex = rng() % newChromos.size();
        int randomElement = newChromos[randomIndex];
        cout << randomIndex << " ";
        if(randomElement == 1)newChromos[randomIndex] = 0;
        else newChromos[randomIndex] = 1;
    }
    Data child = create_new_data(newChromos);
    return child;
}

Data uniform_mutation(const Data& parent, int percent){
    cout << endl << "uniform_mutation: " << endl;
    vector<int> newChromos = parent.allBits;
    cout << "Initial chromosome: ";
    printChromos(newChromos);
    cout << "Mutation on elements :";
    for(int i = 0; i < newChromos.size(); i++){
        std::uniform_int_distribution<int> distribution(1, 100);
        int randomNumber = distribution(rng);
        if(randomNumber <= percent){
            cout << i << " ";
            if(newChromos[i] == 0) newChromos[i] = 1;
            else newChromos[i] = 0;
        }
    }
    Data child = create_new_data(newChromos);
    return child;
}

Data cross_mutation(const Data& parent1,const Data& parent2){
    std::uniform_int_distribution<int> distribution(1, 100);
    int randomNumber = distribution(rng);
    cout << endl << "cross_mutation(" << randomNumber << "):" << endl;
    vector<int> parent1Chromos = parent1.allBits;
    cout << "Parent1: ";
    printChromos(parent1Chromos);
    vector<int> parent2Chromos = parent2.allBits;
    cout << "Parent2: ";
    printChromos(parent2Chromos);
    vector<int> childChromos;
    for(int i = 0; i < parent1Chromos.size(); i++){
        if(randomNumber >= i) childChromos.push_back(parent1Chromos[i]);
        else childChromos.push_back(parent2Chromos[i]);
    }
    Data child = create_new_data(childChromos);
    cout << "Child: ";
    printChromos(child.allBits);
    return child;
}

Data two_point_crossover(const Data& parent1,const Data& parent2, int cross_point_one, int cross_point_two){
    cout << endl << "cross_mutation:" << endl;
    vector<int> parent1Chromos = parent1.allBits;
    cout << "Parent1: ";
    printChromos(parent1Chromos);
    vector<int> parent2Chromos = parent2.allBits;
    cout << "Parent2: ";
    printChromos(parent2Chromos);
    cout << "First point: " << cross_point_one << " ";
    cout << "Second point: " << cross_point_two << endl;
    vector<int> childChromos;
    for(int i = 0; i < parent1Chromos.size(); i++){
        if(cross_point_one >= i) childChromos.push_back(parent1Chromos[i]);
        else if(cross_point_two >= i && i > cross_point_one) childChromos.push_back(parent2Chromos[i]);
        else childChromos.push_back(parent1Chromos[i]);
    }
    Data child = create_new_data(childChromos);
    cout << "Child: ";
    printChromos(child.allBits);
    return child;
}

vector<Data> tournament(const vector<Data>& data, int group_size, int number_of_winners) {
    cout << "Tournament" << endl;
    vector<Data> winners;
    vector<Data> group;
    vector<int> used;
    for(int j = 0; j < number_of_winners; j++){
        while(group.size() < group_size) {
            std::uniform_int_distribution<int> distribution(0, int(data.size()));
            int random_element_group = distribution(rng);
            if (std::find(used.begin(), used.end(), random_element_group) == used.end()) {
                used.push_back(random_element_group);
                group.push_back(data.at(random_element_group));
            }
        }
        Data biggest;
        int counter = 0;
        for(int i = 1; i < group_size; i++){
            counter++;
            Data a = group.at(i);
            cout << "Candidate " << counter << ": " << a.result << endl;
            
            Data b = group.at(i);
            cout << "Candidate " << counter+1 << ": " << b.result << endl;
            if(a.result > b.result && a.result > biggest.result) biggest = a;
            else if(b.result > a.result && b.result > biggest.result) biggest = b;
        }
        winners.push_back(biggest);
    }
    return winners;
}



int main() {
    vector<Data> sorted = fitness(populate(100));
    print_results(sorted);
    cout << endl << "Survivors: " << endl << endl;
    vector<Data>  sortedArray = naturalSelection(sorted);
    print_results(sortedArray);
    printChromos(x_Point_mutation(sorted[0], 3).allBits);
    printChromos(uniform_mutation(sorted[0], 5).allBits);
    cross_mutation(sorted[0], sorted[1]);
    two_point_crossover(sorted[0], sorted[1], 2,10);
    print_results(tournament(sortedArray, 5, 10));
//    cout << beale_function(1.15254, -1.11111);
    ///99992.8
    return 0;
}

