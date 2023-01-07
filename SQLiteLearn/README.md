# SQLiteLearn

This is a project for learning sqlite,the code is from sqlite 1.0.1 and  gdbm 1.8.3. It use cmake build tool to generate the solution in Windows .The basic step of building the project is as follow:


## 1. download the code 
you can download the code by git or http.and Copy the Code to a empty folder.

## 2. Install cmake above version 3.0.
Install cmake tools on you computer and make sure add the cmake.exe to the "Path" system variable;

## 3. create the solution.

create a new folder at to root folder of the Code. Enter the folder and run the command at the folder.

## 4. Run SQL Code.

1. create table
sqlite.exe testdb "create table tuser(id INT);"

2. insert some data in the table
sqlite.exe testdb "insert into table tuser(id) values(1);"

3. show the data of the table.
sqlite.exe testdb "select * from tuser;"