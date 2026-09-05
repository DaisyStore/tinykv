#ifndef KVSTORE_H
#define KVSTORE_H

#include "skiplist.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class KVStore {
private:
    SkipList skiplist;
    string logFile;

public:
    KVStore(const string& file = "wal.log") : logFile(file) {
        loadFromLog();
    }

    // 写日志（辅助函数）
    void writeLog(const string& line) {
        ofstream out(logFile, ios::app);  // 追加模式
        out << line << endl;
        out.close();
    }

    // 插入/更新
    void put(int key, const string& value) {
        skiplist.insert(key, value);
        writeLog("PUT " + to_string(key) + " " + value);
    }

    // 查询
    bool get(int key, string& value) {
        return skiplist.find(key, value);
    }

    // 删除
    bool remove(int key) {
        bool result = skiplist.remove(key);
        if (result) {
            writeLog("DEL " + to_string(key));
        }
        return result;
    }

    // 从日志恢复数据
    void loadFromLog() {
        ifstream in(logFile);
        if (!in.is_open()) {
            return;  // 没有日志文件，说明是第一次运行
        }

        string line;
        while (getline(in, line)) {
            istringstream iss(line);
            string cmd;
            iss >> cmd;

            if (cmd == "PUT") {
                int key;
                string value;
                iss >> key >> value;
                skiplist.insert(key, value);
            } else if (cmd == "DEL") {
                int key;
                iss >> key;
                skiplist.remove(key);
            }
        }
        in.close();
    }
    // 显示数据
    void printAll() {
        skiplist.display();
    }
};

#endif
