#include <iostream>
#include <unordered_map>
using namespace std;

struct DLinkedNode
{
    int key,value;
    DLinkedNode *prev;
    DLinkedNode *next;
    DLinkedNode(int k,int v):key(k),value(v),prev(nullptr),next(nullptr){}
    DLinkedNode(){};
};

class LRUCache {
private:
    int capacity;
    int size;
    DLinkedNode* head;
    DLinkedNode* tail;
    unordered_map<int, DLinkedNode*> cache;
public:
    LRUCache(int capacity) {
        this->capacity=capacity;
        head=new DLinkedNode();
        tail=new DLinkedNode();
        head->next=tail;
        tail->prev=head;
        head->prev=nullptr;
        tail->next=nullptr;
        this->size=0;
    }
    
    void addToHead(DLinkedNode *node)
    {
        node->prev=head;
        node->next=head->next;
        node->next->prev=node;
        head->next=node;
    }

    DLinkedNode* removeNode(DLinkedNode* node)
    {
        node->next->prev=node->prev;
        node->prev->next=node->next;
        return node;
    }
    

    int get(int key) {
        if(!cache.count(key)) return -1;
        DLinkedNode* node=cache[key];
        int value=node->value;
        removeNode(node);
        addToHead(node);
        return value;
    }
    
    void put(int key, int value) {
        if(cache.count(key))
        {
            DLinkedNode* node=cache[key];
            node->value=value;
            removeNode(node);
            addToHead(node);
        }
        else
        {
            DLinkedNode* node=new DLinkedNode(key,value);
            addToHead(node);
            cache[key]=node;
            ++size;
            if(size>capacity)
            {
                DLinkedNode* re=removeNode(tail->prev);
                cache.erase(re->key);
                delete re;
                --size;
            }
        }
    }

    void printLRU()
    {
        DLinkedNode* node=head;
        while(node!=tail->prev)
        {
            node=node->next;
            cout<<node->key<<" "<<node->value<<endl;
        }
        // cout<<endl;
    }
};

int main()
{
    LRUCache cache=LRUCache(5);
    for (size_t i = 0; i < 7; i++)
    {
        cache.put(i,i*10);
    }
    cache.printLRU();
    for (size_t i = 0; i < 3; i++)
    {
        cout<<cache.get(i)<<endl;
    }
    cache.printLRU();
}
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */