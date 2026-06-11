# C++17 数据结构实现

这个仓库用于实现大学数据结构课程中常见的核心数据结构与算法，使用 C++17 编写，并尽量保持下面几个目标：

- 实现清晰，方便学习和复习
- 保留底层思路，不直接完全交给 STL
- 每个已实现模块都提供 `demo`
- 每个主要模块都提供 `test`

这个项目更偏向「课程学习仓库」，而不是工业级容器库。重点是把常见数据结构系统地实现出来，并整理成一个适合长期维护和放在 GitHub 上展示的项目。

## 已实现内容

### 线性结构

- 顺序表 `SequentialList<T>`
- 单链表 `SinglyLinkedList<T>`
- 双链表 `DoublyLinkedList<T>`
- 跳表 `SkipList<Key, Value>`
- 链式栈 `LinkedStack<T>`
- 链式队列 `LinkedQueue<T>`

### 排序

- 直接插入排序
- 折半插入排序
- 希尔排序
- 冒泡排序
- 快速排序
- 简单选择排序
- 堆排序
- 归并排序
- 计数排序
- 基数排序

### 树与堆

- 二叉树
- 二叉搜索树
- 二叉堆

### 图与集合结构

- 并查集
- 邻接矩阵
- 邻接表
- BFS
- DFS
- Dijkstra 最短路径
- 拓扑排序

### 哈希结构

- 哈希表

## 目录结构

- `include/`：主要实现代码
- `examples/`：每个数据结构或算法模块对应的示例程序
- `tests/`：轻量级测试程序
- `docs/`：补充说明与路线图

## 编译与运行

### 直接编译某个 demo

```powershell
g++ -std=c++17 -I include examples\skip_list_demo.cpp -o skip_list_demo.exe
& .\skip_list_demo.exe
```

### 直接编译某个测试

```powershell
g++ -std=c++17 -I include tests\test_graph.cpp -o test_graph.exe
& .\test_graph.exe
```

### 使用 CMake

```powershell
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## 示例程序

- `examples/sequential_list_demo.cpp`
- `examples/singly_linked_list_demo.cpp`
- `examples/doubly_linked_list_demo.cpp`
- `examples/skip_list_demo.cpp`
- `examples/linked_stack_demo.cpp`
- `examples/linked_queue_demo.cpp`
- `examples/sorting_demo.cpp`
- `examples/binary_tree_demo.cpp`
- `examples/binary_search_tree_demo.cpp`
- `examples/binary_heap_demo.cpp`
- `examples/disjoint_set_demo.cpp`
- `examples/adjacency_matrix_graph_demo.cpp`
- `examples/adjacency_list_graph_demo.cpp`
- `examples/hash_table_demo.cpp`

## 测试程序

- `tests/test_sequential_list.cpp`
- `tests/test_singly_linked_list.cpp`
- `tests/test_doubly_linked_list.cpp`
- `tests/test_skip_list.cpp`
- `tests/test_linked_stack.cpp`
- `tests/test_linked_queue.cpp`
- `tests/test_sorting.cpp`
- `tests/test_tree_and_heap.cpp`
- `tests/test_graph.cpp`
- `tests/test_disjoint_set_and_hash_table.cpp`

## 说明

- 由于很多结构采用了模板写法，所以主要实现放在头文件中。
- 目前保留了 demo 和 test 两套入口：`demo` 更适合展示用法，`test` 更适合验证正确性。
