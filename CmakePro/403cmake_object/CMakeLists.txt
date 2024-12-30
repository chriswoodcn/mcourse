#403cmake_object/CMakeLists.txt
# 只能在Linux完全测试通过，Windows需要代码加export
cmake_minimum_required(VERSION 3.22)
project(cmake_object)
# a.cpp b.cpp =>a.cpp.o b.cpp.o
# a.cpp.o b.cpp.o =>libtesta.so
# main.cpp  libtesta.so=> main
file(WRITE a.cpp [=[
#include <iostream>
void A(){std::cout<<"A\n";}
]=])

file(WRITE b.cpp [=[
#include <iostream>
void B(){std::cout<<"B\n";}
]=])

file(WRITE main.cpp [=[
#include <iostream>
void A();
void B();
int main()
{
    A();
    B();
    std::cout<<"main\n";
}
]=])

# 添加object对象 testa_obj =》 a.cpp.o b.cpp.o
add_library(testa_obj OBJECT a.cpp b.cpp)


#if(NOT MSVC)
#    target_compile_options(testa_obj PRIVATE "-fPIC")
#endif()

# 是否加-fPIC POSITION_INDEPENDENT_CODE ON添加
set_target_properties(testa_obj PROPERTIES POSITION_INDEPENDENT_CODE ON)


#obj=>so
# 用生成器表达式获取object对象
# $<TARGET_OBJECT:testa_obj> => a.cpp.o b.cpp.o
# add_library SHARED会自动添加-fPIC
add_library(testa SHARED $<TARGET_OBJECTS:testa_obj>)

#测试的执行程序
add_executable(main main.cpp)

#执行程序依赖的库
target_link_libraries(main testa)
