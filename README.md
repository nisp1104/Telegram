# Telegram
Project that I created with Etash Kalra in December 2019 for CSCI 2275

## Requirements
The telegram.txt must be passed in as a command line argument in order for the program to run correctly.
Example: `> FinalProjectV4.exe telegram.txt`

## Initiation
Before the user is given the menu of options to pick from, the program reads through the telegram.txt file and adds each city into a vector `cities`, along with a list of adjacent cities and their weight (which represent distance in this program) for each city. This allows the list of cities and its connections to be represented as a data structure.

## 1. Print list of all cities and their neighboring cities
This option displays all cities listed in the telegram.txt file and outputs all connected cities. It does this by taking each city and recursively printing out its adjacent cities.

## 2. Print connecting cities and distances for a given city
This option is similar to the option above in that it prints out information about a specific city and its connections. Unlike the option above, it allows the user to specify which city they want printed out, and it informs the user of the weight/distance of the connections between the adjacent cities.

## 3. Delete City
If the user enters the name of a city in the data structure, the program finds the city, deletes the connections to the adjacent cities with the `erase()` function, and deletes the city with the same `erase()` function. If the user tries to print the city using option 2, the console will tell the user that the city is not found. Similarly, if the user prints a list of all cities in the data structure with option 1, they will not see that deleted city in the list. They can bring back the city by either adding it with option 4 or restarting the program.

## 4. Add City
After checking that the user-inputted city doesn't already exist in the data structure, the program allows the user to add the name of a new city to enter into the data structure. The program uses the same function as it did in option 1 to insert the new city into the structure. Then, the user has the option to add any adjacent cities and the distance between each adjacent city, or they can leave the city unconnected. If the user does connect the new city to existing cities, the program will ensure that the adjacent cities that they specify already exist in the structure. Once the user declares that they are done adding adjacent cities, they can now see the city in the city list with option 1 or view specifications about the new city with option 2.

## 5. Transmit a message between cities
This option simulates the process of transmitting a message between cities. The process is done using Yen's algorithm, which uses multiple instances of Dijkstra's algorithm (more information about how the algorithm works can be found here: https://en.wikipedia.org/wiki/Yen%27s_algorithm). The user enters two cities that are connected through adjacent cities, along with any message that they would like to send. Once this is done, the program uses Yen's algorithm to find the shortest path between the two cities. The path is displayed, along with the total weight/distance of the path taken to deliver the message. To save some typing, I won't go into detail about how we made the algorithm work for this project, but I'd advise you to look at the code to see how it works since it was a proud accomplishment for my partner and me.

## 6. Quit
The program is exited.
