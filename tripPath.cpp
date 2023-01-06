#include <iostream>
#include <string>
#include <vector>
#include <cstring>  

using namespace std;

template <typename T>
struct SkipList{
    T city;
    SkipList* next;
    SkipList* skip;
    
    SkipList(const T city, SkipList<T>* n = nullptr, SkipList<T>* s = nullptr)
        : city(city), next(n), skip(s){}
};

void deleteList(SkipList<std::string>* list){
    while(list){
        SkipList<std::string>* temp = list;
        list = list->next;
        delete temp;
    }
}

void printList (SkipList<std::string>* list){
    while(list){
        std::cout<<list->city<<" ";
        list = list->next;
    }
    std::cout<<std::endl;
}

SkipList<std::string>* toList(std::vector<std::string> vectorCities, int numberOfCities){
    if (vectorCities.empty() || numberOfCities == 0){
        return nullptr;
    }
    SkipList<std::string>* first = new SkipList<std::string>(vectorCities[0]);
    SkipList<std::string>* current = first;
    for(size_t i = 1; i < numberOfCities; i++){
        current->next = new SkipList<std::string>(vectorCities[i]);
        current = current->next;
    }
    return first;
}

void printSkipList(SkipList<std::string>* list){
    while(list){
        cout<<list->city<<" ";
        if(list->skip != nullptr){
            list = list->skip;
        }else{
        list = list->next;}
    }
    cout<<endl;
}

std::vector<std::string> findShortestPath(std::vector<std::string> wantToVisitVector, SkipList<std::string>* list){
    std::vector<std::string> shorterPath;
    SkipList<std::string>* saved = list;
    int i = 0;
    if(list == nullptr){
        return {};
    }
    std::cout<<list->city<<" ";
    shorterPath.push_back(list->city);
    list = list->next;

    while(list != nullptr){
        if(list->city == wantToVisitVector[i]){
            std::cout<<list->city<<" ";
            shorterPath.push_back(wantToVisitVector[i]);
            i++;
        }
        if(list->skip == nullptr){
            if(list->city != wantToVisitVector[i]){
                std::cout<<list->city<<" ";
                wantToVisitVector.push_back(list->city);
            }
        list = list->next;
        }else if(list->skip != nullptr){
            SkipList<std::string>* temp = list;
            bool cityIsInTheSkip = false;
            while(list->next != temp->skip){
                if(wantToVisitVector[1] == list->city){
                    cityIsInTheSkip = true;
                }
                list = list->next;
            }
            if(cityIsInTheSkip == true){
                list = temp->next;
            }else{
                list = temp->skip;
            }
        }
    }
    return shorterPath;
}

int main()
{
    std::cout<<"Enter the number of cities: ";
    int numberOfCities;
    std::cin>>numberOfCities;
    if(numberOfCities == 0){
        return 0;
    }
    std::string cities;
    std::cout<<"Enter all cities: ";

    std::vector<std::string> vectorCities;
    for (int i = 0; i < numberOfCities; i++){
        std::cin>>cities;
        vectorCities.push_back(cities);
    }
    SkipList<std::string>* list = toList(vectorCities, numberOfCities);
    printList(list);
    
    std::cout<<"Enter direct trips: "<<std::endl;
    std::cout<<"(write end to stop entering direct lines)"<<std::endl;
    std::string direct;
    std::cin>>direct;
    int t = 0;
    SkipList<std::string>* saved = list;
    SkipList<std::string>* temp = list;
    while(direct != "end"){
        for(int i = 0; i < numberOfCities-1; i++){
            if(t == 0 && direct == list->city){
                temp = list;
                t = 1;
                std::cin>>direct;
            }
            if(t == 1 && direct == list->next->city){
                temp->skip = list->next;
                t = 0;
                std::cin >> direct;
                list = saved;
            }else{
                list = list->next;
            }
        }
    }
    
    std::cout<<"Enter what cities you want to visit: "<<std::endl;
    std::cout<<"(write end to stop entering direct lines)"<<std::endl;
    std::string cityToVisit;
    std::vector<std::string> wantToVisitVector;
    std::cin>>cityToVisit;
    
    while(cityToVisit != "end"){
        wantToVisitVector.push_back(cityToVisit);
        std::cin>>cityToVisit;
    }
    list = saved;
    findShortestPath(wantToVisitVector, list);
    
    deleteList(saved);
   
    return 0;
}
