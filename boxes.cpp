#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

struct Box{
    std::string name;
    std::vector<std::string> elements;
    std::vector<Box*> boxes;

    Box(std::string name, std::vector<std::string> elements, std::vector<Box*> boxes)
        : name(name), elements(elements), boxes(boxes){};
};

void printBox(Box* box){
    if (!box){
        return;
    }
    std::cout<<box->name<<" ";
    for(int j = 0; j < box->elements.size(); j++){
        std::cout<<box->elements[j]<<" ";
    }
    for(int i = 0; i < box->boxes.size(); i++){
        printBox(box->boxes[i]);
    }
}

void restructure(Box* start, Box* prev){
   if(!start){
    return;
   }
   if(start->elements.empty()){
    if(start->boxes.empty()){
        int p = 0;
        for(int j = 0; j < prev->boxes.size(); j++){
            if(prev->boxes[j]->name == start->name){
                p = j;
            }
        }
        std::swap(prev->boxes[p], prev->boxes[prev->boxes.size() -1]);
        prev->boxes.pop_back();
        return;

    }
    prev->boxes.push_back(start->boxes[0]);
    int p = 0;
    for(int j = 0; j < prev->boxes.size(); j++){
        if(prev->boxes[j]->name == start->name){
            p = j;
        }
    }
    
    std::swap(prev->boxes[p], prev->boxes[prev->boxes.size() -1]);
    prev->boxes.pop_back();
    start = prev;
    restructure(prev->boxes[p], start);
   }
   for(int i = 0; i < start->boxes.size(); i++){
        restructure(start->boxes[i], start);
    }
}

int main(){
    std::stack<Box*> allBoxes;

    Box* plovdicBox = new Box("PlovdivBox", {"Magnet", "Book"}, {});
    allBoxes.push(plovdicBox);
    Box* artBox = new Box("ArtBox", {}, {});
    allBoxes.push(artBox);
    Box* drawings = new Box("Drawings", {"OldPlovdiv"}, {});
    allBoxes.push(drawings);
    Box* theatreBox = new Box("TheatreBox", {}, {});
    allBoxes.push(theatreBox);
    Box* theatreSouvenirs = new Box("TheatreSouvenirs", {}, {});
    allBoxes.push(theatreSouvenirs);
    Box* plates = new Box("Plates", {"DecorativePlate"}, {});
    allBoxes.push(plates);
    Box* bags = new Box("Bags", {}, {});
    allBoxes.push(bags);
    plovdicBox->boxes.push_back(artBox);
    plovdicBox->boxes.push_back(theatreBox);
    artBox->boxes.push_back(drawings);
    theatreBox->boxes.push_back(theatreSouvenirs);
    theatreSouvenirs->boxes.push_back(plates);
    theatreSouvenirs->boxes.push_back(bags);

    Box* StaraZagoraBox = new Box("StaraZagoraBox", {"Postcard"}, {});
    allBoxes.push(StaraZagoraBox);
    Box* Figurines = new Box("Figurines", {"AncientFigurine"}, {});
    allBoxes.push(Figurines);
    Box* Cups = new Box("Cups", {"TraditionalCup"}, {});
    allBoxes.push(Cups);
    StaraZagoraBox->boxes.push_back(Figurines);
    StaraZagoraBox->boxes.push_back(Cups);

    //print struct
    printBox(plovdicBox);
    std::cout<<std::endl;
    restructure(plovdicBox, nullptr);
    printBox(plovdicBox);

    std::cout<<std::endl;
    printBox(StaraZagoraBox);
    std::cout<<std::endl;
    restructure(StaraZagoraBox, nullptr);
    printBox(StaraZagoraBox);

    //deleting
    while(!allBoxes.empty()){
        delete allBoxes.top();
        allBoxes.top() = nullptr;
        allBoxes.pop();
    }
    
    return 0;
}