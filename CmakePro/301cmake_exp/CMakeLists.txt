#301cmake_exp/CMakeLists.txt
cmake_minimum_required (VERSION 3.20)
project (cmake_exp)
add_executable(cmake_exp cmake_exp.cpp)
#[[
逻辑运算符
$<BOOL:string>  
                转换string为0或1。评估0以下任何一项是否为真：
                string是空的，
                string是不区分大小写的等于 0, FALSE, OFF, N, NO, IGNORE, or NOTFOUND, or
                string以后缀结尾-NOTFOUND（区分大小写）。
                否则计算为1。
$<NOT:condition> 取反 0变1 1变0
$<AND:conditions>
$<OR:conditions>

条件表达式
$<condition:true_string>  0返回空串 1 返回true_string
]]  # $<BOOL:OFF>  ==》 0   $<0:TEST1=123>
target_compile_definitions(cmake_exp PUBLIC "$<$<BOOL:ON>:TEST1=123>")

#######################################
#### 测试生成表达式的方式 ###############
### 利用cmake的错误来查看  
# $<AND:1,0>"  
#target_include_directories(cmake_exp PUBLIC "$<AND:1,0>")
#target_include_directories(cmake_exp PUBLIC "$<OR:0,0>")
#set(LIB OFF)
# LIB等于OFF时显示STATIC ON显示空
#target_include_directories(cmake_exp PUBLIC "$<$<NOT:$<BOOL:${LIB}>>:STATIC>")
#在配置阶段不处理生成表达式
#message($<$<NOT:$<BOOL:${LIB}>>:STATIC>)


### 生成一个自定义目标
#cmake生成表达式调试方法（官方）
# cmake -E echo "生成表达式"
#add_custom_target(gen COMMAND ${CMAKE_COMMAND} -E echo "$<$<NOT:$<BOOL:${LIB}>>:STATIC=1>")


# 字符串比较
# $<STREQUAL:string1,string2>
# $<EQUAL:value1,value2>
#target_include_directories(cmake_exp PUBLIC "$<STREQUAL:string1,string1>")
#target_include_directories(cmake_exp PUBLIC "$<EQUAL:123,1>")

# 变量查询
# $<CONFIG:cfgs>
# $<CONFIG> Debug Release 。。
#target_include_directories(cmake_exp PUBLIC "$<CONFIG>")
#$<CONFIG:Debug,Release>配置项式Debug,Release之一返回1
#target_include_directories(cmake_exp PUBLIC "$<CONFIG:Debug,Release>")

# $<PLATFORM_ID:platform_ids> 系统名称  Windows Linux
message("CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
#target_include_directories(cmake_exp PUBLIC "$<PLATFORM_ID:Windows,Linux>")

#$<IF:condition,true_string,false_string>
#set(LIB ON)
#target_include_directories(cmake_exp PUBLIC "$<IF:$<BOOL:${LIB}>,ON_STRING,OFF_STRING>")

set (conf  "Debug")
#set(exp "$<STREQUAL:$<LOWER_CASE:${conf}>,debug>")

#目标相关查询
#生成目标的全路径
#set(exp "$<TARGET_FILE:cmake_exp>")

# 获取目标的属性
#set(exp "$<TARGET_PROPERTY:cmake_exp,NAME>")
#target_include_directories(cmake_exp PUBLIC ${exp})
add_custom_target(gen COMMAND ${CMAKE_COMMAND} -E echo "${exp}")
