//ANALYSIS OF ALGORITHMS 2 HOMEWORK 1
//Leminur Çelik - 150190085
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
//Defined Vertex Class
class Vertex{
    private:
        int xCoordinate;//Initialize x-coordinate
        int yCoordinate;//Initialize y-coordinate
        int strengthLevel;//Initialize strength level
    public:
        //Constructor of Vertex
        Vertex(){};
        
        //Constructor of Vertex with x-coordinate, y-coordinate, strength level as inputs
        Vertex(int x, int y, int strength){
            xCoordinate = x;
            yCoordinate = y;
            strengthLevel = strength;
        };

        //Return x-coordinate of a vertex
        int get_xCoordinate(){
            return xCoordinate;
        };

        //Return y-coordinate of a vertex
        int get_yCoordinate(){
            return yCoordinate;
        };

        //Return strength level of a vertex
        int get_strengthLevel(){
            return strengthLevel;
        };
};

//Defined Graph Class
class Graph{
    private:
        int **adjMatrix;//Initialize adjacency matrix
        int numberVertices;//Initialize number of vertices
        int xDistance;//Initialize x distance from one vertex to other
        int yDistance;//Initialize y distance from one vertex to other
        int squaredDistance;//Initialize squared distance from one vertex to other
        int sourceVertex;//Initialize source vertex
    public:
        //Constructor of Graph
        Graph(int number, int sourceNode){
            numberVertices = number;
            sourceVertex = sourceNode;
            adjMatrix = new int*[numberVertices];//Create an adjacency matrix with the number of rows equal to the number of vertices
            for (int i = 0; i < numberVertices; i++)
            {
                adjMatrix[i] = new int[numberVertices];//Create an adjacency matrix with the number of columns equal to the number of vertices
                //Initialize edges 0 
                for (int j = 0; j < numberVertices; j++)
                {
                    adjMatrix[i][j] = 0;
                }
            }
        };

        //Set edges between vertices
        void setEdges(Vertex *vertices){
            for (int i = 0; i < numberVertices; i++){
                for (int j = 0; j < numberVertices; j++){
                    if (i == j) 
                    {
                        adjMatrix[i][j] = 0;
                        break;
                    }
                    xDistance = abs(vertices[i].get_xCoordinate() - vertices[j].get_xCoordinate());//Calculate the difference of the x-coordinates of the two vertices
                    yDistance = abs(vertices[i].get_yCoordinate() - vertices[j].get_yCoordinate());//Calculate the difference of the y-coordinates of the two vertices
                    squaredDistance = pow(xDistance, 2) + pow(yDistance, 2);//Sum the x-coordinate distance squared and the y-coordinate distance squared for the two vertices
                    //If the squared distance is less than or equal to the strength level of two vertices, set the edge between the two vertices
                    if (squaredDistance <= vertices[i].get_strengthLevel() && squaredDistance <= vertices[j].get_strengthLevel())
                    {
                        adjMatrix[i][j] = 1;
                        adjMatrix[j][i] = 1;  
                    }
                }
            }
        };

        //Write graph representation into an output file
        void printGraph(ofstream &graph){
            graph << "Graph:" << endl;
            for (int i = 0; i < numberVertices; i++)
            {
                for (int j = 0; j < numberVertices; j++)
                {
                    graph << adjMatrix[i][j] << " ";
                }
                graph << endl;
            }
        };

        //Breadth First Search Algorithm
        void BreadthFirstSearch(int source, vector<int> &distance, vector<int> &predecessor){
            vector<bool> visited(numberVertices, false);//Initialize a vector called visited with number of vertices and initalized as false
            queue<int> q;//Initialize a queue called q
            q.push(source);//Push source vertex into the queue
            visited[source] = true;//Set source vertex as visited
            distance[source] = 0;//Set distance as 0
            int visitedVertex;
            while(!q.empty()){
                visitedVertex = q.front();//Set visited vertex as first element of queue
                q.pop();//Pop a vertex from the queue
                for (int i = 0; i < numberVertices; i++)
                {
                    //If visited vertex and the vertex selected have edge and the selected vertex has not yet been visited, do the following
                    if(adjMatrix[visitedVertex][i] == 1 && (!visited[i])){
                        q.push(i);//Push this vertex into the queue
                        distance[i] = distance[visitedVertex] + 1;//Set the distance by adding one to the distance of the parent node
                        predecessor[i] = visitedVertex;//Set parent of a vertex
                        visited[i] = true;//Set this vertex as visited
                    }
                }
            }
        };

        //Find shortest path to reach target point using Breadth First Search Algorithm and write path into an output file
        void findShortestPath(int source, int destination, ofstream &bfs){
            vector<int> distance(numberVertices, -1);//Initialize a vector called distance with number of vertices and initalized as -1
            vector<int> predecessor(numberVertices, -1);//Initialize a vector called predecessor with number of vertices and initalized as -1
            BreadthFirstSearch(source, distance, predecessor);//Call Breadth First Search function
            stack<int> st;//Initialize a stack called st
            //Push vertices from destination to source into the stack 
            while(predecessor[destination] != -1){
                st.push(destination);
                destination = predecessor[destination];
            }
            st.push(destination);
            int pathLength = st.size() - 1;
            bfs << "BFS:" << endl;
            //Write shortest path from source vertex to target vertex into a file
            //Write -1 if destination vertex cannot be reached
            if(pathLength != 0){
                bfs << pathLength << " ";
                while (st.size() > 1){
                    bfs << st.top()<< "->";
                    st.pop();
                }
                bfs << st.top() << endl;
            }
            else{
                bfs << "-1" << endl;
            }
        };

        //Check whether the graph contains a cycle or not
        bool containsCycle(int vertex, vector<bool>& visited, vector<int>& predecessor, vector<int>& savedPath){
            visited[vertex] = true;//Set the vertex as visited
            for (int i = 0; i < numberVertices; i++){
                //If source vertex and the vertex have edge and the predecessor of the vertex is not source vertex, save path and return true
                if (adjMatrix[vertex][sourceVertex] == 1 && (predecessor[vertex] != sourceVertex)){
                    savedPath.push_back(sourceVertex);
                    savedPath.push_back(vertex);
                    while(predecessor[vertex] != -1){
                        savedPath.push_back(predecessor[vertex]);
                        vertex = predecessor[vertex];
                    }
                    return true;
                }
                //If vertex and the vertex selected have edge and the selected vertex has not yet been visited, call this function recursively
                else if (adjMatrix[vertex][i] == 1 && (!visited[i])){
                    predecessor[i] = vertex;//Set predecessor of selected vertex as vertex
                    //Call containsCycle function recursively, if the graph contains a cycle return true
                    if(containsCycle(i, visited, predecessor, savedPath)){
                        return true;
                    }
                }
            }
            return false;
        };

        //Depth First Search Algorithm
        void DepthFirstSearch(int start, ofstream &dfs){
            vector<bool> visited(numberVertices, false);//Initialize a vector called visited with number of vertices and initalized as false
            vector<int> predecessor(numberVertices, -1);//Initialize a vector called predecessor with number of vertices and initalized as -1
            visited[start] = true; //Set source vertex as visited
            vector<int> savedPath;//Initialize a vector called saved path
            for (int i = 0; i < numberVertices; i++){
                //If starting vertex and the vertex selected have edge and the selected vertex has not yet been visited, do the following
                if (adjMatrix[start][i] == 1 && (!visited[i])){
                    predecessor[i] = start;//Set predecessor of vertex selected as starting vertex 
                    //If the graph contains a cycle, write path into a file
                    if (containsCycle(i, visited, predecessor, savedPath)){
                        dfs << "DFS:" << endl;
                        dfs  << savedPath.size()-1 << " ";
                        while(savedPath.size() > 1){
                            dfs << savedPath.back() << "->";
                            savedPath.pop_back();
                        }
                        dfs << savedPath.back();
                        dfs << endl;
                        break;
                    }
                    //If the graph does not contain a cycle, write -1 into a file
                    else{
                        dfs << "DFS:" << endl;
                        dfs << "-1" << endl;
                        break;
                    }
                }
            }
        };

        //Destructor of Graph
        ~Graph(){
            for(int i = 0; i < numberVertices; i++){
                delete[] adjMatrix[i];
            }
            delete[] adjMatrix;
        };
};

int main(int argc, char **argv){
    string input = argv[1];//Get the input file from the command line
    fstream file(input, ios::in);//Define the input file as file
    ofstream graph("graph.txt", ios::out);//Define the output of graph representation file as output
    ofstream bfs("bfs.txt", ios::out);//Define the output of BFS algorithm file as bfs
    ofstream dfs("dfs.txt", ios::out);//Define the output of DFS algorithm file as dfs
    
    int number, source_node, target_node;//Initialize number of vertices, source node and target node
    file >> number >> source_node >> target_node;//Read number of vertices, source node and target node from file 
    Vertex *vertices = new Vertex[number];//Create vertices with given number
    //Call constructor function with x-coordinate, y-coordinate, strength level as inputs
    for (int i = 0; i < number; i++){
        int x, y, strength;
        file >> x >> y >> strength;
        vertices[i] = Vertex(x, y, strength);
    }

    Graph g(number, source_node);//Create a graph using adjacency matrix
    g.setEdges(vertices);//Check for edge between nodes and add edge if any
    g.printGraph(graph);//Call function to write graph into a file 
    graph.close();//Close graph file
    g.findShortestPath(source_node, target_node, bfs);//Find shortest path using BFS algorithm
    bfs.close();//Close bfs file
    g.DepthFirstSearch(source_node, dfs);//Find a cycle using DFS algorithm
    dfs.close();//Close dfs file,

    exit(0);
}