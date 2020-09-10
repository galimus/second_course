#include <exception>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <list>
#include <unordered_map>

template <typename T, typename KeyT = int>
class  cache_t {
public:
    size_t sz_;
    std::list<T> cache_;
    typedef typename std::list<T>::iterator ListIt;
    std::unordered_map<int, ListIt> hash_;
    bool full() const {
               return (cache_.size() == sz_);
            }
    
    bool lookup(int elem) {
        auto hit = hash_.find(elem);
        if (hit == hash_.end()) {
            if (full()) {
               hash_.erase(cache_.back());
                cache_.pop_back();
            }
            cache_.push_front(elem);
            hash_[elem] = cache_.begin();
            return false;
        }
        auto eltit = hit->second;
        if (eltit != cache_.begin())
            cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
        return true;
    }
    
};



int main() {
    int hits = 0;
    int n, m;
    
    std::cin >> m >> n;
   
    cache_t<int> c{static_cast<size_t>((m))};
    
    for (int i = 0; i < n; ++i) {
        int q;
        std::cin >> q;
      
        if ( std::cin.good () == false) {
            throw std::runtime_error("ERROR");
        }
        if (c.lookup(q))
            hits += 1;
    }
    
    std::cout << hits << std::endl;
}

