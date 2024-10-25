create database db_books;
use db_books;
create table tb_book(
ID char(10) NOT NULL,
bookname char(50) NOT NULL,
author char(50) NOT NULL,
bookconcern char(100) NOT NULL,
PRIMARY KEY(ID)
)ENGINE=MYISAM;