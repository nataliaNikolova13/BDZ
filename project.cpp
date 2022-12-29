#include <iostream>
#include <string>
#include <vector>
#include <cstring>  
// #include <stringstream>

using namespace std;

template <typename T>
struct SkipList{
    T city;
    SkipList* next;
    SkipList* skip;
    
    SkipList(const T city, SkipList<T>* n = nullptr, SkipList<T>* s = nullptr)
        : city(city), next(n), skip(s){}
};

// template <typename T>
void deleteList(SkipList<std::string>* list){
    while(list){
        SkipList<std::string>* temp = list;
        list = list->next;
        delete temp;
    }
}

// template <typename T>
void printList (SkipList<std::string>* list){
    while(list){
        std::cout<<list->city<<" ";
        list = list->next;
    }
    std::cout<<std::endl;
}

// template <typename T>
SkipList<std::string>* toList(std::vector<std::string> vectorCities, int numberOfCities){
    if (vectorCities.empty() || numberOfCities == 0){
        // cout<<"*";
        return nullptr;
    }
    SkipList<std::string>* first = new SkipList<std::string>(vectorCities[0]);
    SkipList<std::string>* current = first;
    for(size_t i = 1; i < numberOfCities; i++){
        current->next = new SkipList<std::string>(vectorCities[i]);
        current = current->next;
        // cout<<"-";
    }
    // cout<<"+";
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

int main()
{
    std::cout<<"Enter the number of cities: ";
    int numberOfCities;
    std::cin>>numberOfCities;
    std::string cities;
    std::cout<<"Enter all cities: ";
    // 
    std::vector<std::string> vectorCities;
    for (int i = 0; i < numberOfCities; i++){
        std::cin>>cities;
        
        vectorCities.push_back(cities);
        // std::cout<<vectorCities[i]<<std::endl;
    }
    SkipList<std::string>* list = toList(vectorCities, numberOfCities);
    printList(list);
    
    std::cout<<"Enter direct trips: "<<std::endl;
    std::string direct;
    std::cin>>direct;
    // std::string temp;
    int t = 0;
    SkipList<std::string>* saved = list;
    SkipList<std::string>* temp = list;
    while (direct != "end"){
        // cout<<direct<<"-";
        if(t == 1){
            cout<<">";
            for(int i = 0; i < numberOfCities-1; i++){
                if (direct == list->next->city){
                    list->skip = temp;
                    t = 0;
                    cout<<"+";
                }
                // list = list->next;
            }
        }else{
            // temp = direct;
            for(int i = 0; i < numberOfCities-1; i++){
                if (direct == list->next->city){
                    temp = list->next;
                }
            }
            t = 1;
        }
        
        std::cin>>direct;
    }
    
    printSkipList(saved);
    deleteList(saved);
    // strToArr(cities, vectorCities);
    // splitstr(cities, "&&");
    return 0;
}
