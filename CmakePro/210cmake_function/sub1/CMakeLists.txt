# 210cmake_function/sub1/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_function_sub1)
function(func_sub1)
    message("in sub1 func")
    math(EXPR sub1_var "${sub1_var} + 1")
    set(sub1_var ${sub1_var} PARENT_SCOPE) #开放给调用者
endfunction()
func_sub1()
func_sub1()
message("sub1_var = ${sub1_var}")
set(sub1_var ${sub1_var} PARENT_SCOPE) #开放给父目录