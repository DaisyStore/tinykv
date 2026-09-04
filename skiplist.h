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
    Node* header;  // 哨兵节点
    float probability;
    
    int randomLevel() {  // 随机生成节点的层数
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
        srand(time(0));  // 用时间初始化种子
    }
    
    ~SkipList() {
        Node* p = header;
        while (p) {
            Node* next = p->forward[0];
            delete p;
            p = next;
        }
    }
    
    void insert(int key, string value) {  // 插入一个节点
        vector<Node*> update(maxLevel, nullptr);  // 存目标key的前驱节点
        Node* current = header;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        if (update[0]->forward[0] && update[0]->forward[0]->key == key) {
            update[0]->forward[0]->value = value;  // key已经存在，直接修改value
            return;
        }
        
        int newLevel = randomLevel();
        if (newLevel > currentLevel) {
            for (int i = currentLevel; i < newLevel; i++) {
                update[i] = header;  // 补充前驱节点是header的情况
            }
            currentLevel = newLevel;
        }
        
        Node* newNode = new Node(key, value, newLevel);
        
        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
    
    bool find(int key, string& value) {  // 查找跳表中键为key的节点的value
        Node* current = header;
        
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        
        if (current->forward[0] && current->forward[0]->key == key) {
            value = current->forward[0]->value;  // 返回value
            return true;
        }
        return false;
    }
    
    bool remove(int key) {  // 移除跳表中键为key的节点
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
                if (update[i]->forward[i] == target) {  // 要先做判断，再更新forward[i]
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
    
    void display() {  // 显示跳表中节点的 key、value
        Node* current = header->forward[0];
        while (current) {
            cout << current->key << ": " << current->value << endl;
            current = current->forward[0];
        }
    }
};

#endif
