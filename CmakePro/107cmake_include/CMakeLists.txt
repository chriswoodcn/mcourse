#107cmake_include/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project("cmake_include")
message("begin include")

include("cmake/test_cmake.cmake")
include("cmake/test_cmake.cmake")
include("cmake/test_cmake1.cmake" OPTIONAL) #OPTIONAL 可选，文件不存在不报错
include("cmake/test_cmake1.cmake" OPTIONAL  RESULT_VARIABLE ret) # RESULT_VARIABLE 返回值，是否引用成功
message("RESULT_VARIABLE ret= ${ret}") #NOTFOUND
include("cmake/test_cmake.cmake" OPTIONAL  RESULT_VARIABLE ret)
message("RESULT_VARIABLE ret= ${ret}") #导入文件的绝对路径

message("end include")

