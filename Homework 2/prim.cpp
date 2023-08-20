//ANALYSIS OF ALGORITHMS 2 HOMEWORK 2
//Leminur Çelik - 150190085
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <chrono>
using namespace std;
 
class Vertex{
    private:
        int xCoordinate;//Initialize x-coordinate
        int yCoordinate;//Initialize y-coordinate
        long int pount;//Initialize pount number
        bool finish;//Initialize finish for bakeries unable to open a new branch
        vector<int> visitedVertices;//Initialize visited vertices
    public:
        //Constructor of Vertex
        Vertex(){};
        
        //Constructor of Vertex with x-coordinate, y-coordinate, pount number as inputs
        Vertex(int xCoordinate, int yCoordinate, long int pount){
            this->xCoordinate = xCoordinate;
            this->yCoordinate = yCoordinate;
            this->pount = pount;
        };

        //Return x-coordinate of a vertex
        int get_xCoordinate(){
            return this->xCoordinate;
        };

        //Return y-coordinate of a vertex
        int get_yCoordinate(){
            return this->yCoordinate;
        };

        //Return pount number of a vertex
        long int get_pount(){
            return this->pount;
        };

        //Return finish of a vertex
        int get_finish(){
            return this->finish;
        };

        //Return finish of a vertex
        void set_finish(bool finish){
            this->finish = finish;
        };

        //Return visited vertices of a vertex
        vector<int> get_visited_vertices(){
            return this->visitedVertices;
        };

        //Set visited vertices vector of a vertex with given number
        void set_visited_vertices(int number){
            this->visitedVertices.push_back(number);
        };
};

class Graph{
    private:
        int **graph;//Initialize adjacency matrix
        int numberVertices;//Initialize number of vertices
        int xDistance;//Initialize x distance from one vertex to other
        int yDistance;//Initialize y distance from one vertex to other
        long unsigned int plow;//Initialize plow
        float threshold;//Initialize threshold
        int bakeryNumber;//Initialize number of bakeries
    public:
        //Constructor of Graph
        Graph(int numberVertices, float threshold, int bakeryNumber){
            this->numberVertices = numberVertices;
            this->threshold = threshold;
            this->bakeryNumber = bakeryNumber;
            graph = new int*[numberVertices];//Create an adjacency matrix with the number of rows equal to the number of vertices
            for (int i = 0; i < numberVertices; i++)
            {
                graph[i] = new int[numberVertices];//Create an adjacency matrix with the number of columns equal to the number of vertices
                //Initialize edges 0 
                for (int j = 0; j < numberVertices; j++)
                {
                    graph[i][j] = 0;
                }
            }
        };

        //Set edges between vertices
        void setEdges(Vertex *vertices){
            for (int i = 0; i < numberVertices; i++){
                for (int j = 0; j < numberVertices; j++){
                    if (i == j) 
                    {
                        graph[i][j] = 0;
                        break;
                    }
                    //Plow equals to the absolute difference of pount numbers in between two vertices
                    plow = abs(vertices[i].get_pount() - vertices[j].get_pount());
                    //If the plow is less than or equal to the threshold times the mean of their pount numbers, then there is an edge between two vertices
                    if (plow <= (((vertices[i].get_pount() + vertices[j].get_pount()) / 2) * threshold))
                    {
                        //Each edge has weight which is equal to  the plow
                        graph[i][j] = plow;
                        graph[j][i] = plow;  
                    }
                }
            }
        };

        //Find the greater edge weight from the relation of a vertex to other vertices
        int maxKey(vector<bool> &visited, int index, vector<int> &key){
            int max_index = -1;//Initialize max index to -1
            for (int i = 0; i < numberVertices; i++)
            {
                //If a vertex has a connection with another vertex and that vertex has not been visited before and its value is less than the value of the edge with the vertex, 
                //then equal the key value of the other vertex to the connection value with the vertex
                if (graph[index][i] != 0 && visited[i] == false && key[i] < graph[index][i])
                {
                    key[i] = graph[index][i];
                }
            }
            int largest = 0;//Initialize largest to 0
            for (int i = 0; i < numberVertices; i++)
            {
                //If key value of a vertex is bigger than largest value and taht vertec has not been visited before,
                //then equal largest to key value of that vertex and max index to i
                if (key[i] > largest && visited[i] == false)
                {
                    largest = key[i];
                    max_index = i;
                }
            }
            return max_index;//Return max index
        };

        //Prims algorithm 
        void primsAlgorithm(Vertex *vertices, vector<int> &bakeries){
            vector<bool> visited(numberVertices, false);//Initialize a vector called visited with number of vertices and initalized as false
            vector<vector<int>> key(bakeryNumber);//Initialize a 2D vector called key, declare the size of the row
            for (int i = 0; i < bakeryNumber; i++)
            {
                vertices[bakeries[i]].set_visited_vertices(bakeries[i]);//Set visited vertices vector of a bakeries
                visited[bakeries[i]] = true;//Set bakery indices as visited
                vertices[bakeries[i]].set_finish(false);//Set finish of bakeries as false
                key[i] = vector<int>(numberVertices);//Declare the size of the column of 2D vector
            }
            for (int i = 0; i < numberVertices - 1; i++)
            {   
                int checker = 0;//Initialize checker to 0
                for (int j = 0; j < bakeryNumber; j++)
                {
                    if (vertices[bakeries[j]].get_finish() == false)
                    {
                        checker++;
                        int index = vertices[bakeries[j]].get_visited_vertices().back();//Initialize index to visited vertices vector's back value of bakeries
                        int u = maxKey(visited, index, key[j]);//Call maxKey function 
                        //If u is equal to -1, it means that bakery cannot open another branch,
                        //set the finish of bakery and continue 
                        if(u == -1){
                            vertices[bakeries[j]].set_finish(true);
                            continue;
                        }
                        visited[u] = true;//Set u vertex as true
                        vertices[bakeries[j]].set_visited_vertices(u);//Put the value u in visited vertices vector of that bakery
                    }
                }
                //Exit the for loop if no bakery can open branches
                if (checker == 0){
                    break;
                }
            }
        };

        //Write prim representation into an output file
        void printPrimsAlgorithm(Vertex *vertices, vector<int> &bakeries, ofstream &prim){
            for (int j = 0; j < bakeryNumber; j++)
            {
                prim << "k" << j << " " << vertices[bakeries[j]].get_visited_vertices().size() << endl;
                for (int long unsigned i = 0; i < vertices[bakeries[j]].get_visited_vertices().size() - 1; i++)
                {
                    prim << vertices[bakeries[j]].get_visited_vertices()[i] << "->";
                }
                prim << vertices[bakeries[j]].get_visited_vertices()[vertices[bakeries[j]].get_visited_vertices().size() - 1];
                prim << endl;
            }
        };

        //Destructor of Graph
        ~Graph(){
            for(int i = 0; i < numberVertices; i++){
                delete[] graph[i];
            }
            delete[] graph;
        };
};
int main(int argc, char **argv){
    string input = argv[1];//Get the input file from the command line
    fstream file(input, ios::in);//Define the input file as file
    ofstream prim("prim.txt", ios::out);//Define the output of graph representation file as output
    int cityNumber, bakeryNumber, sourceIndex;//Initialize the number of city, the number of bakery and the index of bakery
    float threshold;//Initialize threshold
    file >> cityNumber >> bakeryNumber >> threshold;//Read the number of cities and the number of bakeries and threshold valuefrom file
    vector<int> bakeries;//Initialize a vector called bakeries
    //Read the indices of bakeries from file and push into the vector called bakeries
    for (int i = 0; i < bakeryNumber; i++)
    {
        file >> sourceIndex;
        bakeries.push_back(sourceIndex);
    }
    Vertex *vertices = new Vertex[cityNumber];//Create vertices with given number
    //Call constructor function with x-coordinate, y-coordinate, strength level as inputs
    for (int i = 0; i < cityNumber; i++){
        int x, y, a;
        file >> x >> y >> a;
        vertices[i] = Vertex(x, y, a);
    }
    Graph g(cityNumber, threshold, bakeryNumber);//Create a graph using adjacency matrix
    g.setEdges(vertices);//Check for edge between nodes and add edge if any
    g.primsAlgorithm(vertices, bakeries);//Call prims algorithm function
    g.printPrimsAlgorithm(vertices, bakeries, prim);//Call print function for prims algorithm
    exit(0);
}