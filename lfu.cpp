
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int key;
    int value;
    int freq;
    Node *next;
    Node *prev;
    Node(int k, int v)
    {
        key = k;
        value = v;
        freq = 1;
        next = NULL;
        prev = NULL;
    }
};

class DLList{
    public:
    Node *head;
    Node *tail;
    int size;

    DLList(){
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail-> prev = head;
        size = 0;
    }
    public:
    void addNode(Node* node){
        Node *nextNode = head->next;
        head->next = node;
        node->prev = head;
        node->next = nextNode;
        nextNode->prev = node;
        size++;
    }

    void removeNode(Node* node){
        Node *nextNode = node->next;
        Node *prevNode = node->prev;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        size--;
    }
    public:
    Node* removeTail(){
        Node *node = tail->prev;
        removeNode(node);
        return node;
    }
};

class LFUCache{
    public:
        int minFreq = 0;
        map<int, Node *> keyNode;
        map<int, DLList *> freqMap;
        int capacity;
        int cnt;

        LFUCache(int cap)
        {
            cnt = 0;
            capacity = cap;
        }

    void updateFreq(Node* node){

        int currFreq = node->freq;

        freqMap[currFreq]->removeNode(node);

        if(currFreq==minFreq and freqMap[currFreq]->size==0){
            minFreq++;
        }
        node->freq++;
        DLList *currentList = freqMap[node->freq];
        if(!currentList){
            currentList = new DLList();
            freqMap[node->freq] = currentList;
        }
        currentList->addNode(node);
    }
    int get(int key){

        if(keyNode.find(key)!=keyNode.end()){

            Node *node = keyNode[key];
            updateFreq(node);
            return node->value;
        }
        return -1;
    }


    void put(int key,int value){
        if(capacity==0)
            return;
        if(keyNode.find(key)!=keyNode.end()){
            Node *node = keyNode[key];
            node->value = value;
            updateFreq(node);
            return;
        }
        if(cnt==capacity){
            DLList *minFreqList = freqMap[minFreq];
            Node* del = minFreqList->removeTail();
            keyNode.erase(del->key);
            cnt--;
        }
        Node *newNode = new Node(key, value);
        minFreq = 1;
        DLList *list = freqMap[1];
        if(!list){
            list = new DLList();
            freqMap[1] = list;
        }
        list->addNode(newNode);
        cnt++;
        keyNode[key] = newNode;
        return;
    }
};




int main(){

    LFUCache lfu(3);

    lfu.put(3, 5);
    lfu.put(4, 4);
    lfu.put(4, 8);

    cout << lfu.get(1) << endl;
    cout << lfu.get(3);
    cout << endl
         << lfu.get(4);
    lfu.put(1, 7);
    lfu.get(1);
    lfu.put(2, 6);
    cout<<endl<<lfu.get(3);
}
