#linux中的shell是内核的一个外层保护工具，负责完成用户与内核之间的交互
#username@hostname:direction$
#whoami
#hostname
#pwd
#多个命令;隔开 多行命令加 \
#history [numberline] #历史命令
#echo $HISTSIZE
#HISTSIZE=1000 #修改历史记录记录数量

#shell中的特殊字符
#1.通配符
# * 匹配任意长度字符
# ？ 匹配一个长度的字符
# [...] 匹配其中指定的一个字符
# [-] 匹配指定一个字符的范围
# [^...] 除了其中指定的字符,都匹配
#2.管道
# | 将之前命令的输出传递到下一个命令中

#输入输出重定向
#改变shell命令或程序的默认的标准输入输出目标，重定向到新的目标
# > file 将file文件重定向为输出源 新建模式
# >> file 将file文件重定向为输出源 追加模式
# < file 将file文件重定向为输入源
# 2> 或者 &> 将命令产生的错误信息输入到文件中 &不管正确还是错误都输出
# 2>> &>> 
# cat 使用标准输入输出设备
# cat > file.txt 输出重定向 用户使用键盘输入字符串enter结束
# cat < file.txt 输入重定向 从文件中读取字符串显示到显示器上

#命令置换
#将一个命令的输入作为另一个命令的参数 
# command1 `command1`  command2的输出将作为command1的参数
#echo Today is `date`
# command1 $(command2)
#echo Today is $(date)

#基本维护命令
#man
# man commandname 查看命令commandname说明
#passwd
# passwd username 已有账户重新修改用户口令
#su
# su username 切换用户 -c 执行一个命令后就结束 -m 保持环境变量不变 - 转换用户身份的同时使用该用户的环境
#echo
# echo [-n] information 标准输出  -n表示输出文字后不换行 提示信息文字可以加单引号也可以不加
#date
# date 输出当前系统时间 -s按照datestr日期格式设置日期
#clear
# clear 清除控制台输出
#df
# df -ahY 查看磁盘空间使用情况  -a 显示所有物理文件系统使用情况 -T显示文件系统文件格式 -h按兆单位 -k按千字节显示
#du
# du 列出目录和文件所使用的磁盘块数，每块占512字节 -a 仅列出空闲文件数 -h列出磁盘使用情况 -s列出总的空闲空间