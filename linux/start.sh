# shell脚本 shell脚本是解释型语言 
# shell脚本的本质是shell命令的有序集合

# 1.建立shell文件
# 2.赋予执行权限 chmod修改权限
# 3.执行shell文件 ./xxx.sh | 加入path路径

# shell变量 
# 允许用户建立变量数据 没有空格 不支持数据类型 任何赋值都解释为一串字符
COUNT=1
echo $COUNT
DATE=`date`
echo $DATE 
# 四种变量 
#1.用户自定义变量
# 建议全大写方便识别 调用前加$xxx 从右向左赋值 可以用unset命令删除变量的赋值
unset COUNT
#2.位置变量即命令行参数 
$0 #与输入的命令行一样 包含脚本文件名
# $1,...$9 分别包含第一个到第九个命令行参数
$# #包含命令行参数的个数
$@ #包含所有命令行参数 $1,...$9 ${10} ${11}
$? #包含前一个命令的退出状态
$* #包含所有命令行参数 $1,...$9 ${10} ${11}
$$ #包含正在执行进程的ID号
#3.预定义变量 
#4.环境变量
#export
#env

# 功能语句
# 说明性语句 #开头 不被解释执行
#! /bin/sh
# 脚本第一行 告诉os用哪种类型的shell来执行该程序
# 功能性语句 任意的shell命令 用户程序或其他shell程序
# read命令
# read var 把读入的数据全赋给var
# read var1 var2 var3 第一个单词赋给var1 第二个单词赋给 var2 其余所有赋给最后一个变量
# 如果执行read语句时标准输入无数据，程序会一直等待，直到有数据或程序终止
# echo不换行 bash + echo -n 或者 sh + echo "xxx \c"
# expr命令 简单整数运算 + - \* / %
expr 12 + 5 \* 3 #27
expr 3 - 8 / 2 #-1
num=9
sum=`expr $num \* 6`
echo $sum #54
#test语句
#可测试三种对象 字符串 整数 文件属性
test "$answer" = "yes" #变量是否为字符串yes
test $num -eq 18 #变量num是否为整数18
test -d tmp #tmp是否为一个目录名
#字符串测试
# s1 = s2 是否完全一样
# s1 != s2 内容是否有差异
# -z s1 s1长度是否为0
# -n s1 s1长度是否不为0
#整数测试
# a -eq b
# a -ne b
# a -gt b
# a -ge b >=
# a -lt b
# a -le b <=
#文件属性测试
# -d name 测试name是否为一个目录
# -f name 测试name是否普通文件
# -L name 测试name是否符号链接
# -b name 测试name是否为一个块设备文件
# -c name 测试name是否为一个字符设备文件
# -p name 测试name是否为一个管道文件
# -S name 测试name是否为一个套接字文件
# -e name 测试name是否存在
# -r name 测试name文件是否存在并可读
# -w name 测试name文件是否存在并可写
# -x name 测试name文件是否存在并可执行
# -s name 测试name文件是否存在且长度不为0
# f1 -nt f2 测试文件f1是否比文件f2 更新
# f1 -ot f2 测试文件f1是否比文件f2 更旧
test -d /etc
echo $? #expect 0  --- true
test  -e $HOME/test.sh 
echo $? #expect 1  --- false
# 结构性语句 

#分支语句 
# if 表达式
# then 命令表
# fi

# if 表达式
# then 命令表1
# elif 表达式
# then 命令表2
# else 命令表3
# fi

# test表达式有2种方式
# if test -f $filename 或者 if [ -f $filename]
# then ...
# fi

# 多路分支
# case 字符串变量 in
#   模式1 | moshi1 | MOSHI1)
#     命令表
#     ;;
#   模式2)
#     命令表
#     ;;
#   *)
#     命令表
# esac

#循环语句

#函数


