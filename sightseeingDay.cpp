#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Graph{
    std::vector<std::string> names;
    std::vector<std::vector<int>> matrix;

    Graph(std::vector<std::string> names, std::vector<std::vector<int>> matrix)
        : names(names), matrix(matrix){}
};

void fillMatrix(Graph* graph){
    int m = graph->matrix.size();
    // std::cout<<"-";
    for(int i = 0; i < graph->names.size(); i++){
        if(i >= m){
            graph->matrix.push_back({});
        }
        for(int j = 0; j < graph->names.size(); j++){
            if(i >= m || j >= m){
                // std::cout<<"%";
            graph->matrix[i].push_back(0);
            // std::cout<<"$";
            }
        }
        // graph->matrix[i][j].push_back(0);
    }
    // std::cout<<"+";
}

void printMatrix(Graph* graph){
    for(int i = 0; i < graph->names.size(); i++){
        std::cout<<graph->names[i]<<" ";
    }
    std::cout<<std::endl;
    for(int i = 0; i < graph->names.size(); i++){
        for(int j = 0; j < graph->names.size(); j++){
        std::cout<<graph->matrix[i][j]<<" ";
    }
    std::cout<<std::endl;}
}

void addVertex(Graph* graph, std::string first, std::string second, int weight){
    int posFirst;
    int posSecond;
    // std::cout<<"=";

    for(int i = 0; i < graph->names.size(); i++){
        if(first == graph->names[i]){
            posFirst = i;
        }else if(second == graph->names[i]){
            posSecond = i;
        }
    }
    // std::cout<<"=";
    fillMatrix(graph);
    graph->matrix[posFirst][posSecond] = weight;
    graph->matrix[posSecond][posFirst] = weight;
    // std::cout<<"=";
}

void findPath(Graph* graph, int timePeriod, int min, int posX, int posY){
    if(!graph){
        return;
    }
    std::cout<<graph->names[posX]<<" ";
    
    
    for(int i = 0; i < graph->names.size(); i++){
        if(graph->matrix[posX][i] != 0 && i != posY){
            posY = i;
            min = min + graph->matrix[posX][posY];
            break;
        }
    }
    int temp = posX;
    posX = posY;
    posY = temp;
    if(min >= timePeriod){
        return;
    }
    findPath(graph, timePeriod, min, posX, posY);
    
}

int main(){
    std::ifstream file("plovdiv.txt"); 
    if (!file.is_open()) 
    {
        std::cout << "Problem while opening the file" << std::endl;
        return 1;
    }
    Graph* graph = new Graph({}, {});
    int pos = 1;
    int numEdges;
    int numVertex;
    std::string tempFirst;
    std::string tempSecond;

    char tempWord[100];

    int min;
    // file.seekg(-1,ios_base::end);
    // file>>tempWord;
    // min = stoi(tempWord);

    // file.seekg(0, ios_base::beg);

    while (!file.eof()) 
    {
        file >> tempWord;
        if(pos == 1){
            numEdges = stoi(std::string(tempWord));
            // std::cout<<numEdges;
            pos++;
        }else if(pos == 2){
            numVertex = stoi(tempWord);
            // std::cout<<numVertex;
            pos++;
        }else{
             if(pos%3 == 0){
                if(int(tempWord[0]) < 49 || int(tempWord[0]) > 57 ){
                tempFirst = tempWord;
                bool isThere = false;
                for(int i = 0; i < graph->names.size(); i++){
                    if(tempFirst == graph->names[i]){
                        isThere = true;
                    }
                }
                if(!isThere){
                    graph->names.push_back(tempFirst);
                }
                pos++;
                }else{
                    min = stoi(tempWord);
                }
             }else if(pos%3 == 1){
                tempSecond = tempWord;
                bool isThere = false;
                for(int i = 0; i < graph->names.size(); i++){
                    if(tempSecond == graph->names[i]){
                        isThere = true;
                    }
                }
                if(!isThere){
                    graph->names.push_back(tempSecond);
                }
                pos++;
             }else if(pos%3 == 2){
                addVertex(graph, tempFirst, tempSecond, stoi(tempWord));
                pos++;
             }
        }
        std::cout << tempWord << std::endl;
    }

    file.close();   
    printMatrix(graph);
    findPath(graph, min, 0, 0, 0);
    delete graph;
    return 0;
}