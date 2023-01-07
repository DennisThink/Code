SQLite代码分析第一篇----目录结构说明

1. gdbm目录
保持gdbm的源代码，gdbm是一个key-value的数据管理工具。

2. sqlite目录

2.1 include目录
sqlite相关的头文件

2.2 src
sqlite相关的源文件。

1. build.c
被语法解析工具调用，用来处理CREATE TABLE、DROP TABLE、CREATE INDEx、DROP INDEX等SQL语句。

2. dbbe.c
作为数据库的后端，负责保存数据到硬盘和从硬盘读取数据。是一个key-value形式的数据库，在设计的时候支持GDBM、NDBM、SDBM、以及BerkeleyDB。

3. delete.c
被语法解析器调用来处理DELETE语句的解析。

4. expr.c

5. insert.c
被语法解析器调用来处理INSERT语句。

6. main.c

7. parse.c
由lemon工具生成的代码，在阅读代码的时候可以先不看。

8. select.c
被语法解析器调用来处理SELECT语句。

9. shell.c
main 函数所在文件，程序入口。

10. tokenize.c
用来解析SQL中的TOKEN。

11. update.c
被语法解析器调用来处理UPDATE语句。

12. util.c

13. vdbe.c
SQL语句执行的虚拟机。

14. where.c
用于处理WHERE语句。

# 3. 程序流程分析
