#203cmake_property/sub1/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(sub1)
#全局属性
set_property(GLOBAL PROPERTY SUB1_GLOBAL "sub1 global val")

# 目录属性
set_property(DIRECTORY . PROPERTY DIR1 "sub1 dir1")