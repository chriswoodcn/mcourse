#401cmake_target_include/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_target_include)

# WRITE 写文件 清空原数据，如果文件不存在则创建
file(WRITE a.cpp [=[ 
#include <iostream>
void A()
{
    std::cout<<"In A "<<A_VAR<<std::endl;
}
]=]
)

# 静态库
add_library(A STATIC a.cpp)

#[[
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
]]
# PUBLIC  改变 INCLUDE_DIRECTORIES INTERFACE_INCLUDE_DIRECTORIES
# INCLUDE_DIRECTORIES 当前目标使用的属性

# INTERFACE_INCLUDE_DIRECTORIES 依赖当前目标所使用得属性
# 相对路径会自动转为绝对路径
target_include_directories(A PUBLIC "/A_PUBLIC")

# PUBLIC  改变 INCLUDE_DIRECTORIES 
target_include_directories(A PRIVATE "/A_PRIVATE")

# INTERFACE 改变 INTERFACE_INCLUDE_DIRECTORIES
target_include_directories(A INTERFACE "/A_INTERFACE")

#设定A库的宏
target_compile_definitions(A PUBLIC A_VAR=123)


#打印属性
include(CMakePrintHelpers)
cmake_print_properties(TARGETS A PROPERTIES
INCLUDE_DIRECTORIES
INTERFACE_INCLUDE_DIRECTORIES
)



# B->A
file(WRITE b.cpp [=[ 
#include <iostream>
void A();
void B(){
    A();
    std::cout<<"In B "<<A_VAR<<std::endl;
}
]=]
)
add_library(B STATIC b.cpp)
target_link_libraries(B PUBLIC A)
target_include_directories(B PUBLIC "/B_PUBLIC")

#设定B库的宏 STATIC 标志 B库编译时不需要，依赖B库的需要
target_compile_definitions(B INTERFACE STATIC=1)

# 不能打印继承的属性
cmake_print_properties(TARGETS B PROPERTIES
INCLUDE_DIRECTORIES
INTERFACE_INCLUDE_DIRECTORIES
)

#cmake原生属性调试接口
set(CMAKE_DEBUG_TARGET_PROPERTIES 
INCLUDE_DIRECTORIES
INTERFACE_INCLUDE_DIRECTORIES
)

file(WRITE main.cpp [=[
#include <iostream>
int main()
{
    void B();
    B();
    std::cout<<"In main "<<STATIC<<std::endl;
    return 0;
}
]=]
)

# A public interface =>B =>main
# main->B->A
add_executable(main main.cpp)
target_link_libraries(main PUBLIC B)



















#[[


target_link_libraries(<target>
                      <PRIVATE|PUBLIC|INTERFACE> <item>...
                     [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
]]