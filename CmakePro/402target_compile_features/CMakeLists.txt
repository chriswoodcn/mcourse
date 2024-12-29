#402target_compile_features/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(compile_features)
file(WRITE main.cpp [=[
int main()
{
    return 0;
}
]=]
)
add_executable(main main.cpp)
# c++ 17
#target_compile_features(main PRIVATE cxx_std_17)
# vs2022 有效 ubuntu 20.04 gcc无效
#target_compile_features(main PRIVATE cxx_std_23)

# 支持的特征数组
message("CMAKE_CXX_COMPILE_FEATURES =  ${CMAKE_CXX_COMPILE_FEATURES} ")
foreach(var IN LISTS CMAKE_CXX_COMPILE_FEATURES)
    message(${var})
endforeach()
#判断当前编译器是否支持此特性
message("--------------------------------------------")
set(f1 cxx_std_23)
if(f1 IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message("${f1} OK!")
    target_compile_features(main PRIVATE ${f1})
else()
    message("${f1} FAILED!")
endif()

