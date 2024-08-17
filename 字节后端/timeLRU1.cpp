#include <iostream>
#include <unordered_map>
#include <list>
#include <ctime>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (!cache.count(key)) return -1;

        auto it = cache[key];
        if (isExpired(it->second.second)) {
            remove(key);
            return -1;
        }

        kvList.splice(kvList.begin(), kvList, it);
        return it->second.first;
    }

    void put(int key, int value, time_t ttl) {
        if (cache.count(key)) {
            kvList.splice(kvList.begin(), kvList, cache[key]);
            cache[key]->second.first = value;
            cache[key]->second.second = time(0) + ttl;
        } else {
            if (kvList.size() >= capacity) {
                auto last = kvList.back();
                remove(last.first);
            }
            kvList.push_front({key, {value, time(0) + ttl}});
            cache[key] = kvList.begin();
        }
    }

private:
    list<pair<int, pair<int, time_t>>> kvList;
    unordered_map<int, list<pair<int, pair<int, time_t>>>::iterator> cache;
    int capacity;

    bool isExpired(time_t expiryTime) {
        return time(0) > expiryTime;
    }

    void remove(int key) {
        auto it = cache[key];
        kvList.erase(it);
        cache.erase(key);
    }
};

int main() {
    LRUCache cache(3);

    cache.put(1, 10, 5);  // 插入键1, 值10, 过期时间5秒
    cache.put(2, 20, 5);  // 插入键2, 值20, 过期时间5秒
    cache.put(3, 30, 5);  // 插入键3, 值30, 过期时间5秒

    cout << cache.get(1) << endl;  // 应输出10
    _sleep(6*1000);  // 等待6秒，使键1、2、3过期
    cout << cache.get(1) << endl;  // 应输出-1，因为已经过期
    cout << cache.get(2) << endl;  // 应输出-1，因为已经过期
    cout << cache.get(3) << endl;  // 应输出-1，因为已经过期

    cache.put(4, 40, 5);  // 插入键4, 值40, 过期时间5秒
    cout << cache.get(4) << endl;  // 应输出40

    return 0;
}
