/*
Ethan Herndon
Dr. Clinkenbeard
CST 426
10/25/2020
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>

using namespace std;

//Refernce: https://sourcemaking.com/design_patterns/strategy/cpp/1
//The algorithms provided are from my CST 370 class @CSUMB.

class Strategy;
void bfs() {
  int numCitiesVert;
  vector < string > cities;
  map < string, int > visited;

  cout << "Enter number of nodes you want: ";
  cin >> numCitiesVert; //input

  cout << "\n" << "Enter node names: " << endl;
  for (int i = 0; i < numCitiesVert; i++) {
    string element;
    cin >> element;
    visited.insert({
      element,
      -1
    });
    cities.push_back(element);
  }

  int numCitiesEdge;
  string sourceCity;
  string destinationCity;
  unordered_map < string, vector < string >> graph;
  cout << "Enter amount of edges you want: ";
  cin >> numCitiesEdge;

  cout << "\n" << "Enter name of starting node and finshing node" << endl;
  for (int i = 0; i < numCitiesEdge; i++) {
    cin >> sourceCity >> destinationCity;
    graph[sourceCity].push_back(destinationCity);
  }

  string startingCity;
  int hops = 0;

  cout << "\n" << "Now enter starting city and number of hops" << endl;
  cin >> startingCity >> hops;

  queue < string > q;
  q.push(startingCity);
  visited.find(startingCity) -> second = 0;
  vector < int > amount;
  int replaceHops = 0;
  int counter = 0;
  map < string, int > results;

  sort(cities.begin(), cities.end());
  while (!q.empty()) //bfs
  {

    startingCity = q.front();
    results.insert({
      startingCity,
      visited[startingCity]
    });
    for (string neighbor: graph[startingCity]) {

      if (visited[neighbor] == -1) {
        visited[neighbor] = visited[startingCity] + 1;
        q.push(neighbor);
      }
    }
    q.pop();
  }

  for (auto itr = results.begin(); itr != results.end(); ++itr) { //display results
    if (itr -> second > hops) {
      continue;
    }
    cout << itr -> first << ": " << itr -> second << endl;
  }
}

void dijkstra() {
  int vertices, edges;
  cout << "Enter number of vertices and edges: ";
  cin >> vertices >> edges;

  cout << "Enter Point A and Point B and Cost as numbers" << endl;
  // Retrieve Edge Data (Store Path as key and cost as value)
  unordered_map < string, int > edgeData;
  for (int i = 0; i < edges; i++) {
    string sVertex, dVertex;
    int cost;
    cin >> sVertex >> dVertex >> cost;

    edgeData[sVertex + dVertex] = cost;
  }

  int startVertex;
  cout << "\n" << "Please enter your starting node:";
  cin >> startVertex;

  // Setup Perumutation Array to Create Permutations
  int permutation[vertices - 1];
  int l = 0;
  for (int j = 0; j < vertices; j++) {
    if (j != startVertex) {
      permutation[l] = j;
      l++;
    }
  }

  // Setup Vectors of All Possible Permutations
  vector < vector < int >> permutations;
  do {
    vector < int > tempArr;

    // Add Current Permutation + Start Vertex to Vector
    tempArr.push_back(startVertex);
    for (int k = 0; k < vertices - 1; k++) {
      tempArr.push_back(permutation[k]);
    }
    tempArr.push_back(startVertex);

    permutations.push_back(tempArr);
  } while (next_permutation(permutation, permutation + (vertices - 1)));

  // Find Least Expensive Permutation (Path)
  int minCost = INT_MAX;
  int bestPath = -1;
  for (int m = 0; m < permutations.size(); m++) {
    int currentCost = 0;

    // Calculate Path Cost for Each Permutation (Skip those Not Possible)
    for (int n = 0; n < vertices; n++) {
      string edgePath = to_string(permutations[m][n]) + to_string(permutations[m][n + 1]);

      if (edgeData.count(edgePath) > 0) {
        currentCost += edgeData[edgePath];
      } else {
        currentCost = INT_MAX;
        break;
      }
    }

    // Save Info if Cheapest Path
    if (currentCost < minCost) {
      minCost = currentCost;
      bestPath = m;
    }
  }

  // Output Results
  cout << "Path:";
  if (bestPath != -1) {
    for (int p = 0; p < permutations[bestPath].size(); p++) {
      if (p > 0) {
        cout << "->";
      }

      cout << permutations[bestPath][p];
    }
  } else {
    minCost = -1;
  }

  cout << "\nCost:" << minCost << endl;
}

class TestBed {
  public:
    enum StrategyType {
      Dummy,
      Left,
      Right,
      Center
    };
  TestBed() {
    strategy_ = NULL;
  }
  void setStrategy(int type);
  void doIt();
  private:
    Strategy * strategy_;
};

class Strategy {
  public:
    Strategy() {}
  void format() {
    justify();
  }
  private:
    virtual void justify() = 0;
};

class dijkstraStrategy: public Strategy {
  public: dijkstraStrategy(): Strategy() {}
  private: virtual void justify() {
    dijkstra();
  }
};

class aStarStrategy: public Strategy {
  public: aStarStrategy(): Strategy() {}
  private:
    /* virtual */
    void justify() {
      cout << "Implementation was not added, go about your day :).";
    }
};

class bfsStrategy: public Strategy {
  public: bfsStrategy(): Strategy() {}
  private:
    /* virtual */
    void justify() {
      bfs();
    }
};

void TestBed::setStrategy(int type) {
  //delete strategy_;
  if (type == 1)
    strategy_ = new aStarStrategy();
  else if (type == 2)
    strategy_ = new dijkstraStrategy();
  else if (type == 3)
    strategy_ = new bfsStrategy();
  else if (type == 4)
    return;
}

void TestBed::doIt() {
  strategy_ -> format();
}

void displayInstructions() {
  string display = " ";
  display = ("This program is to show strategy patterns of game programming. \nThese patterns include A*, Dijkstra, and Breadth-First Search. \nTo get started please select \n '1' for A* \n '2' for Dijkstra \n '3' for Breadth-First Search \n '4' to Quit");
  cout << display << "\n \n";
}

int main() {
  TestBed test;
  int choice = 0;
  displayInstructions();
  cout << "Please select a strategy pattern: ";
  cin >> choice;

  while (choice) {

    test.setStrategy(choice);
    test.doIt();
    displayInstructions();
    cin >> choice;
  }

}
/***********************************************************
Expected input and result for Dijkstra

Enter number of vertices and edges: 5 12
Enter Point A and Point B and Cost as numbers
0 4 6
0 3 7
1 0 1
3 1 2
4 3 3
2 4 4
0 2 5
0 1 1
1 3 1
3 4 1
4 2 1
2 0 1

Please enter your starting node:2
Path:2->0->1->3->4->2
Cost:5
*/
/**********************************************************
Expected input and result for BFS

Welcome to Breadth-First Search
Enter number of nodes you want: 4

Enter node names:
Monterey
LA
SF
SD
Enter amount of edges you want: 6

Enter name of starting node and finshing node
Monterey LA
LA SD
SD Monterey
SF Monterey
SF LA
SF SD

Now enter starting city and number of hops
Monterey 2
LA: 1
Monterey: 0
SD: 2

*/
