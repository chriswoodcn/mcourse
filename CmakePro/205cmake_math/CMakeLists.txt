#[[ cmake math数学运算
	math(EXPR <variable> "<expression>" [OUTPUT_FORMAT <format>])
	"5 * (10 + 13)". 支持 +, -, *, /, %, |, &, ^, ~, <<, >>
	结果必须是64位有符号整数
	输出格式
		HEXADECIMAL
			0x
				0x3e8
		DECIMAL
			十进制数
]]

#205cmake_math/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_math)
set(exp "(3*10) + 5")
math(EXPR out ${exp})
message("${exp} = ${out}") # (3*10) + 5 = 35
math(EXPR out ${exp} OUTPUT_FORMAT DECIMAL) #十进制
message("${exp} = ${out}") #(3*10) + 5 = 35
math(EXPR out ${exp} OUTPUT_FORMAT HEXADECIMAL) #十六进制 0x
message("${exp} = ${out}") # (3*10) + 5 = 0x23

