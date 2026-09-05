#include "kvstore.h"

int main() {
    KVStore db;

    db.put(1, "apple");
    db.put(2, "banana");
    db.put(3, "cherry");

    cout << "当前存储内容：" << endl;
    db.printAll();

    string value;
    if (db.get(2, value)) {
        cout << "查询 key=2，得到：" << value << endl;
    } else {
        cout << "未找到 key=2" << endl;
    }

    db.remove(1);
    cout << "删除 key=1 后：" << endl;
    db.printAll();

    return 0;
}
