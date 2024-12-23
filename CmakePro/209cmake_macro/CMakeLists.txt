# 209cmake_macro/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_macro)
macro(my_macro)
    message("in my macro")
    set(RET 1)
endmacro()

#宏名称大小写不敏感，尽量只用小写
# 调用是将宏代码赋值过来
my_macro()
My_macro()
message("RET = ${RET}")
#固定参数，实参数量要等于或者超过形参
macro(foo arg1 arg2)
    message("arg1 = ${arg1} arg2=${arg2}")  
    if(arg1) # 宏参数不是变量
        message("== arg1 true ==")
    endif()  
    if(${arg1})
        message("\$\{arg1\} true")
    endif()
    endmacro()

foo(TRUE "test")

macro(foo2)
    #参数数量
    message("ARGC = ${ARGC}")

    #参数list
    message("ARGN = ${ARGN}")

    #ARGN不是变量只能取值使用
    foreach(var IN ITEMS ${ARGN})
        message("var = ${var}")
    endforeach()

    message("ARGV0 = ${ARGV0}")
    message("ARGV1 = ${ARGV1}")
    message("ARGV2 = ${ARGV2}")
endmacro()
foo2(1 "test" True)


macro(my_parse)
    message("ARGN = ${ARGN}")
    cmake_parse_arguments(
        "MY"  #前缀
        "LOG;FILE"  #option
        "BIN;LIB"  # 单值
        "TARGETS"  # 多值
        ${ARGN} #参数数组
    )
    message("MY_LOG = ${MY_LOG}")
    message("MY_FILE = ${MY_FILE}")
    message("MY_BIN = ${MY_BIN}")
    message("MY_TARGETS = ${MY_TARGETS}")
    #参数类型传递错误
    message("MY_UNPARSED_ARGUMENTS = ${MY_UNPARSED_ARGUMENTS}" )
    #未传值错误
    message("MY_KEYWORDS_MISSING_VALUES = ${MY_KEYWORDS_MISSING_VALUES}")
endmacro()
my_parse(
LOG "mylog"
BIN ../../bin 
TARGETS "tar1" "tar1" 
LIB
)





