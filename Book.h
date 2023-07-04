#ifndef INC_3_2_BOOK_H
#define INC_3_2_BOOK_H
#include <stdio.h>
#include <string.h>
#include<iostream>
#include <fstream>
#include<string>
#include <vector>

using namespace std;
class Book
{
public:
    Book();
    ~Book();
    int book_number;
    string book_name;
    string book_writer;
    string book_press;
    string book_address;
    static void show_book_info(Book b);
    static string get_book_content(Book b);
    static void show_book_content(Book b);
    static int deleteBook(vector<Book>& b, Book c);
};

#endif //INC_3_2_BOOK_H