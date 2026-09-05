#include "kvstore.h"

int main() {
    // 第一次运行：写入数据
    {
        cout << "=== 第一次运行 ===" << endl;
        KVStore db("wal.log");
        db.put(1, "apple");
        db.put(2, "banana");
        db.printAll();
        cout << "数据已写入，程序即将退出..." << endl;
    }  

    // 第二次运行：模拟重启
    {
        cout << "\n=== 第二次运行（模拟重启） ===" << endl;
        KVStore db("wal.log");
        cout << "重启后读到的数据：" << endl;
        db.printAll();
    }

    return 0;
}
