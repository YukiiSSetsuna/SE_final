#ifndef INC_3_2_GLOBALFUNCTION_H
#define INC_3_2_GLOBALFUNCTION_H

#include "KnowledgeManager.h"
#include "BookManager.h"
#include "Book.h"

#include<vector>
#include <iostream>
#include <string>
#include <fstream>
#include <io.h>
using namespace std;


void Next(const char* T, int* next);
int* KMP(const string Str, const string Str_to_search, const int max_num);
int content_searching(const Book& b, const string str_to_find);


int select_mainmenu(vector<Book> library, vector<Knowledge> base);
void show_mainmenu();
void select_global_keyword(vector<Book> library, vector<Knowledge> base, vector<Book>& temp_lib, vector<Knowledge>& temp_base);

void get_files_list(string path, vector<string>& files);

string convertTimeStamp2TimeStr(time_t timeStamp);

#endif //INC_3_2_GLOBALFUNCTION_H