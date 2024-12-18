#cmake链接静态库

cmake_minimum_required(VERSION 3.20)
project(test_xlog)
#指定头文件查找路径 
include_directories("../xlog")
# 指定库查找路径  window自动找 ../xlog/build/Debug  ../xlog/build/Release
link_directories("../xlog/build")
add_executable(test_xlog test_xlog.cpp)
# 指定加载的库
target_link_libraries(test_xlog xlog)

