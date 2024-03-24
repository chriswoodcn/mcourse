#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

void do_exec_create(sqlite3 *db) {
  char *err_msg;
  int res = sqlite3_exec(
      db, "create table stu2(id int primary key,name char,score float);", NULL,
      NULL, &err_msg);
  if (res != SQLITE_OK) {
    printf("sqlite3_open failed: %s\n", err_msg);
    return;
  }
  printf("do_exec_create success\n");
}
void do_exec_insert(sqlite3 *db) {
  char *err_msg;
  int res = sqlite3_exec(db, "insert into stu2 values(1,\"xiaowang\",95.0);",
                         NULL, NULL, &err_msg);
  if (res != SQLITE_OK) {
    printf("do_exec_insert failed: %s\n", err_msg);
  }
  res = sqlite3_exec(db, "insert into stu2 values(2,\"zhangsan\",86.0);", NULL,
                     NULL, &err_msg);
  if (res != SQLITE_OK) {
    printf("do_exec_insert failed: %s\n", err_msg);
  }
  printf("do_exec_create success\n");
}
/// @brief sqlite3查询回调函数 每找到一条记录自动执行一次此回调
/// @param para 传递给回调函数的参数
/// @param f_num 记录中能够包含的字段数目
/// @param f_value 包含每个字段值的指针数组
/// @param f_name 包含每个字段名的指针数组
/// @return
int callback(void *para, int f_num, char **f_value, char **f_name) {
  printf("select para %s\n", (char *)para); // expect hello
  printf("column size %d\n", f_num);
  printf("column name");
  for (int i = 0; i < f_num; i++) {
    printf(" %s ", *(f_name + i));
  }
  printf("\n");
  printf("column value");
  for (int i = 0; i < f_num; i++) {
    printf(" %s ", *(f_value + i));
  }
  printf("\n");
  return 0;
}
/**
 * @brief 查询sqlite3
 * @param sqlite3实例
 */
void do_exec_select(sqlite3 *db) {
  char *err_msg;
  int res =
      sqlite3_exec(db, "select * from stu2;", callback, "hello", &err_msg);
  if (res != SQLITE_OK) {
    printf("do_exec_select failed: %s\n", err_msg);
  }
}
void get_table_select(sqlite3 *db) {
  char **dbresult;
  int nRow, nColum;
  char *err_msg;
  int rc = sqlite3_get_table(db, "SELECT * FROM stu2;", &dbresult, &nRow,
                             &nColum, &err_msg);
  if (rc == SQLITE_OK) {
    int index = nColum;
    for (int i = 0; i < nRow; i++) {
      for (int j = 0; j < nColum; j++) {
        printf("字段名-值: %s - %s;", dbresult[j], dbresult[index]);
        ++index;
      }
      puts("");
    }
  }
  sqlite3_free_table(dbresult);
}
void get_table_select2(sqlite3 *db) {
  sqlite3_stmt *stmt;
  int rc;
  const char *sql = "SELECT * FROM stu2;";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  printf("sqlite3_prepare_v2 rc: %d\n", rc);
  if (rc == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      // 查询结果
      int id = sqlite3_column_int(stmt, 0);
      const unsigned char *name = sqlite3_column_text(stmt, 1);
      double score = sqlite3_column_double(stmt, 2);
      printf("ID: %d, Name: %s, SCORE: %.2lf \n", id, name, score);
    }
  } else {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
  }
  sqlite3_finalize(stmt);
}
int main(int argc, char *argv[]) {
  printf("use sqlite3 version: %s\n", SQLITE_VERSION);
  int res;
  sqlite3 *db;
  res = sqlite3_open("stu.db", &db);
  if (res != SQLITE_OK) {
    printf("sqlite3_open failed: %s\n", sqlite3_errmsg(db));
    exit(-1);
  }
  do_exec_create(db);
  do_exec_insert(db);
  do_exec_select(db);
  get_table_select(db);
  get_table_select2(db);

  res = sqlite3_close(db);
  if (res != SQLITE_OK) {
    printf("sqlite3_close failed: %s\n", sqlite3_errmsg(db));
    exit(-1);
  }
  return 0;
}