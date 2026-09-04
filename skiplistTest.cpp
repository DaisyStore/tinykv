#include "skiplist.h"

int main() {
    SkipList sl;
    
    sl.insert(3, "three");
    sl.insert(1, "one");
    sl.insert(5, "five");
    sl.insert(2, "two");
    
    cout << "跳表内容：" << endl;
    sl.display();
    
    string val;
    if (sl.find(3, val)) {
        cout << "找到 key=3, value=" << val << endl;
    } else {
        cout << "未找到 key=3" << endl;
    }
    
    sl.remove(2);
    cout << "删除 key=2 后：" << endl;
    sl.display();
    
    return 0;
}
