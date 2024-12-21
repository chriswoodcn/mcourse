# 202cmake_cache/sub2/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(sub2)
message("in sub2  VAR_NORMAL = ${VAR_NORMAL}")
message("in sub2 VAR_SUB1 = ${VAR_SUB1}")
# 访问SUB1 中的全局缓存变量
message("== in sub2 VAR_CACHE_SUB1 = ${VAR_CACHE_SUB1}")