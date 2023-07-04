#include "BookManager.h"
#include "Global_Function.h"
#include "KnowledgeManager.h"
#include "Book.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <time.h>


using namespace std;

BookManager::BookManager() 
{

}
BookManager::BookManager(vector<Book> lib)
{
    library = lib;
}
BookManager::~BookManager()
{

}

void BookManager::select_library_mainmenu(vector<Book>& b)
{
    while (true)
    {
        //展示主菜单
        BookManager::showMenu_bookmanager();
        char choice;
        cin >> choice;
        switch (choice)
        {
            case'0'://退出
            {
                cout << "欢迎下次使用" << endl;
                return;
            }
            case '1'://添加书籍
            {
                bool suc = BookManager::admin_Login();
                if (suc)
                {
                    BookManager::add_book(b);
                    break;
                }
                else
                    break;
                
            }
            case '2'://修改书籍
            {
                bool suc = BookManager::admin_Login();
                if (suc)
                {
                    cout << "请先检索你所需要修改的书籍" << endl;
                    Book temp = BookManager::search_book(b);
                    if (temp.book_number != -1)
                    {
                        BookManager::modify_book(b, temp);
                    }
                    break;
                }
                else
                    break;
            }
            case '3'://展示所有图书
            {
                if (b.empty())
                {
                    cout << "当前无图书" << endl;
                    break;
                }
                BookManager::show_allbook(b);
                break;
            }
            case '4'://搜索书籍
            {   
                Book temp = BookManager::search_book(b);
                if (temp.book_number != -1)
                {
                    BookManager::view_book(b, temp);
                }
                break;
            }
            case  '5'://管理员修改
            {
                bool legal = BookManager::admin_Login();
                if (!legal) { break; }
                else
                {
                    //执行修改
                    BookManager::register_admin();
                }
                break;
            }
            default:
            {
                cout << "指令错误，请重新输入" << endl;
            }
        }
        system("pause");
        system("cls");
    }
}

bool BookManager::admin_Login()
{
    while (true)
    {
        string name, password = "";
        cout << "请输入管理员账户名：" << endl;
        cin >> name;
        cout << "请输入管理员账户密码：" << endl;
        cin >> password;
        string login = name + password;
        string standard = BookManager::read_admininfo();
        //cout << "test:" << standard << endl;
        //cout << "test:" << login << endl;
        if (login == standard)
        {
            cout << "欢迎登陆！" << endl;
            return true;
        }
        else
        {
            cout << "登录失败：用户名或密码错误，重新输入？" << endl;
            cout << "输入1重新输入，输入0退出" << endl;
            char choice;
            cin >> choice;
            switch (choice)
            {
                case '1':
                {
                    continue;
                }
                case '0':
                {
                    return false;
                }
            }
        }
    }
    return true;
}

string BookManager::read_admininfo()
{
    string info_path = "data/admin/admin.txt";
    ifstream ifs;
    ifs.open(info_path);//读文件
    if (!ifs.is_open())//判断是否存在
    {
        cout << "文件不存在" << endl;
        ifs.close();
        string str_empty = "";
        return str_empty;
    }
    string content;
    string temp;
    while (getline(ifs, temp))
    {
        content += temp;
    }
    ifs.close(); // 及时关闭fstream
    return content;
}

void BookManager::register_admin()
{
    string new_name;
    string new_password;
    cout << "请输入新管理员账户名称" << endl;
    cin >> new_name;
    cout << "请输入新管理员账户密码" << endl;
    cin >> new_password;
    string info_path = "data/admin/admin.txt";
    ofstream ofs;
    ofs.open(info_path);//读文件
    if (!ofs.is_open())//判断是否存在
    {
        cout << "文件不存在" << endl;
        ofs.close();
    }
    ofs << new_name + "\n" + new_password;
    ofs.close();
}

void BookManager::write_log(Book& new_book,string c)
{
    string info_path = "data/admin/log_book.txt";
    ofstream ofs;
    ofs.open(info_path, ios::app);//读文件追加
    if (!ofs.is_open())//判断是否存在
    {
        cout << "文件不存在" << endl;
        ofs.close();
    }
    time_t now = time(NULL);
    string time = convertTimeStamp2TimeStr(now);
    ofs << time + " " + c + "书名：" + new_book.book_name << endl;
}

void BookManager::showMenu_bookmanager()
{
    cout << "************************************" << endl;
    cout << "*****     中医书籍资料库系统   *****" << endl;
    cout << "*****     添加书籍信息请按1    *****" << endl;
    cout << "*****     修改书籍信息请按2    *****" << endl;
    cout << "*****     显示书籍信息请按3    *****" << endl;
    cout << "*****     搜索书籍信息请按4    *****" << endl;
    cout << "*****     修改管理员信息请按5    *****" << endl;
    cout << "*****     退出图书系统请按0    *****" << endl;
    cout << "************************************" << endl;
}
void BookManager::showMenu_searchbook()
{
    cout << "**************************************" << endl;
    cout << "*****   请选择您检索书籍的方式   *****" << endl;
    cout << "*****   通过书名查找请按1        *****" << endl;
    cout << "*****   通过书籍编号查找请按2    *****" << endl;
    cout << "*****   通过作者查找请按3        *****" << endl;
    cout << "*****   通过出版社查找请按4      *****" << endl;
    cout << "*****   通过关键词查找请按5      *****" << endl;
    cout << "*****   退出查找请按0            *****" << endl;
    cout << "**************************************" << endl;
}
void BookManager::showMenu_modifybook()
{
    cout << "**************************************" << endl;
    cout << "*****     您想要修改该书哪种信息 *****" << endl;
    cout << "*****     修改书籍编号请按1      *****" << endl;
    cout << "*****     修改书籍名请按2        *****" << endl;
    cout << "*****     修改作者请按3          *****" << endl;
    cout << "*****     修改出版社请按4        *****" << endl;
    cout << "*****     删除该书请按5          *****" << endl;
    cout << "*****     退出修改请按0          *****" << endl;
    cout << "**************************************" << endl;
}
void BookManager::showMenu_viewbook()
{
    cout << "**************************************" << endl;
    cout << "*****     您想对该书籍作哪种处理 *****" << endl;
    cout << "*****     展示书籍内容请按1      *****" << endl;
    cout << "*****     搜索文本内容请按2      *****" << endl;
    cout << "*****     修改书籍信息请按3      *****" << endl;
    cout << "*****     退出查看系统请按0      *****" << endl;
    cout << "**************************************" << endl;
}

Book BookManager::search_book(vector<Book>& b)
{
    Book tmp;
    vector<Book>c;//为防止书籍其他信息重复，将信息重复的查找结果存在c中
    tmp.book_number = 0;
    BookManager::showMenu_searchbook();
    char choose2;
    cin >> choose2;
    switch (choose2)
    {
        case '1'://按书名查找
        {
            BookManager::search_book_name(b, c);
            break;
        }
        case '2'://编号
        {
            BookManager::search_book_number(b, c);
            break;
        }
        case '3'://作者
        {
            BookManager::search_book_writer(b, c);
            break;
        }
        case '4'://出版社
        {
            BookManager::search_book_press(b, c);
            break;
        }
        case '5'://关键词
        {
            BookManager::search_book_keyword(b, c);
            break;
        }
        case '0'://退出
        {
            cout << "欢迎下次使用" << endl;
            tmp.book_number = -1;//将返回书籍的编号置为-1，代表没有找到书籍
            break;
        }
        default:
        {
            cout << "指令错误，请重新输入" << endl;
        }
    }
    if (tmp.book_number != -1)
    {
        if (c.empty())  //没有符合条件的书
        {
            cout << "查无此书" << endl;
            tmp.book_number = -1;
        }
        else if (c.size() == 1) //符合条件的只有一本书
        {
            //view_book(b, c[0]);
            return c[0];
        }
        else        //符合条件的不止一本书
        {
            cout << "请确认您要查找的书籍" << endl;
            int i;
            for (i = 0; i < c.size(); ++i) {
                cout << i + 1 << "、\t";
                Book::show_book_info(c[i]);
            }
            cout << "请选择您要查找的书籍序号，注意不是书籍编号" << endl;
            int num;
            cin >> num;
            if (num > i+1 || num < 0)
            {
                cout << "输入的序号未在列表内，默认选择第一个" << endl;
                return c[0];
            }
            //view_book(b, c[i]);
            return c[num-1];
        }
    }
    return tmp;
}
void BookManager::search_book_number(vector<Book>& b, vector<Book>& c) {
    cout << "请输入您要查找的书籍编号" << endl;
    int num;
    cin >> num;
    if (BookManager::book_isValid(num, b) == 2)
    {
        cout << "编号需为正整数，请重新输入" << endl;
        cin.clear();
        cin.ignore();//这两个函数很关键！没有的话会一直循坏
    }
    else if(BookManager::book_isValid(num, b) == 1)
    {
        for (auto& i : b) 
        {
            if (i.book_number == num)
            {
                c.push_back(i);
            }
        }
    }
    
}
void BookManager::search_book_name(vector<Book>& b, vector<Book>& c) {
    string name;
    cout << "请输入您要查找的书籍名称" << endl;
    cin >> name;
    for (auto& i : b) {
        if (i.book_name == name)
        {
            c.push_back(i);
        }
    }
}
void BookManager::search_book_writer(vector<Book>& b, vector<Book>& c) {
    string writer;
    cout << "请输入您要查找的书籍作者" << endl;
    cin >> writer;
    for (auto& i : b) {
        if (i.book_writer == writer)
        {
            c.push_back(i);
        }
    }
}
void BookManager::search_book_press(vector<Book>& b, vector<Book>& c) {
    string press;
    cout << "请输入您要查找的书籍出版社" << endl;
    cin >> press;
    for (auto& i : b) {
        if (i.book_press == press)
        {
            c.push_back(i);
        }
    }
}
void BookManager::search_book_keyword(vector<Book>& b, vector<Book>& c)
{
    string keyword;
    cout << "请输入您要查找的关键词，不超过十个汉字：" << endl;
    cin >> keyword;
    for (auto& i : b) 
    {   //查找书名
        int* name_ans;
        name_ans = KMP(i.book_name, keyword, 5);
        int flag_name = *(name_ans);
        //查找作者名
        int* writer_ans;
        writer_ans = KMP(i.book_writer, keyword, 5);
        int flag_writer = *(writer_ans);
        //查找书籍内容
        string content = Book::get_book_content(i);
        int* content_ans;
        content_ans = KMP(content, keyword, 10);
        int flag_content = *(content_ans);
        if (flag_content != -1 || flag_writer != -1 || flag_name != -1 || i.book_name == keyword || i.book_writer == keyword || i.book_press == keyword)
        {
            c.push_back(i);
        }

        delete name_ans;
        name_ans = NULL;
        delete writer_ans;
        writer_ans = NULL;
        delete content_ans;
        content_ans = NULL;
    }
}

void BookManager::add_book(vector<Book>& b) {
    Book newbook;
    BookManager::add_book_number(b, newbook);
    BookManager::add_book_name(b, newbook);
    BookManager::add_book_writer(b, newbook);
    BookManager::add_book_press(b, newbook);
    BookManager::add_book_address(b, newbook);
    b.push_back(newbook);
    cout << "添加成功" << endl;
    BookManager::save_library(b);
    string record = "添加书籍：";
    BookManager::write_log(newbook, record);

}
void BookManager::add_book_number(vector<Book>& b, Book& c) {
    int num;
    cout << "请输入编号，编号需为正整数且不可重复" << endl;
    while (true)
    {
        cin >> num;
        if (BookManager::book_isValid(num, b) != 0)
        {
            cout << "编号需为正整数且不可重复，请重新输入" << endl;
            cin.clear();
            cin.ignore();//这两个函数很关键！没有的话会一直循坏
        }   
        else
        {
            //cout << "number break" << endl;
            break;
        }
        
    }
    c.book_number = num;
}
void BookManager::add_book_name(vector<Book>& b, Book& c) {
    string name;
    cout << "请输入书名" << endl;
    cin >> name;
    c.book_name = name;
}
void BookManager::add_book_writer(vector<Book>& b, Book& c) {
    string writer;
    cout << "请输入作者" << endl;
    cin >> writer;
    c.book_writer = writer;
}
void BookManager::add_book_press(vector<Book>& b, Book& c) {
    string press;
    cout << "请输入出版社" << endl;
    cin >> press;
    c.book_press = press;
}
void BookManager::add_book_address(vector<Book>& b, Book& c)
{
    string address;
    cout << "请将txt格式的书籍放入该软件根目录的'data/book/'文件夹当中，并确保编码格式为ANSI，否则读取中文会出现乱码！" << endl;
    cout << "请输入书籍文件名,格式为 ‘书名.txt’ " << endl;
    while (true)
    {
        cin >> address;
        ifstream ifs;
        string file_path = "data/book/" +  address;
        ifs.open(file_path, ios::in);//读文件
        if (!ifs.is_open())//判断是否存在
        {
            cout << "文件不存在" << endl;
            ifs.close();
        }
        else break;
    }
    c.book_address = address;
}

void BookManager::modify_book(vector<Book>& b, Book& c)
{
    while (true)
    {
        Book::show_book_info(c);
        BookManager::showMenu_modifybook();
        char choice;
        cin >> choice;
        switch (choice)
        {
            case '0'://退出
            {
                cout << "退出修改系统" << endl;
                return;
            }
            case '1':
            {
                BookManager::modify_book_number(b, c);
                break;
            }
            case '2':
            {
                BookManager::modify_book_name(b, c);
                break;
            }
            case '3':
            {
                BookManager::modify_book_writer(b, c);
                break;
            }
            case '4':
            {
                BookManager::modify_book_press(b, c);
                break;
            }
            case '5'://删除
            {
                int flag = Book::deleteBook(b, c);
                if (flag == 0)
                {
                BookManager::save_library(b);
                cout << "已完成删除，退出修改系统" << endl;
                string record = "删除书籍：";
                BookManager::write_log(c, record);
                return;
                }
                else
                {
                    break;
                }
            }
            default:
            {
                cout << "指令错误，修改失败" << endl;
                break;
            }
        }
        system("pause");
        system("cls");
    }
}
void BookManager::modify_book_number(vector<Book>& b, Book& c)
{
    int number;
    int pre_number = c.book_number;
    cout << "现编号为：" << c.book_number << endl;
    cout << "请输入修改后编号" << endl;
    cin >> number;
    if (BookManager::book_isValid(number, b) != 0)//判断编号是否有效
    {
        cout << "编号重复，修改失败" << endl;
    }
    else {
        int i = 0;
        for (; i < b.size(); ++i) 
        {
            if (b[i].book_number == c.book_number)break;
        }
        c.book_number = number;
        b[i].book_number = number;
        cout << "修改成功" << endl;
        BookManager::save_library(b);
        string record = "修改书籍编号 原编号:";
        record += to_string(pre_number) + " 现编号:" + to_string(number) + " ";
        BookManager::write_log(c, record);
    }
}
void BookManager::modify_book_name(vector<Book>& b, Book& c)
{
    string name;
    string pre_name = c.book_name;
    cout << "现书名为：" << c.book_name << endl;
    cout << "请输入修改后书名" << endl;
    cin >> name;
    int i = 0;
    for (; i < b.size(); ++i)
    {
        if (b[i].book_number == c.book_number)break;
    }
    c.book_name = name;
    b[i].book_name = name;
    cout << "修改成功" << endl;
    BookManager::save_library(b);
    string record = "修改书籍名称 原名称:";
    record += pre_name + " 现名称:" + name + " ";
    BookManager::write_log(c, record);
}
void BookManager::modify_book_writer(vector<Book>& b, Book& c)
{
    string writer;
    string pre_writer = c.book_writer;
    cout << "现作者为：" << c.book_writer << endl;
    cout << "请输入修改后作者" << endl;
    cin >> writer;
    int i = 0;
    for (; i < b.size(); ++i) 
    {
        if (b[i].book_number == c.book_number)break;
    }
    c.book_writer = writer;
    b[i].book_writer = writer;
    cout << "修改成功" << endl;
    BookManager::save_library(b);
    string record = "修改书籍作者 原作者:";
    record += pre_writer + " 现作者:" + writer + " ";
    BookManager::write_log(c, record);
}
void BookManager::modify_book_press(vector<Book>& b, Book& c)
{
    string press;
    string pre_press = c.book_press;
    cout << "现出版社为：" << c.book_press << endl;
    cout << "请输入修改后出版社" << endl;
    cin >> press;
    int i = 0;
    for (; i < b.size(); ++i) 
    {
        if (b[i].book_number == c.book_number)break;
    }
    c.book_press = press;
    b[i].book_press = press;
    cout << "修改成功" << endl;
    BookManager:: save_library(b);
    string record = "修改书籍出版社 原出版社:";
    record += pre_press + " 现出版社:" + press + " ";
    BookManager::write_log(c, record);
}

void BookManager::view_book(vector<Book>& b, Book& c)
{
    while (true)
    {
        cout << "书籍信息为：" << endl;
        Book::show_book_info(c);
        BookManager::showMenu_viewbook();
        char choose_viewBook;
        cin >> choose_viewBook;
        switch (choose_viewBook)
        {
            case '0'://退出
            {
                cout << "退出查看系统" << endl;
                return;
            }
            case '1'://展示书籍内容
            {
                Book::show_book_content(c);
                cout << "请按任意键返回上一级菜单" << endl;
                break;
            }
            case '2'://搜索文本内容
            {
                cout << "请输入要搜索的词语，不超过十个汉字" << endl;
                string to_find;
                cin >> to_find;
                cout << "请稍等片刻，正在搜索中......" << endl << endl;
                string readfile;
                readfile = Book::get_book_content(c);
                if (readfile.length() == 0)
                {
                    cout << c.book_name << "文件为空！请查看" << c.book_address << "是否存在" << endl;
                }
                int max_ans_num = 10;   //最多支持的答案数量
                int* ans;
                ans = KMP(readfile, to_find, max_ans_num);
                int len = 600;    //输出接下来多少个字符
                int ans_cnt = 0;//实际输出的答案个数
                int ans_valid = *(ans);
                if (ans_valid == -1)
                {
                    cout << "查无此词！" << endl;
                    delete ans;
                    ans = NULL;
                }
                else
                {
                    for (int j = 0; j < max_ans_num; j++)
                    {
                        
                        //cout << "i, j" << i << "\t" << j;
                        if (ans_valid != -1 && *(ans+j) != -1)
                        {
                            int i = *(ans + j);
                            ans_cnt = j + 1;
                            string s2 = " ";
                            i = i - 1;
                            //cout << "i: " << i << endl;
                            s2 = readfile.substr(i, len);//输出接下来的len个字符
                            s2 = s2 + "...";
                            cout << "文段" << j + 1 << "为：" << endl << s2 << endl;
                            cout << endl;
                        }
                    }

                    cout << "输入“Y”在知识库中查询段落中出现的中医概念,输入“N”返回上级菜单" << endl;
                    string str;
                    cin >> str;
                    if (str == "Y")
                    {
                        cout << "要对哪一个段落进行查询？输入对应的段落序号" << endl;
                        int para_num;//输入的段落编号
                        cin >> para_num;
                        if (para_num < 1 || para_num > ans_cnt)
                        {
                            cin.clear();
                            cin.ignore();
                            cout << "没有对应段落序号，即将返回上级菜单" << endl;
                            break;
                        }
                        else
                        {
                        vector<Knowledge>base;
                        KnowledgeManager knowledge_base;
                        knowledge_base.base = base;
                        KnowledgeManager::fetch_base(knowledge_base.base);//读取KnowledgeBase
                        int start_num = *(ans + para_num - 1) - 1;//段落开头在文章中的下标
                        string content_to_search = readfile.substr(start_num, len);
                        KnowledgeManager::search_content_to_knowledge(content_to_search, knowledge_base.base);
                        //跳转到知识库中搜索；
                        }
                        
                    }
                    cout << "请按任意键返回上一级菜单" << endl;
                    delete ans;
                    ans = NULL;
                }
                break;
            }
            case '3'://修改书籍信息
            {
                BookManager::modify_book(b, c);
                break;
            }
        }
        system("pause");
        system("cls");
    }
}


void BookManager::show_allbook(vector<Book>& b)
{
    sort(b.begin(), b.end(), book_number_cmp);
    cout << "当前图书数目为" << b.size() << "本" << ",现有书籍信息为：" << endl;
    for (const auto& i : b)
    {
        Book::show_book_info(i);
    }
}
void BookManager::save_library(vector<Book>& b)
{
    sort(b.begin(), b.end(), book_number_cmp);
    ofstream ofs;
    ofs.open(LIBRARY_FILENAME, ios::out);   //以输出方式打开文件
    for (int i = 0; i < b.size(); ++i)  //录入每本书信息 
    {
        ofs << b[i].book_number << " " << b[i].book_name << " " << b[i].book_writer << " " << b[i].book_press << " " << b[i].book_address << endl;
        //将所有信息存储，信息之间以空格分隔，书之间以换行符分隔
    }
    cout << "保存成功" << endl;
    ofs.close();//关闭文件
}
void BookManager::fetch_library(vector<Book>& b)
{
    ifstream ifs;
    ifs.open(LIBRARY_FILENAME, ios::in);//读文件
    if (!ifs.is_open())//判断是否存在
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    Book temp;
    while (ifs >> temp.book_number && ifs >> temp.book_name && ifs >> temp.book_writer && ifs >> temp.book_press >> temp.book_address)//信息读取到temp中
    {
        b.push_back(temp);//将temp存在b中
    }
    ifs.close();
    if (b.empty())
    {
        cout << "文件为空" << endl;
    }
}
int BookManager::book_isValid(int num, vector<Book>& b)
{
    for (auto& i : b) {
        if (i.book_number == num)return 1; // already has a repeat number
    }
    if (num < 1 || num > 9999) return 2; //number is invalid
    return 0; // number is new and valid
}
bool BookManager::book_number_cmp(const Book& a, const Book& b)
{
    return a.book_number < b.book_number;
}