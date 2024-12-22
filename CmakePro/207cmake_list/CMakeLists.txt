# 207cmake_list/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_list)
#list变量初始化
set(src "a" "b" "c" "d;e;f")
message("src = ${src}")
#获取list变量长度
list(LENGTH src length)
message("src length = ${length}")
#list追加写入
list(APPEND  src "g")
list(APPEND  src "h" "i")
message("${length} src = ${src}")

# list访问 下标 0，1，2 。。。 结尾往前 -1 -2 -3 
# src = a;b;c;d;e;f;g;h;i
list(GET src 1 var)
message("GET src 1  = ${var}")
list(GET src 5 var)
message("GET src 5  = ${var}")
list(GET src -1 var)
message("GET src -1  = ${var}")
list(GET src -2 var)
message("GET src -2  = ${var}")

# 拼接所有的节点
list(JOIN src "|" var)
message("JOIN ${var}")
list(JOIN src "" var)
message("JOIN ${var}")

# 取其中一部分数组
list(SUBLIST src  0 3 var)
message("SUBLIST ${var}")

# 查找内容
# src = a;b;c;d;e;f;g;h;i
list(FIND src "d" b) # 3
message("FIND ${b}")

list(LENGTH src length) # 9
math(EXPR e "${length}-${b}") # 9 -3 = 6

list(SUBLIST src ${b} ${e} var) # e 长度
message("SUBLIST ${b} ${e} ${var}")

#插入节点
# src = a;b;c;d;e;f;g;h;i
list(INSERT src 4 "d1")
list(INSERT src 2 "b1")
list(INSERT src 2 "b")
message("INSERT src ${src}")

# 删除和修改节点
# a;b;b;b1;c;d;d1;e;f;g;h;i

#通过节点值删除
list(REMOVE_ITEM src "b")
message("REMOVE src = ${src}")

# a;b1;c;d;d1;e;f;g;h;i
#删除指定位置  e
list(REMOVE_AT src 5)
#重新插入 相当于修改 E
list(INSERT src 5 "E")
message("REMOVE_AT INSERT src = ${src}")
# 
#双向队列操作方式
#后端出队 b1;c;d;d1;E;f;g;h
list(POP_BACK src var)
message("POP_BACK ${var}")
message("src = ${src}")

#前端出队 先进先出 b1;c;d;d1;E;f;g;h
list(POP_FRONT src var)
message("POP_FRONT ${var}")
message("src = ${src}")

#去掉重复元素
set(rsrc "a;b;c;d;d;b;a;z;t;f")
message("rsrc = ${rsrc}")
list(REMOVE_DUPLICATES rsrc)
message("REMOVE_DUPLICATES rsrc = ${rsrc}")

# 数据排序
list(SORT rsrc)
message("SORT rsrc = ${rsrc}")
set(arr "3;23;122;157;1;5;7")
#默认字符串排序
list(SORT arr)
message("arr = ${arr}")

#自然数排序
list(SORT arr COMPARE NATURAL)
message("NATURAL arr = ${arr}")



