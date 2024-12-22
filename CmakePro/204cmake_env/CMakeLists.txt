#204cmake_env/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_env)
#环境变量使用 全局无缓存变量
#自定义环境变量
set(ENV{MYENV} "test env value")
message("MYENV = $ENV{MYENV}")
add_subdirectory(sub1)
message("SUB_ENV = $ENV{SUB_ENV}")
#系统环境变量
message("USER NAME = $ENV{USER}")
message("PATH = $ENV{PATH}")

