### sqlite

ubuntu 安装三个包 sqlite3,sqlite3-doc,libsqlite3-dev

数据库操作

- 命令行
  sqlite3 数据库文件名(xxx.db)

  - 系统命令
    .help 查看系统命令
    .quit 退出
    .tables
    .schema (tablename)
  - SQL 命令

    - 创建表
      create table stu(id int,name char,score float);
      create table stu2(id int primary key,name char,score float);
      数据类型不支持严格类型检查
      字符串 char string text
      小数 float real
    - 删除表
      drop table stu;
    - 插入数据
      insert into stu values(1,"xiaowang",95.0);
      insert into stu values(2,"wangwu",88.0);
      insert into stu values(2,"lisi",66.0);
      insert into stu(name,score) values("6666",59.0);
    - 查找数据
      select \* from stu order by score;
      select \* from stu limit 5;
      select \* from where id = 1;
    - 修改数据
      update table stu set name = "haha" where id = 1;
      delete from stu where id = 2 or id = null;
    - 增加字段
      alter table stu add column class int default 1;
    - 删除字段
      不直接删除字段
      create table student as select id,name,class from stu;
      drop table stu;
      alter table student rename to stu;
      1. 删除列
         ALTER TABLE 表名 DROP COLUMN 列名;
      2. 增加列
         ALTER TABLE 表名 ADD COLUMN 列名 属性 约束;
      3. 重命名列
         ALTER TABLE 表名 RENAME COLUMN 旧列名 TO 新列名;
      4. 重命名表
         ALTER TABLE 旧表名 RENAME TO 新表名;
      5. 删除主键
         ALTER TABLE 表名 DROP PRIMARY KEY;
      6. 添加主键===CONSTRAINT 约束名可以不要，()括号必须有，不然会报错
         ALTER TABLE 表名 ADD CONSTRAINT 约束名 PRIMARY KEY (指定列);
      7. 添加索引
         ALTER TABLE 表名 ADD index 索引名 (列名);
      8. 修改列
         ALTER TABLE 表名 CHANGE 旧列名 TO 新列名 属性
      9. 修改列的属性  
         ALTER TABLE 表名 MODIFY COLUMN 列名 新属性;
      10. 修改列的默认值
          ALTER TABLE 表名 ALTER COLUMN 列名 SET DEFAULT 默认值;
      11. 删除约束
          ALTER TABLE 表名 DROP CONSTRAINT 约束名;

- C 代码方式
  https://www.sqlite.org/capi3ref.html

```c
#define SQLITE_OK           0   /* Successful result */
/* beginning-of-error-codes */
#define SQLITE_ERROR        1   /* Generic error */
#define SQLITE_INTERNAL     2   /* Internal logic error in SQLite */
#define SQLITE_PERM         3   /* Access permission denied */
#define SQLITE_ABORT        4   /* Callback routine requested an abort */
#define SQLITE_BUSY         5   /* The database file is locked */
#define SQLITE_LOCKED       6   /* A table in the database is locked */
#define SQLITE_NOMEM        7   /* A malloc() failed */
#define SQLITE_READONLY     8   /* Attempt to write a readonly database */
#define SQLITE_INTERRUPT    9   /* Operation terminated by sqlite3_interrupt()*/
#define SQLITE_IOERR       10   /* Some kind of disk I/O error occurred */
#define SQLITE_CORRUPT     11   /* The database disk image is malformed */
#define SQLITE_NOTFOUND    12   /* Unknown opcode in sqlite3_file_control() */
#define SQLITE_FULL        13   /* Insertion failed because database is full */
#define SQLITE_CANTOPEN    14   /* Unable to open the database file */
#define SQLITE_PROTOCOL    15   /* Database lock protocol error */
#define SQLITE_EMPTY       16   /* Internal use only */
#define SQLITE_SCHEMA      17   /* The database schema changed */
#define SQLITE_TOOBIG      18   /* String or BLOB exceeds size limit */
#define SQLITE_CONSTRAINT  19   /* Abort due to constraint violation */
#define SQLITE_MISMATCH    20   /* Data type mismatch */
#define SQLITE_MISUSE      21   /* Library used incorrectly */
#define SQLITE_NOLFS       22   /* Uses OS features not supported on host */
#define SQLITE_AUTH        23   /* Authorization denied */
#define SQLITE_FORMAT      24   /* Not used */
#define SQLITE_RANGE       25   /* 2nd parameter to sqlite3_bind out of range */
#define SQLITE_NOTADB      26   /* File opened that is not a database file */
#define SQLITE_NOTICE      27   /* Notifications from sqlite3_log() */
#define SQLITE_WARNING     28   /* Warnings from sqlite3_log() */
#define SQLITE_ROW         100  /* sqlite3_step() has another row ready */
#define SQLITE_DONE        101  /* sqlite3_step() has finished executing */
/* end-of-error-codes */

/// 打开数据库
/// 成功返回SQLITE_OK并赋值*db 失败返回错误码
int sqlite3_open(
  const char *filename,   /* Database filename (UTF-8) */
  sqlite3 **ppDb          /* OUT: SQLite db handle */
);
/// 关闭数据库
/// 成功返回SQLITE_OK
int sqlite3_close(sqlite3*);

/// 关闭数据库
const char *sqlite3_errmsg(sqlite3*);

/// 操作数据库
// 当使用查询时 callback和void *才有意义
// int (*callback)(void*,int,char**,char**)
// 第二个参数是结果的行数
// 第三个参数是一个结果数组sqlite3_column_text()
// 第四个参数是一个结果数组sqlite3_column_name().
int sqlite3_exec(
  sqlite3*,                                  /* An open database */
  const char *sql,                           /* SQL to be evaluated */
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
);
// sqlite3_get_table主要是用于非回调的方式进行select查询
// 参数1：打开数据库得到的指针；
// 参数2：一条sql语句，跟sqlite3_exec中一样；
// 参数3：查询的数据结果，他是一个指针数组的指针，内存分布为：字段名称，后面是紧接着是每个字段的值；
// 参数4：查询到的数据条数，（行数）；
// 参数5：查询到的字段数，（列数）；
// 参数6：错误信息；
int sqlite3_get_table(
  sqlite3 *db,          /* An open database */
  const char *zSql,     /* SQL to be evaluated */
  char ***pazResult,    /* Results of the query */
  int *pnRow,           /* Number of result rows written here */
  int *pnColumn,        /* Number of result columns written here */
  char **pzErrmsg       /* Error msg written here */
);
void sqlite3_free_table(char **result);

// sqlite3_prepare_v2 和 sqlite3_step 配合 sqlite3_column 系列函数来迭代查询结果
sqlite3 *db;
sqlite3_stmt *stmt;
int rc;
const char *sql = "SELECT * FROM stu;";
rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
if (rc == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // 假设查询结果有两列，分别是 INTEGER 和 TEXT 类型
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        printf("ID: %d, Name: %s\n", id, name);
    }
} else {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
}
sqlite3_finalize(stmt);
sqlite3_close(db);
```

```
使用C库

# 将自定义库 mylib.so 复制到系统库目录
sudo cp mylib.so /usr/local/lib

# 创建符号链接
sudo ln -s /usr/local/lib/mylib.so /usr/lib/mylib.so

# 将自定义头文件 mylib.h 复制到系统头文件目录
sudo cp mylib.h /usr/local/include
```

### 网络词典项目
