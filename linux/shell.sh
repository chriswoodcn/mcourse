#shell介绍
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

#用户管理命令
#/etc/passwd 用户 man 5 /etc/passwd查看释义
#/etc/group 组
#添加用户 sudo adduser username
#/etc/adduser.conf 配置文件
#SKEL模板
#usermod -d /home/newname -l newname oldname 改变用户属性 man usermod
#删除用户 deluser --remove-home username
#添加组 addgroup groupname  
# sudo usermod -g newgroupname username
#删除组 delgroup groupname

#进程管理命令
#ps命令 -A -w -au -aux显示所有包含其他使用者的进程
# 进程状态标识
# r 正在执行中
# s 阻塞状态
# t 暂停状态
# z 不存在但暂时无法消除
# d 不可中断的静止
# < 高优先级的进程
# n 低优先级的进程
# l 有内存分页分配并所在内存中
# + 进程处在前台
#top命令 监视进程
#pstree命令 将所有进程树状图显示
#kill -l查看信号 默认15 software terminate signal
#kill命令 kill [-signal] pid

#文件系统类型和结构
# 文件系统 用于组织和管理计算机存储设备上的大量文件，并提供用户交互接口
# 分类
# - 磁盘文件系统
# - 网络文件系统
# - 专有/虚拟文件系统
# cat /proc/partitions
# 文件系统结构
# linux下 分区属于目录结构 l
# linux将所有硬件视为文件来处理 一旦linux系统可以访问到硬件，就将其上的文件系统挂到目录树中的一个子目录中
# linux文件系统是一个树形分层组织结构
# 基本目录（文件层次结构标准 FHS file hierarchy standard） FHS2.3
# / 根目录
# /bin 存放系统可执行文件 二进制
# /boot 存放linux内核和系统启动文件 包括grub lilo启动器程序
# /dev 存放所有设备文件 包括硬盘 分区 键盘 鼠标 usb tty
# /etc 存放系统所有配置文件
# /home 用户主目录默认位置
# /initrd 存放启动时挂载initrd.img映像文件的目录，以及载入所需设备模块的目录
# /lib 存放共享库文件 包含许多被/bin /sbin程序使用的库文件
# /lost+found 存放由fsck放置的零散文件
# /media ubuntu系统自动挂载cd-rom 软驱 usb存储器之后存放临时读入的文件
# /mnt 通常作为被挂载文件系统的挂载点
# /opt 作为可选文件和程序的放置目录，主要被第三方开发者用来简易安装和卸载他们的软件包
# /proc 存放所有标志为文件的进程 通过进程号或其他系统动态信息进行标识
# /root 超级用户的主目录
# /sbin 存放更多的可执行文件 二进制 包括系统管理、目录查询等关键命令文件
# /src
# /sys
# /tmp 存放用户和程序的临时文件，所有用户对该目录都有读写权限
# /usr 用于存放与系统用户直接相关的文件和目录
#     /X11R6 x window系统
#     /bin 用户和管理员标准命令
#     /include c/c+各种开发语言环境标准include文件
#     /lib 应用程序及程序包的链接库
#     /local 系统管理员安装的应用程序目录
#     /local/share 系统管理员安装的共享文件
#     /sbin 用户和管理员标准命令
#     /share 存放使用手册等共享文件的目录
#     /share/dict 存放词表的目录
#     /share/man 系统使用手册
#     /share/misc 一般数据
#     /share/sgml sgml数据
#     /share/xml xml数据
# /var 用于存放长度可变的文件，例如日志文件和打印机文件
#     /cache 应用程序缓存目录
#     /crash 系统错误日志
#     /games 游戏数据
#     /lib 各种状态数据
#     /lock 文件锁定记录
#     /log 日志记录
#     /mail 电子邮件
#     /opt /opt目录的变量数据
#     /run 进程的标示数据
#     /spool 存放电子邮件打印任务等的队列目录
#     /tmp 临时文件目录

#文件系统命令
# file filename 用于判定一个文件的类型
# mkdir [-p] directory_name 创建目录
# rmdir [-p] directory_name 删除目录不能有内容 rm -r 删除目录可以有内容
# ln 创建链接文件
# ln [-s] target link_name  -s表示创建软链接 软链接 类似快捷方式 指向源
# 没有-s创建硬链接 指向inode
#文件归档和压缩命令
# 压缩工具 gzip bzip2 zip
# 扩展名 .gz .bz2 .zip
# 解压工具 gunzip bunzip2 unzip
# gzip [-l -d -num] filename -l查看压缩文件内信息不进行压缩 -d 进行解压 -num 1-9压缩率
# gunzip [-f] file.gz
# tar命令
# tar [-t -x -u -c -v -f -j -z] tarfile filelist
# -t 显示归档文件中的内容 -x释放归档文件 -u更新归档文件
# -c 创建一个新的归档文件 -v显示归档释放过程信息 -f指定归档文件名 否则使用默认的
# -j 由tar归档并bzip2压缩 -z由tar归档并gzip压缩

#网络配置管理

 
#shell脚本