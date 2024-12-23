# 208cmake_foreach_while/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_foreach_while)

#[[
foreach(<loop_var> <items>)
  <commands>
endforeach()
]]
# 遍历范围 从0开始 到stop结束  0 1 2 3 4 5
# #foreach(<loop_var> RANGE <stop>)
set(out "")
foreach(var RANGE 5)  # 0 1 2 3 4 5
    #message("var = ${var}")
    string(APPEND out ${var} " ")
endforeach()
message("out = ${out}")
# foreach(<loop_var> RANGE <start> <stop> [<step>])
foreach(var RANGE  1 3)
message(${var})
endforeach()
set(out "")
# 遍历范围从 0 到50 每次加5
foreach(var RANGE 0 50 5) # 0 5 10 15 20 25 30 35 40 45 50
    string(APPEND out ${var} " ")
endforeach()
message("out = ${out}")

# foreach(<loop_var> IN [LISTS [<lists>]] [ITEMS [<items>]])
# 遍历list数组
set(args "a" "b" "c" "d" "e")
foreach(var IN LISTS args)
    message(${var})
endforeach()
foreach(var IN ITEMS ${args}) # 必须是list值
    message(${var})
endforeach()
foreach(var IN ITEMS "1;2;3;4") # 数组格式的字符串不支持
    message(${var})
endforeach()

foreach(var IN ITEMS 1;2;3;4)
    message(${var})
endforeach()

#按次序遍历多个list 可实现list按条件拼接
set(A "0;1;2;3")
set(B "4;5;6;7")
set(out "")
foreach(var IN LISTS A B)
    string(APPEND out ${var} " ")
endforeach()
message("LISTS:${out}")

# 同步遍历多个list
# foreach(<loop_var>... IN ZIP_LISTS <lists>)
set(arr1 "1;2;3;4;5;6;7")
set(arr2 "A;B;C;D;E;F;G")
foreach(var IN ZIP_LISTS arr1 arr2)
    message("${var_0}:${var_1}")
endforeach()

foreach(var1 var2 IN ZIP_LISTS arr1 arr2)
    message("${var1} - ${var2}")
endforeach()
message("-----------------------------------------")
# break() continue()
foreach(var RANGE 100) # 0...100
    #取余为3显示数字，其他显示.
    math(EXPR re "${var} % 3") # 0是false 其他是true
    if(NOT re) #=0
        message(${var})
        continue()# 本次循环结束
    endif()
    #大于50退出
    if(var GREATER 50)
        break() #整个foreach循环结束
    endif()
    message(".")
endforeach()

#[[
while(<condition>)
  <commands>
endwhile()
]]
# 防止死循环
set(var 1)
while(var)
    math(EXPR var "${var}+1")
    math(EXPR re "${var} % 10 ")
    if(re) # ！=0
        continue()
    endif()

    message(${var})
    if(var GREATER 100)
        set(var 0) # break();
    endif()
endwhile()














