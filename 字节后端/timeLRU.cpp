#include <iostream>
#include <unordered_map>
#include <ctime>

using namespace std;

struct DLinkedNode
{
    int key,value;
    time_t expiryTime;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(int k,int v,time_t t):key(k),value(v),expiryTime(t),prev(nullptr),next(nullptr){};
};

class LRUCache
{
    public:
        LRUCache(int capacity):head(nullptr),tail(nullptr)
        {
            this->capacity=capacity;
            this->start_time=time(0);
        }

        int get(int key)
        {
            if(!cache.count(key)) return -1;
            DLinkedNode* node=cache[key];
            if(isExpired(node->expiryTime))
            {
                removeNode(node);
                cache.erase(key);
                return -1;
            }

            moveToHead(node);
            return node->value;
        }

        void put(int key,int value, time_t ttl)
        {
            if(cache.count(key))
            {
                DLinkedNode *node=cache[key];
                node->value=value;
                node->expiryTime=time(0)+ttl;
                moveToHead(node);
            }
            else
            {
                DLinkedNode* node=new DLinkedNode(key,value,time(0)+ttl);
                if(cache.size()>=capacity)
                {
                    cache.erase(tail->key);
                    removeNode(tail);
                }
                addNode(node);
                cache[key]=node;
            }
        }

    // 打印整个链表缓存
        void printCache() {
            DLinkedNode* current = head;
            while (current != nullptr) {
                cout << "Key: " << current->key << ", Value: " << current->value << ", Expiry Time: " << current->expiryTime-start_time << endl;
                current = current->next;
            }
        }

    private:
        unordered_map<int,DLinkedNode*> cache;
        DLinkedNode* head;
        DLinkedNode* tail;
        int capacity;
        int start_time;

        bool isExpired(time_t expiryTime)
        {
            return time(0)>expiryTime;
        }

        void addNode(DLinkedNode *node)
        {
            node->next=head;
            node->prev=nullptr;
            if(head!=nullptr)
            {
                head->prev=node;
            }
            head=node;
            if(tail==nullptr)
            {
                tail=node;
            }
        }

        void removeNode(DLinkedNode *node)
        {
            if(node->prev!=nullptr)
            {
                node->prev->next=node->next;
            }
            else
            {
                head=node->next;
            }

            if(node->next!=nullptr)
            {
                node->next->prev=node->prev;
            }
            else
            {
                tail=node->prev;
            }
            delete node;
        }

        void moveToHead(DLinkedNode *node)
        {
            if(node==head) return;
            removeNode(node);
            addNode(node);
        }

};

int main() {
    LRUCache cache(3);

    cache.put(1, 10, 5);  // 插入键1, 值10, 过期时间5秒
    cache.put(2, 20, 5);  // 插入键2, 值20, 过期时间5秒
    cache.put(3, 30, 5);  // 插入键3, 值30, 过期时间5秒

    cache.printCache();  // 打印缓存状态

    _sleep(6 * 1000);  // 等待6秒，使键1、2、3过期
    cout << cache.get(1) << endl;  // 应输出-1，因为已经过期

    cache.printCache();  // 打印缓存状态

    cache.put(4, 40, 5);  // 插入键4, 值40, 过期时间5秒

    cache.printCache();  // 打印缓存状态

    return 0;
}