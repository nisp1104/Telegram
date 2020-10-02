/*
 Etash Kalra and Nick Spooner
 CSCI 2275 Fall 2019
 Archana Anand
 Final Project
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct adjCity;

struct city {
    string name;
    string message;
    vector<adjCity> adjacency;
    int distance;
    bool solved;
    string path;
    city() {
        solved = false;
        distance = INT_MAX;
    }
    city(string name) {
        this->name = name;
        solved = false;
        distance = INT_MAX;
        path = name;
    }
};

struct adjCity {
    city* c;
    int weight;
};

class Telegram {
    vector<city> cities;
    
public:
    
    void printConnections(string cityname) {
        for (city ct : cities) {
            if (ct.name == cityname) {
                cout << cityname << " is connected to:" << endl;
                for (int i = 0; i < ct.adjacency.size(); i++) {
                    cout << ct.adjacency[i].c->name << ", " << ct.adjacency[i].weight << endl;;
                }
                return;
            }
        }
        
        cout << "City not found." << endl;
        
    }
    
    void printCities() {
        for (city ct : cities) {
            cout << ct.name << " is connected to ";
            for (int i = 0; i < ct.adjacency.size(); i++) {
                cout << ct.adjacency[i].c->name << ", ";
            }
            cout << endl;
        }
    }
    
    void deleteCity(string cityname) {
        for (int i = 0; i < cities.size(); i++) {
            //Finds city
            if (cities[i].name == cityname) {
                for (int j = 0; j < cities.size(); j++) {
                    //Finds all cities that are adjacent to city i
                    for (int k = 0; k < cities[j].adjacency.size(); k++) {
                        if (cities[i].name == cities[j].adjacency[k].c->name)
                            //Deletes city i from city j's adjacency list
                            cities[j].adjacency.erase(cities[j].adjacency.begin() + k);
                    }
                }
                
                //Find the city in the city vector and erase it
                cities.erase(cities.begin()+i);
                return;
            }
        }
        
        cout << "City not found." << endl;
    }
    
    void addEdge(string cityname1, string cityname2, int weight) {
        for (int i = 0; i < cities.size(); i++) {
            //Find first city
            if (cities[i].name == cityname1) {
                for (int j = 0; j < cities.size(); j++) {
                    //Find second city once first is found
                    if (cities[j].name == cityname2) {
                        /*Add the second city to the adjacency list of the first city (BUT NOT VICE VERSA). Vice Versa will be done again when the second object is iterated through in the read file function.*/
                        
                        adjCity tempcity;
                        tempcity.c = &cities[j];
                        tempcity.weight = weight;
                        cities[i].adjacency.push_back(tempcity);
                        return;
                        
                    }
                }
            }
        }
    }
    
    bool findCity(string cityname) {
        for (int i = 0; i < cities.size(); i++) {
            if (cities[i].name == cityname)
                return true;
        }
        
        return false;
    }
    
    void insertCity(string cityname) {
        
        //If the city already exists in the vector, skip it.
        for (int i = 0; i < cities.size(); i++) {
            if (cities[i].name == cityname) {
                return;
            }
        }
        
        //Add new city to the cities vector (if not added already, in which case it will return).
        city new_city(cityname);
        cities.push_back(new_city);
        
    }
    
    void readFile(string filename) {
        
        //Create first input file stream (first iteration through input txt)
        ifstream inputfilestream;
        inputfilestream.open(filename);
        if (!inputfilestream.is_open()) {
            cout << "error opening file" << endl;
            exit(1);
        }
        
        string current_line;
        //First iteration through file, gets all of the nodes before the "-" character without adding their adjacencies.
        while (getline(inputfilestream, current_line)) {
            //Turn the current line into its own string stream so we can separate the city before the "-" character.
            stringstream ss(current_line);
            string new_city;
            getline(ss, new_city, '-');
            insertCity(new_city);
        }
        
        //Reset the ifstream to the beginning of the file for second iteration.
        inputfilestream.clear();
        inputfilestream.seekg(0, std::ios::beg);
        while (getline(inputfilestream, current_line)) {
            //Parse the current line into all of the required inputs
            stringstream ss(current_line);
            
            //Store the name of the city before the "-" on the line (this is the main city of the line)
            string current_city;
            getline(ss, current_city, '-');
            
            //Each subsequent city ties to the current city is stored temporarily here with the weight between them as a concatenated string
            //Ex.) "Seattle(10)" is a single string
            string temp_city_string;
            
            while (getline(ss, temp_city_string, ',')) {
                //Remove unexpected whitespaces
                //temp_city_string.erase(remove(temp_city_string.begin(), temp_city_string.end(), '\n'), temp_city_string.end());
                //temp_city_string.erase(remove(temp_city_string.begin(), temp_city_string.end(), '\r'), temp_city_string.end());
                
                //Create a new string stream to parse the actual city name from the associated weight.
                //Ex.) "Seattle(10)" will become "Seattle" and 10.
                stringstream citystream(temp_city_string);
                
                //Stores city name ex.)"Seattle"
                string temp_city;
                
                //Stores weight string ex.) "10"
                string weight_s;
                //Stores weight int ex.) 10
                int weight;
                
                //Parses the city's name from the concatenated string
                getline(citystream, temp_city, '(');
                
                //Gets the remainder of the concatenated string as the weight minus an unnecessary ')' and converts to int
                //Ex.) "10)" parsed as "10" and converted to 10.
                getline(citystream, weight_s, ')');
                weight = stoi(weight_s);
                
                addEdge(current_city, temp_city, weight);
                
            }
            
        }
        
    }
    
    void addCity(string cityname) {
        
        string adjCity;
        int weight;
        string weight_s;
        insertCity(cityname);
        
        cout << "Enter an existent adjacent city, or type \"done\" to exit: ";
        getline(cin, adjCity);
        cout << endl;
        
        while (1) {
            
            if (adjCity == "done" || adjCity == "Done") {
                break;
            }
            
            if (!findCity(adjCity)) {
                cout << "City doesn't exist. Enter a valid city: " << endl;
                getline(cin, adjCity);
                cout << endl;
                continue;
            }
            
            cout << "Enter the distance between the two cities: ";
            getline(cin, weight_s);
            weight = stoi(weight_s);
            if(weight <= 0) {
                cout << "Enter a value greater than 0.";
                return;
            }
            
            cout << endl;
            
            addEdge(cityname, adjCity, weight);
            addEdge(adjCity, cityname, weight);
            
            cout << "Enter an existent adjacent city, or type \"done\" to exit: ";
            getline(cin, adjCity);
            cout << endl;
        }
    }
    
    void transmitMessage(string city1, string city2, string message) {
        
        //Reset all of the cities' distance, solved boolean, and path
        for(int i = 0; i < cities.size(); i++) {
            cities[i].distance = INT_MAX;
            cities[i].solved = false;
            cities[i].path = cities[i].name;
        }
        
        //Find city1 and assign 0 to its distance to begin the algorithm
        for(int i = 0; i < cities.size(); i++) {
            if(cities[i].name == city1) {
                cities[i].distance = 0;
                break;
            }
        }
        
        while(true) {
            int min = INT_MAX;
            city temp;
            
            //Find unsolved node with minimum distance (set to temp)
            for(int i = 0; i < cities.size(); i++) {
                if(!cities[i].solved && cities[i].distance < min) {
                    min = cities[i].distance;
                    temp = cities[i];
                }
            }
            
            for(int i = 0; i < cities.size(); i++) {
                //Find the temp city
                if(temp.name == cities[i].name) {
                    //Mark temp as solved
                    cities[i].solved = true;
                    
                    //Print path and return if temp is city2
                    if(cities[i].name == city2) {
                        cout << "The total path had distance: " << cities[i].distance << endl;
                        cout << endl;
                        cout << "(" << message << ") " << cities[i].path << endl;
                        return;
                    }
                    
                    //If city2 not found yet, get the adjacency list
                    vector<adjCity> adj = cities[i].adjacency;
                    
                    for(int j = 0; j < adj.size(); j++) {
                        if(cities[i].distance + adj[j].weight < adj[j].c->distance) {
                            adj[j].c->distance = cities[i].distance + adj[j].weight;
                            adj[j].c->path = cities[i].path + " > " + adj[j].c->name;
                        }
                    }
                    
                }
            }
            
        }
        
    }
    
};

void printMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Print list of all cities and their neighboring cities" << endl;
    cout << "2. Print connecting cities and distances for a given city" << endl;
    cout << "3. Delete City" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Transmit a message between cities" << endl;
    cout << "6. Quit" << endl;
}

int main(int argc, const char* argv[]) {
    
    Telegram t;
    
    t.readFile(argv[1]);
    
    string string_input;
    
    printMenu();
    
    while (getline(cin, string_input)) {
        
        int menu_input = 0;
        try { //try used to catch error handling...
            menu_input = stoi(string_input); //converts string input to number for options in switch statement
            cout << endl;
        }
        catch (...) {
            continue;
        }
        
        //Switch the int value of the user input option.
        switch (menu_input) {
            case 1: { //Print All Cities and Neighbors
                t.printCities();
                cout << endl;
            } break;
            case 2: { //Print City and Its Neighbors
                string cityname;
                cout << "Enter a city name: ";
                getline(cin, cityname);
                cout << endl;
                t.printConnections(cityname);
                cout << endl;
            } break;
            case 3: { //Delete City
                string cityname;
                cout << "Enter a city name: ";
                getline(cin, cityname);
                cout << endl;
                t.deleteCity(cityname);
                cout << endl;
            } break;
            case 4: { //Add City
                string cityname;
                cout << "Enter a new city name: ";
                getline(cin, cityname);
                cout << endl;
                if (t.findCity(cityname))
                    cout << "City already exists." << endl;
                else
                    t.addCity(cityname);
                cout << endl;
            } break;
            case 5: { //Transmit Message Between Cities
                string city1, city2, message;
                cout << "Enter the city to send the message from: ";
                getline(cin, city1);
                cout << "Enter the city to send the message to: ";
                getline(cin, city2);
                cout << "Please enter your message:" << endl;
                getline(cin, message);
                cout << endl;
                
                t.transmitMessage(city1, city2, message);
                
                cout << endl;
            } break;
            case 6: { //Quit
                exit(1);
            } break;
            default: {
                cout << endl;
            } break;
                
        }
        
        printMenu();
        
    }
    
    return 0;
}

