#include <algorithm>
#include <iostream>
#include <sstream>
#include "BookManager.h"
#include "KnowledgeManager.h"
#include "Global_Function.h"
#include "Book.h"                                                                                                           
using namespace std;


string convertTimeStamp2TimeStr(time_t timeStamp) {
    //struct tm* timeinfo = nullptr;
    //char buffer[80];
    //timeinfo = localtime(&timeStamp);
    struct tm t;
    time_t now;
    time(&now);
    localtime_s(&t, &timeStamp);

    stringstream ss;
    string result;
    ss << t.tm_year + 1900 << "-" << t.tm_mon + 1 << "-"
        << t.tm_mday << " " << t.tm_hour << ":"
        << t.tm_min << ":" << t.tm_sec;
    result = ss.str();

    printf("%d-%d-%d %d:%d:%d\n", t.tm_year + 1900, t.tm_mon + 1,
        t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    //strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    //printf("%s\n", buffer);
    return result;
}

void Next(const char* T, int* next) {
    int i = 1;
    next[1] = 0;
    int j = 0;
    while (i < strlen(T)) {
        if (j == 0 || T[i - 1] == T[j - 1]) {
            i++;
            j++;
            if (T[i - 1] != T[j - 1]) {
                next[i] = j;
            }
            else {
                next[i] = next[j];
            }
        }
        else {
            j = next[j];
        }
    }
}
int* KMP(const string Str, const string Str_to_search, const int max_num)
{
    int* ans = new int[max_num];    //最多搜索多少个结果
    for (int j = 0; j < max_num; j++)//初始化为-1，所以可以根据*(ans)是否等于-1来判断有无搜索结果
    {
        *(ans + j) = -1;
    }
    const char* S = Str.data();
    const char* T = Str_to_search.data();
    int i = 1;
    int j = 1;
    int cnt = 0;
    int next[21];   //最多支持搜索十个汉字
    Next(T, next);  //根据模式串T,初始化next数组   
    while (i <= strlen(S) && cnt < max_num)
    {
        j = 1;
        while (i <= strlen(S) && j <= strlen(T)) {
            //j==0:代表模式串的第一个字符就和当前测试的字符不相等；S[i-1]==T[j-1],如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
            if (j == 0 || S[i - 1] == T[j - 1]) {
                i++;
                j++;
            }
            else {
                j = next[j];//如果测试的两个字符不相等，i不动，j变为当前测试字符串的next值
            }
        }
        if (j > strlen(T)) {//如果条件为真，说明匹配成功
            ans[cnt] = i - (int)strlen(T);//储存的是所搜索的字符串在文本中的下标
            //cout << "key: " << i - (int)strlen(T) << "        ";
            //cout << "ans[" << cnt << "]:" << i - (int)strlen(T) << endl;
            cnt++;
        }
    }
    //cout << "KMPsizeof(ans):" << sizeof(ans) << endl;
    return ans;
}
int content_searching(const Book& b, const string str_to_find) {
    string readfile;
    readfile = Book::get_book_content(b);
    if (readfile.length() == 0)
    {
        cout <<b.book_name<< "文件为空！请查看" <<b.book_address<< "是否存在" << endl;
    }
    int max_ans_num = 10;   //最多支持的答案数量
    int* ans;
    ans = KMP(readfile, str_to_find, max_ans_num);
    int len = 600;    //输出接下来多少个字符，中文的话要除2，len=600即接下来300字
    bool ans_exist = false;
    for (int j = 0; j < max_ans_num; j++)
    {
        int i = *(ans + j);
        //cout << "i, j" << i << "\t" << j;
        if (i != -1)
        {
            ans_exist = true;
            string s2 = " ";
            //cout << "i: " << i << endl;
            s2 = readfile.substr(i-1, len);//输出接下来的len个字符，-1是由于中文占两个字符
            s2 = s2 + "...";
            cout << "文段" << j + 1 << "为：" << endl << s2 << endl;
            cout << endl;
        }
        if (!ans_exist)
        {
            delete ans;
            ans = NULL;
            return -1;
        }
    }
    delete ans;
    ans = NULL;
    return 0;
}


int select_mainmenu(vector<Book> library, vector<Knowledge> base)
{
    while (true)
    {
        //展示主菜单
        show_mainmenu();
        char choice;
        cin >> choice;
        switch (choice)
        {
        case'0'://退出
        {
            cout << "欢迎下次使用" << endl;
            return 0;
        }
        case '1'://进入书籍资料库
        {
            BookManager::select_library_mainmenu(library);
            break;
        }
        case '2'://进入基本知识库
        {
            KnowledgeManager::select_base_mainmenu(base);
            break;
        }
        case '3'://进行全局搜索
        {
            vector<Book>temp_lib;
            vector<Knowledge>temp_base;
            select_global_keyword(library, base, temp_lib, temp_base);
            if (temp_lib.empty() && temp_base.empty())  //没有符合条件的书
            {
                cout << "全局搜索没有找到相关内容" << endl;
            }
            else        
            {
                cout << "可搜到的知识有" << temp_base.size() << "条，分别是：" << endl;
                for (int i = 0; i < temp_base.size(); ++i) {
                    Knowledge::show_knowledge_info(temp_base[i]);
                }
                cout <<endl<< "可搜到的书籍资料有" << temp_lib.size() << "本，分别是：" << endl;
                for (int i = 0; i < temp_lib.size(); ++i) {
                    Book::show_book_info(temp_lib[i]);
                }
                cout << "如需进一步查看，请进入对应知识库进行查阅。" << endl;
            }
            break;
        }
        default:
        {
            cout << "指令错误，请重新输入" << endl;
            break;
        }
        }
        system("pause");
        system("cls");
    }
}
void show_mainmenu()
{
    cout << "************************************" << endl;
    cout << "*****   中医知识库系统         *****" << endl;
    cout << "*****   进入书籍资料库请按1    *****" << endl;
    cout << "*****   进入基本知识库请按2    *****" << endl;
    cout << "*****   要进行全局搜索请按3    *****" << endl;
    cout << "*****   退出知识库系统请按0    *****" << endl;
    cout << "************************************" << endl;
}
void select_global_keyword(vector<Book> library, vector<Knowledge> base, vector<Book>& temp_lib, vector<Knowledge>& temp_base)
{
    //library和base存放的是知识库中的书籍和知识，temp_lib和temp_base存的是符合搜索条件的书籍和知识
    cout << "请输入您要查找的关键词" << endl;
    string keyword;
    cin >> keyword;
    for (auto& i : base)
    {
        //判断知识名中是否有关键词
        int* name_ans;
        name_ans = KMP(i.name, keyword, 5);
        int flag_name = *(name_ans);
        //判断内容中是否有关键词
        string content = Knowledge::get_knowledge_content(i);
        int* content_ans;
        content_ans = KMP(content, keyword, 5);
        int flag_content = *(content_ans);
        if (flag_content != -1 || flag_name != -1)
        {
            temp_base.push_back(i);//有的话就放入temp_base
        }
        delete name_ans;
        name_ans = NULL;
        delete content_ans;
        content_ans = NULL;
    }

    for (auto& i : library)
    {
        //判断书名是否含有关键词
        int* name_ans;
        name_ans = KMP(i.book_name, keyword, 2);
        int flag_name = *(name_ans);
        //判断作者名是否含有关键词
        int* writer_ans;
        writer_ans = KMP(i.book_writer, keyword, 2);
        int flag_writer = *(writer_ans);
        //判断内容中是否含有关键词
        string content = Book::get_book_content(i);
        int* content_ans;
        content_ans = KMP(content, keyword, 10);
        int flag_content = *(content_ans);

        if (flag_content != -1 || flag_writer != -1 || flag_name != -1 || i.book_name == keyword || i.book_writer == keyword || i.book_press == keyword)
        {
            temp_lib.push_back(i);//有的话就放入temp_lib
        }
        delete name_ans;
        name_ans = NULL;
        delete writer_ans;
        writer_ans = NULL;
        delete content_ans;
        content_ans = NULL;
    }
}

void get_files_list(string path, vector<string>& files) //用于获取文件夹下所有文件的文件名，类似python中的listdir
{
    intptr_t hFile = 0;
    _finddata_t fileinfo;
    if ((hFile = _findfirst(path.append("/*").c_str(), &fileinfo)) != -1) 
    {
        while (_findnext(hFile, &fileinfo) == 0) 
        {
            if (strcmp(fileinfo.name, ".."))
                files.push_back(fileinfo.name);
        }
        _findclose(hFile);
    }
}