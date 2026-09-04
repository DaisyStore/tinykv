#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct Node {
    int key;
    string value;
    vector<Node*> forward;
    
    Node(int k, string v, int level) : key(k), value(v), forward(level, nullptr) {}
};

class SkipList {
private:
    int maxLevel;
    int currentLevel;
    Node* header;
    float probability;
    
    int randomLevel() {
        int level = 1;
        while ((rand() / (double)RAND_MAX) < probability && level < maxLevel) {
            level++;
        }
        return level;
    }
    
public:
    SkipList(int maxLevel = 16, float p = 0.5) 
        : maxLevel(maxLevel), currentLevel(1), probability(p) {
        header = new Node(-1, "", maxLevel);
        srand(time(0));
    }
    
    ~SkipList() {
        Node* p = header;
        while (p) {
            Node* next = p->forward[0];
            delete p;
            p = next;
        }
    }
    
    void insert(int key, string value) {
        vector<Node*> update(maxLevel, nullptr);
        Node* current = header;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        if (update[0]->forward[0] && update[0]->forward[0]->key == key) {
            update[0]->forward[0]->value = value;
            return;
        }
        
        int newLevel = randomLevel();
        if (newLevel > currentLevel) {
            for (int i = currentLevel; i < newLevel; i++) {
                update[i] = header;
            }
            currentLevel = newLevel;
        }
        
        Node* newNode = new Node(key, value, newLevel);
        
        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
    
    bool find(int key, string& value) {
        Node* current = header;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        
        if (current->forward[0] && current->forward[0]->key == key) {
            value = current->forward[0]->value;
            return true;
        }
        return false;
    }
    
    bool remove(int key) {
        vector<Node*> update(maxLevel, nullptr);
        Node* current = header;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        Node* target = update[0]->forward[0];
        if (target && target->key == key) {
            for (int i = 0; i < currentLevel; i++) {
                if (update[i]->forward[i] == target) {
                    update[i]->forward[i] = target->forward[i];
                }
            }
            delete target;
            
            while (currentLevel > 1 && header->forward[currentLevel - 1] == nullptr) {
                currentLevel--;
            }
            return true;
        }
        return false;
    }
    
    void display() {
        Node* current = header->forward[0];
        while (current) {
            cout << current->key << ": " << current->value << endl;
            current = current->forward[0];
        }
    }
};

#endif
