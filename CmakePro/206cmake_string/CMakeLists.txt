#206cmake_string/CMakeLists.txt
cmake_minimum_required(VERSION 3.22)
project(cmake_string)

# 取出begin 和end之间的内容test cmake string
set(STR1 "  begin test cmake string end  ")
# 查找的开头字符串
set(BSTR  "begin")
#在${STR1}中 查找${BSTR}的位置存入b
# cmake位置以0开始
string(FIND ${STR1} ${BSTR} b)
message("FIND ${BSTR} POS ${b}")

string(FIND ${STR1} "end" e)
message("FIND end POS ${e}")

#去掉begin字符位置
#获取字符串长度
string(LENGTH ${BSTR} size)
math(EXPR b "${b} + ${size}")
message("b = ${b}")

# e等于开始到结束的长度
math(EXPR length "${e} - ${b}")
message("length = ${length}")

#获取字串 在${STR1字符串${b}位置取${length}长度字符串写入substr
string(SUBSTRING ${STR1} ${b} ${length} substr)
message("SUBSTRING substr = [${substr}]")
#去掉头尾 空格 \t \n \r
string(STRIP ${substr} substr)
message("STRIP substr = [${substr}]")
#转成大写 test cmake string
string(TOUPPER ${substr} substr)
message("TOUPPER substr = [${substr}]")

#字符串追加 TEST CMAKE STRING
string(APPEND substr " append01 " " append02 ")
message("APPEND substr = [${substr}]")

#字符串替换 STRINGappend01append02
# string(REPLACE <match-string> <replace-string> <out-var> <input>...)
string(REPLACE "append" "REPLACE" substr ${substr})
message("REPLACE substr = [${substr}]")
#TEST CMAKE STRINGREPLACE01REPLACE02

#正则表达式匹配
string(REGEX MATCH "[A-Z]+[0-9]+" output ${substr})
message("REGEX MATCH output = [${output}]")

#[[
string JSON
	  string(JSON <out-var> [ERROR_VARIABLE <error-var>]          
        {GET | TYPE | LENGTH | REMOVE}          
        <json-string> <member|index> [<member|index> ...])
	  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
               MEMBER <json-string>          
               [<member|index> ...] <index>)
	  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                SET <json-string>          
                <member|index> [<member|index> ...] <value>)
	  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
                EQUAL <json-string1> <json-string2>)
]]

#测试用json
# json对象 {}  json 数组 [] 
# 格式 key:value
set( tjson
[=[
{
    "webs":{
        "web":[
        {
            "name":"cmake",
            "url":"cmake.org.cn"
        },{
            "name":"ffmpeg",
            "url":"ffmpeg.club"
        }
        ,{
            "name":"tt",
            "url":"tt.club"
        }
        ]
    }
}
]=]
)
message(${tjson})
#[[
string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
       GET <json-string> <member|index> [<member|index> ...])
]]
# 访问webs->web[0]->name
string(JSON var ERROR_VARIABLE evar
        GET ${tjson} webs web 0 name
    )
if(evar)
message(${evar})
endif()
message("webs web 0 = ${var}")    
string(JSON var ERROR_VARIABLE evar
        GET ${tjson} webs web 1 url
    )
message("webs web 1 = ${var}")    
message("evar = ${evar}")

string(JSON var ERROR_VARIABLE evar
        GET ${tjson} webs web2 url
    )
if(${var})
message("webs web2 = ${var}")
else()
message("NOTFOUND")
endif()

message("evar = ${evar}")

#读取json数组长度
#[[
string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
       LENGTH <json-string> [<member|index> ...])
]]
string(JSON web_count ERROR_VARIABLE evar
    LENGTH ${tjson} webs web
)
message("JSON LENGTH = ${web_count}")

#json的增加和修改
#[[
string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
       SET <json-string> <member|index> [<member|index> ...] <value>)
value必须是json
]]
#json的增加
string(JSON set_out SET ${tjson} webs web ${web_count} [=[{
    "name":"cpp",
    "url":"cppds.com"
}]=])

message("set_out = ${set_out}")
#json的修改 SET
string(JSON set_out2 SET ${set_out} webs web 1 [=[{
    "name":"ffmpeg2",
    "url":"ffmpeg.club"
}]=])
message("set_out2 = ${set_out2}")

#json的删除 REMOVE
#[[
string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
       REMOVE <json-string> <member|index> [<member|index> ...])
]]
string(JSON remove_out REMOVE ${set_out2} webs web 0)
string(JSON remove_out REMOVE ${remove_out} webs web 1)
message("remove_out = ${remove_out}")