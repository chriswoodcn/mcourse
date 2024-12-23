# 210cmake_function/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_function)

macro(mac1 arg1 arg2)
    if(arg2)
        message("macro arg2 = TRUE")
    endif()  
    #return() #调用后当前函数、目录、文件退出
endmacro()
#mac1(1 2)
function(fun1 arg1 arg2)
    if(arg1)
        message("arg1 is true")
        return()
    endif()
    message("IN function fun1 arg1 = ${arg1} arg2 = ${arg2}")
    if(arg2) #函数区别于宏可以当作变量
        message("arg2 = TRUE")
    endif()
    foreach(var IN LISTS ARGN) #遍历所有变参
        message("var = ${var}")
    endforeach()
    
endfunction()
fun1(OFF TRUE "testfunc1" 1 3 ON)
mac1(OFF TRUE "testfunc1")
fun1(ON TRUE "testfunc1" 1 3 ON)


function(fun_var arg1)
    # arg1 参数遍历如果有全局遍历名字一样还是取局部的变量
    message("in fun_var ${arg1}")
    message("var1 = ${var1}")
    set(var1 "fun var") #不能修改外部变量 这一步调用相当于创建了一个局部变量
    set(RET "1" PARENT_SCOPE) # 设定变量作用域到父 （调用函数者、父目录）
endfunction()

set(var1 "main")
set(arg1 "main arg1")
fun_var(123)
message("var1 = ${var1}")
message("RET = ${RET}")

add_subdirectory(sub1)
#可以直接访问子目录中的函数
func_sub1() #父目录重新创建了一套内存空间
message("sub1_var = ${sub1_var}")