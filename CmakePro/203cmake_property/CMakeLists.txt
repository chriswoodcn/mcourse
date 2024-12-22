#203cmake_property/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(cmake_property)
#[[
set_property(<GLOBAL                      |
              DIRECTORY [<dir>]           |
              TARGET    [<target1> ...]   |
              SOURCE    [<src1> ...]
                        [DIRECTORY <dirs> ...]
                        [TARGET_DIRECTORY <targets> ...] |
              INSTALL   [<file1> ...]     |
              TEST      [<test1> ...]     |
              CACHE     [<entry1> ...]    >
             [APPEND] [APPEND_STRING]
             PROPERTY <name> [<value1> ...])

get_property(<variable>
             <GLOBAL             |
              DIRECTORY [<dir>]  |
              TARGET    <target> |
              SOURCE    <source>
                        [DIRECTORY <dir> | TARGET_DIRECTORY <target>] |
              INSTALL   <file>   |
              TEST      <test>   |
              CACHE     <entry>  |
              VARIABLE           >
             PROPERTY <name>
             [SET | DEFINED | BRIEF_DOCS | FULL_DOCS])

define_property(<GLOBAL | DIRECTORY | TARGET | SOURCE |
                 TEST | VARIABLE | CACHED_VARIABLE>
                 PROPERTY <name> [INHERITED]
                 [BRIEF_DOCS <brief-doc> [docs...] ]
                 [FULL_DOCS <full-doc> [docs...] ]
                 [INITIALIZE_FROM_VARIABLE <variable>])     

]]

# 全局属性
#设置全局属性
set_property(GLOBAL PROPERTY TEST_GLOBAL "test global 001")

#获取全局属性
get_property(val GLOBAL PROPERTY TEST_GLOBAL)
message("TEST_GLOBAL = ${val}")

#访问子目录中的全局属性
add_subdirectory(sub1)
get_property(val GLOBAL PROPERTY SUB1_GLOBAL)
message("SUB1_GLOBAL = ${val}")


#APPEND APPEND_STRING
# APPEND 数组方式添加 TEST_APPEND = append 001;append 002;append 003 
set_property(GLOBAL APPEND PROPERTY TEST_APPEND "append 001")
set_property(GLOBAL APPEND PROPERTY TEST_APPEND "append 002")
set_property(GLOBAL APPEND PROPERTY TEST_APPEND "append 003")
get_property(val GLOBAL PROPERTY TEST_APPEND)
message("TEST_APPEND = ${val}")


# APPEND_STRING 字符串拼接 append string 001 append string 002 append string 003
set_property(GLOBAL APPEND_STRING PROPERTY TEST_APPEND_STRING "append string 001 ")
set_property(GLOBAL APPEND_STRING PROPERTY TEST_APPEND_STRING "append string 002 ")
set_property(GLOBAL APPEND_STRING PROPERTY TEST_APPEND_STRING "append string 003 ")
get_property(val GLOBAL PROPERTY TEST_APPEND_STRING)
message("TEST_APPEND_STRING = ${val}")


#get_property SET | DEFINED 
set_property(GLOBAL PROPERTY P1 "p1")
get_property(var GLOBAL PROPERTY P1)
message("P1 SET = ${var}")
if(var)
    message("P1 is set")
else()
    message("P1 not set")
endif()
#只有调用define_property之后才会为1
get_property(var GLOBAL PROPERTY P1 DEFINED)
message("P1 DEFINED = ${var}")
if(NOT var)
    message("P1 not defined")
endif()

#定义属性 不需要赋值
define_property(GLOBAL PROPERTY TEST_DEF  BRIEF_DOCS "p1 brief docs")
get_property(var GLOBAL PROPERTY TEST_DEF DEFINED )
message("TEST_DEF DEFINED = ${var}")

#获取属性概要说明BRIEF_DOCS
get_property(var GLOBAL PROPERTY TEST_DEF BRIEF_DOCS )
message("TEST_DEF BRIEF_DOCS = ${var}")

#目录属性
set_property(DIRECTORY . PROPERTY DIR1 "dir001")
get_property(var DIRECTORY . PROPERTY DIR1)
message("DIR1 = ${var}")

#拿到子目录sub1的属性
get_property(var DIRECTORY sub1 PROPERTY DIR1)
message("sub1 DIR1 = ${var}")

#文件属性
set_property(SOURCE main.cpp PROPERTY S1 "s1 value")
get_property(var SOURCE main.cpp PROPERTY S1)
message("SOURCE S1 = ${var}")

# cmake传递变量给c++
# cmake 预置属性 COMPILE_DEFINITIONS    传递预处理变量（宏变量） -DPARA1 1234
set_property(SOURCE main.cpp PROPERTY COMPILE_DEFINITIONS "PARA1=1234")
add_executable(${PROJECT_NAME} main.cpp)
