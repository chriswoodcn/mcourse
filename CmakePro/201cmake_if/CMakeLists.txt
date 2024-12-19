#201cmake_if/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_if)
#[[
if(<condition>)
  <commands>
elseif(<condition>) # optional block, can be repeated
  <commands>
else()              # optional block
  <commands>
endif()
]]

#[[
if(<常量>) #constant 常量
如果常量是1, ON, YES, TRUE,Y或非零数（包括浮点数），则为真True。
如果常量是0, OFF, NO, FALSE, N, IGNORE, NOTFOUND, 空字符串，或以-NOTFOUND结尾则为假False
命名布尔常量不区分大小写
]]
if(1)
    message("1 is true")
endif()

if(0) #0 false
    message("0 is true?")
else()
    message("0 is false?")
endif()

if(OFF) #false
    message("OFF is true?")
elseif(NO) #false
    message("NO is true?")
else()
    message("OFF NO is false!")
endif()

if() # flase
    message("empty is true?")
else()
    message("empty is false?")
endif()

if(-1)
    message("-1 is true")
endif()
if(333)
    message("333 is true")
endif()
if(0.1)
    message("0.1 is true")
endif()

if(-NOTFOUND)
    message("-NOTFOUND is true")
else()
    message("-NOTFOUND is false")
endif()

#[[
if(<variable>)
如果给定一个定义为非假常量的值的变量，则为真否则为 False，包括变量未定义时。
宏参数不是变量。环境变量if(ENV{some_var})总是会评估为假。
]]
if(VAR_NOT_DEF) #未定义变量为false
    message("VAR_NOT_DEF is true?")
else()
    message("VAR_NOT_DEF is false?")
endif()
set(VAR1_TRUE TRUE)
if(VAR1_TRUE)
    message("VAR1_TRUE is true！")
endif()

#[[
if(<string>)
带引号的字符串计算为 false,除非字符串的值是真正的常量之一
]]

if("TRUE")
    message("string TRUE is true!")
endif()
if("ON")
    message("string ON is true!")
endif()
if("test") #字符串值不是常量真都是false
else()
    message("string test is false")
endif()
if("1234")
    message("string 1234 is true")
endif()


#[[
逻辑运算符
if(NOT <condition>)
如果条件不为真，则为真。
if(<cond1> AND <cond2>)
如果两个条件都是真的，则为真。

if(<cond1> OR <cond2>)
如果任一条件是真的，则为真。

if((condition) AND (condition OR (condition)))
首先评估括号内的条件，然后评估其余条件。
]]

set(VAR_OFF OFF)
if(NOT VAR_OFF) #如果条件不为真，则为真。
    message("NOT VAR_OFF (true)")
endif()

if(TRUE AND ON)
    message("TRUE and ON is true")
endif()

if(TRUE AND OFF)
    message("TRUE and OFF is true?")
else()
    message("TRUE and OFF is false?")
endif()
if(TRUE OR OFF)
    message("TRUE OR OFF is true?")
else()
    message("TRUE OR OFF is false?")
endif()
if(TRUE AND (OFF OR ON))
    message("TRUE AND (OFF OR ON) is true?")
endif()