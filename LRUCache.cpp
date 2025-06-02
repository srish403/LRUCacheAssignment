#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
private:
    int capacity; // maximum number of items cache can hold
    list<pair<int, int>> keyList;  // stores keys and values
    unordered_map<int, list<pair<int, int>>::iterator> cache; // key -> iterator in list

public: // to initialize cache capacity
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
// retrieve the value for the given key
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1; 
        }
        
        keyList.splice(keyList.begin(), keyList, cache[key]);
        return cache[key]->second;
    }
 // update the value for the given key
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
             cache[key]->second = value;
            keyList.splice(keyList.begin(), keyList, cache[key]);
        } else {
            if (keyList.size() == capacity) {
          // cache full(remove the least recently used item at the back)
                int lruKey = keyList.back().first;
                keyList.pop_back();
                cache.erase(lruKey);
            }
            
           //adds new item at the front(most recently used)
            keyList.push_front({key, value});
            cache[key] = keyList.begin();
        }
    }
};

int main() {
    LRUCache lru(2);  //Cache capacity is set to 2
    lru.put(1, 1);
    lru.put(2, 2);
    cout << lru.get(1) << endl;  
    lru.put(3, 3);               
    cout << lru.get(2) << endl;  
    lru.put(4, 4);               
    cout << lru.get(1) << endl;  
    cout << lru.get(3) << endl;  
    cout << lru.get(4) << endl;  

    return 0;
}