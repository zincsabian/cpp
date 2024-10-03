## 介绍

### shared_ptr
shared_ptr利用引用计数来统计某一份内存的引用次数， 通常维护一个 <ptr, count> 的结构
ptr指向某一份内存空间， 解析方式为类型T

### unique_ptr
unique_ptr通过对某个指针的独占（仅移动， 无copy）来实现