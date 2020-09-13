#include<algorithm>
#include <unordered_map>
#include <iostream>
#include <list>
#include <vector>

using namespace std;


class LFUCache {
public:
    unordered_map<int, list<int>> freq_keyslist;
    unordered_map<int, vector<int>> key_value_freq;
    unordered_map<int, list<int>::iterator> key_iterator;
    int min_freq;
    int size;
    int c;
    
    LFUCache(int capacity) {
        c = capacity;
        size = 0;
        min_freq = 0;
        
    }
    
    int get(int key) {
        if(!key_value_freq.count(key)) return -1;
        
        int value = key_value_freq[key][0];
        int freq = key_value_freq[key][1];
        freq_keyslist[freq].erase(key_iterator[key]);
        
        freq_keyslist[freq+1].push_back(key);
        key_value_freq[key][1]++;
        key_iterator[key] = --freq_keyslist[freq+1].end();
        
        if(!freq_keyslist[min_freq].size()) min_freq++;
        
        return value;
    }
    
    void put(int key, int value) {
        if(c<=0) return;
        
        if(get(key) != -1){
            key_value_freq[key][0] = value;
            return;
        }
        
        if(size==c){
           
            int key_to_remove = freq_keyslist[min_freq].front();
            freq_keyslist[min_freq].pop_front();
            key_value_freq.erase(key_to_remove);
            key_iterator.erase(key_to_remove);
        }
        
        key_value_freq[key] = {value, 1};
        freq_keyslist[1].push_back(key);
        key_iterator[key] = --freq_keyslist[1].end();
        min_freq=1;
        if(size < c) size++;
        
    }
};






int main() {
    
    LFUCache cache = *new LFUCache( 2 );
    
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);
    cache.put(3, 3);
    cache.get(2);
    cache.put(4, 4);
    cache.get(1);
    cache.get(3);
    cache.get(4);      
    
}
