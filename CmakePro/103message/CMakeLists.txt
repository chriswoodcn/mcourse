# 103message/CMakeLists.txt
#[[ 
2.1 注释
message(arg1 arg2 arg3)
cmake -S . -B build >log 2>&1
]]
cmake_minimum_required(VERSION 3.20)
project(message)

# 2.2 message基础使用
message("参数1")  #测试message
message("参数p1" "参数p2"  #[[注释在message中]] "p3" 123 测试)

#2.3 message高级使用-指定日志级别
# FATAL_ERROR 进程退出，生成退出 打印代码路径和行号 stderr
#message(FATAL_ERROR "TEST FATAL_ERROR")

# SEND_ERROR 进程继续，生成退出 不会生成 add_executable add_library stderr
# 打印代码路径和行号 
message(SEND_ERROR "TEST SEND_ERROR")
add_executable(test_message test_message.cpp)
message("after ERROR")

# WARNING 打印代码路径和行号 stderr
message(WARNING "TEST WARNING")

#NOTICE等同于 none也就是不加  message("TEST NOTICE")  stderr
message("TEST none")
message(NOTICE "TEST NOTICE")

#STATUS 加前缀 --  用户可能感兴趣 stdout
message(STATUS "TEST STATUS")

#VERBOSE 加前缀 -- 默认不显示 用户需要的详细信息 stdout
message(VERBOSE "TEST VERBOSE")

# 设置日志显示级别
# cmake -S . -B build --log-level=VERBOSE

# 标准输出重定向到文件
# cmake -S . -B build --log-level=VERBOSE >> logs/message.`date "+%Y-%m-%d"`.log 

# 标准错误输出重定向到标准输出 
# cmake -S . -B build --log-level=VERBOSE >> logs/message.`date "+%Y-%m-%d"`.log  2>&1

#DEBUG 加前缀 -- 
message(DEBUG  "test DEBUG")

#TRACE 加前缀 -- 
# cmake -S . -B build --log-level=TRACE
message(TRACE "test TRACE")

#2.4 message Reporting checks查找库日志
#[[
CHECK_START 开始记录将要执行检查的消息
CHECK_PASS 记录检查的成功结果
CHECK_FAIL 记录不成功的检查结果
]]
message("=======================2.4=============================")
#开始查找
message(CHECK_START "查找xcpp")
#查找库xcpp的代码
# message消息缩进
set(CMAKE_MESSAGE_INDENT "--")

#嵌套查找
message(CHECK_START "查找xlog")
#查找xlog代码
message(CHECK_PASS "成功")

message(CHECK_START "查找xthreadpool")
message(CHECK_FAIL "失败")

#取消缩进
set(CMAKE_MESSAGE_INDENT "")
#结束查找 查找失败
message(CHECK_FAIL "失败")

