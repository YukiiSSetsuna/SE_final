#ifndef INC_3_2_BOOKMANAGER_H
#define INC_3_2_BOOKMANAGER_H

#include "BookManager.h"
#include "Global_Function.h"
#include "KnowledgeManager.h"
#include "Book.h"
#include<vector>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
constexpr auto LIBRARY_FILENAME = "data/book/library.txt";
using namespace std;


class BookManager
{
	public:
		BookManager();
		BookManager(vector<Book> lib);
		~BookManager();
		vector<Book> library;


		static void select_library_mainmenu(vector<Book>& b);
		
		static bool admin_Login();
		static string read_admininfo();
		static void register_admin();
		static void write_log(Book& new_book,string c);

		static void showMenu_bookmanager();
		static void showMenu_searchbook();
		static void showMenu_modifybook();
		static void showMenu_viewbook();

		static Book search_book(vector<Book>& b);
		static void search_book_number(vector<Book>& b, vector<Book>& c);
		static void search_book_name(vector<Book>& b, vector<Book>& c);
		static void search_book_writer(vector<Book>& b, vector<Book>& c);
		static void search_book_press(vector<Book>& b, vector<Book>& c);
		static void search_book_keyword(vector<Book>& b, vector<Book>& c);

		static void add_book(vector<Book>& b);
		static void add_book_number(vector<Book>& b, Book& c);
		static void add_book_name(vector<Book>& b, Book& c);
		static void add_book_writer(vector<Book>& b, Book& c);
		static void add_book_press(vector<Book>& b, Book& c);
		static void add_book_address(vector<Book>& b, Book& c);

		static void modify_book(vector<Book>& b, Book& c);
		static void modify_book_number(vector<Book>& b, Book& c);
		static void modify_book_name(vector<Book>& b, Book& c);
		static void modify_book_writer(vector<Book>& b, Book& c);
		static void modify_book_press(vector<Book>& b, Book& c);

		static void view_book(vector<Book>& b, Book& c);

		static void show_allbook(vector<Book>& b);
		static void save_library(vector<Book>& b);
		static void fetch_library(vector<Book>& b);
		static int book_isValid(int num, vector<Book>& b);
		static bool book_number_cmp(const Book& a, const Book& b);
};






#endif //INC_3_2_BOOKMANAGER_H