# 202cmake_cache/CMakeLists.txt
#[[
set(<variable> <value>... CACHE <type> <docstring> [FORCE])
	type
		BOOL
			ON/OFF 选择框
		FILEPATH
			文件选择
		PATH
			目录选择
		STRING
			字符串
		INTERNAL
			内部变量
	docstring
		变量说明
	FORCE 
		强制修改缓存，不设置第二次调用值不改
]]

cmake_minimum_required(VERSION 3.20)
project(cmake_cache)
#设置缓存变量 字符串类型
set(VAR1 "CACHE VAR1 VALUE1-1 " CACHE STRING  "cache doc")

#缓存变量第二次修改不生效
set(VAR1 "CACHE VAR1 VALUE1-2 " CACHE STRING  "cache doc")

message("VAR1 = ${VAR1}")

# 强制修改缓存 FORCE
set(VAR1 "CACHE VAR1 VALUE1-3 FORCE" CACHE STRING "cache doc" FORCE)

message("VAR1 = ${VAR1}")

# CACHE变量作用域是全局的
# 普通变量的作用域 自身和子模块
set(VAR_NORMAL "test normal")
message("in main")
message("VAR_NORMAL = ${VAR_NORMAL}")
add_subdirectory(sub1) #子目录会获取当前普通变量
add_subdirectory(sub2)

# 无法访问SUB1中的普通变量
message("in main VAR_SUB1 = ${VAR_SUB1}")

# 访问SUB1 中的全局缓存变量
message("== in main VAR_CACHE_SUB1 = ${VAR_CACHE_SUB1}")


#[[
		BOOL
			ON/OFF 选择框
		FILEPATH
			文件选择
		PATH
			目录选择
		STRING
			字符串
		INTERNAL
			内部变量
]]
#BOOl勾选
set(VAR_BOOL1 "ON" CACHE BOOL "VAR bool 001")
set(VAR_BOOL2 "OFF" CACHE BOOL "VAR bool 002")
message("-------------------------------------------")
message("VAR_BOOL1 = ${VAR_BOOL1}")
message("VAR_BOOL2 = ${VAR_BOOL2}")
#选择文件
set(VAR_FILE "filepath" CACHE FILEPATH "var FILEPATH")
#选择文件夹
set(VAR_PATH "PATH" CACHE PATH "var PATH")
#内部缓存变量
set(VAR_INTERNAL "INTERNAL" CACHE INTERNAL "var INTERNAL")

option(OPT1 "opt1 doc" OFF)
option(OPT2 "opt2 doc" ON)

#普通变量
set(NVAR1 "normal var1")

#设置缓存变量覆盖同名普通变量的策略
# OLD 删除同名普通变量
# NEW 不删除普通变量，要访问cache要用 $CACHE{var_name}
cmake_policy(SET CMP0126 NEW)

#cache变量  
set(NVAR1 "cache var1" CACHE STRING "cache doc")

message("NVAR1 = \t ${NVAR1}")
message("CACHE{NVAR1} = \t $CACHE{NVAR1}") #直接查找缓存变量

message("\n\n=================")
#命令行传递缓存变量
#cmake -S . -B build -D PARA1=para001
message("PARA1 = ${PARA1}")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "so or a")
message("BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
message("\n=================")