# TinyKV

一个基于跳表（SkipList）和 WAL（Write-Ahead Log）的轻量级键值存储引擎，使用 C++ 实现。

## 功能

- 内存跳表索引，支持有序存储和快速查找
- 基本的键值操作：`put` / `get` / `remove`
- WAL 日志持久化，重启后数据可恢复

## 文件结构

| 文件 | 说明 |
|------|------|
| `skiplist.h` | 跳表数据结构实现 |
| `skiplistTest.cpp` | 跳表功能测试 |
| `kvstore.h` | KV 接口与 WAL 持久化 |
| `kvTest.cpp` | KV 基本功能测试 |
| `wal_test.cpp` | 重启恢复测试 |

## 编译运行

```bash
g++ -o wal_test wal_test.cpp
./wal_test
