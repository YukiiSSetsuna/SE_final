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
        //չʾ���˵�
        BookManager::showMenu_bookmanager();
        char choice;
        cin >> choice;
        switch (choice)
        {
            case'0'://�˳�
            {
                cout << "��ӭ�´�ʹ��" << endl;
                return;
            }
            case '1'://����鼮
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
            case '2'://�޸��鼮
            {
                bool suc = BookManager::admin_Login();
                if (suc)
                {
                    cout << "���ȼ���������Ҫ�޸ĵ��鼮" << endl;
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
            case '3'://չʾ����ͼ��
            {
                if (b.empty())
                {
                    cout << "��ǰ��ͼ��" << endl;
                    break;
                }
                BookManager::show_allbook(b);
                break;
            }
            case '4'://�����鼮
            {   
                Book temp = BookManager::search_book(b);
                if (temp.book_number != -1)
                {
                    BookManager::view_book(b, temp);
                }
                break;
            }
            case  '5'://����Ա�޸�
            {
                bool legal = BookManager::admin_Login();
                if (!legal) { break; }
                else
                {
                    //ִ���޸�
                    BookManager::register_admin();
                }
                break;
            }
            default:
            {
                cout << "ָ���������������" << endl;
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
        cout << "���������Ա�˻�����" << endl;
        cin >> name;
        cout << "���������Ա�˻����룺" << endl;
        cin >> password;
        string login = name + password;
        string standard = BookManager::read_admininfo();
        //cout << "test:" << standard << endl;
        //cout << "test:" << login << endl;
        if (login == standard)
        {
            cout << "��ӭ��½��" << endl;
            return true;
        }
        else
        {
            cout << "��¼ʧ�ܣ��û�������������������룿" << endl;
            cout << "����1�������룬����0�˳�" << endl;
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
    ifs.open(info_path);//���ļ�
    if (!ifs.is_open())//�ж��Ƿ����
    {
        cout << "�ļ�������" << endl;
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
    ifs.close(); // ��ʱ�ر�fstream
    return content;
}

void BookManager::register_admin()
{
    string new_name;
    string new_password;
    cout << "�������¹���Ա�˻�����" << endl;
    cin >> new_name;
    cout << "�������¹���Ա�˻�����" << endl;
    cin >> new_password;
    string info_path = "data/admin/admin.txt";
    ofstream ofs;
    ofs.open(info_path);//���ļ�
    if (!ofs.is_open())//�ж��Ƿ����
    {
        cout << "�ļ�������" << endl;
        ofs.close();
    }
    ofs << new_name + "\n" + new_password;
    ofs.close();
}

void BookManager::write_log(Book& new_book,string c)
{
    string info_path = "data/admin/log_book.txt";
    ofstream ofs;
    ofs.open(info_path, ios::app);//���ļ�׷��
    if (!ofs.is_open())//�ж��Ƿ����
    {
        cout << "�ļ�������" << endl;
        ofs.close();
    }
    time_t now = time(NULL);
    string time = convertTimeStamp2TimeStr(now);
    ofs << time + " " + c + "������" + new_book.book_name << endl;
}

void BookManager::showMenu_bookmanager()
{
    cout << "************************************" << endl;
    cout << "*****     ��ҽ�鼮���Ͽ�ϵͳ   *****" << endl;
    cout << "*****     ����鼮��Ϣ�밴1    *****" << endl;
    cout << "*****     �޸��鼮��Ϣ�밴2    *****" << endl;
    cout << "*****     ��ʾ�鼮��Ϣ�밴3    *****" << endl;
    cout << "*****     �����鼮��Ϣ�밴4    *****" << endl;
    cout << "*****     �޸Ĺ���Ա��Ϣ�밴5    *****" << endl;
    cout << "*****     �˳�ͼ��ϵͳ�밴0    *****" << endl;
    cout << "************************************" << endl;
}
void BookManager::showMenu_searchbook()
{
    cout << "**************************************" << endl;
    cout << "*****   ��ѡ���������鼮�ķ�ʽ   *****" << endl;
    cout << "*****   ͨ�����������밴1        *****" << endl;
    cout << "*****   ͨ���鼮��Ų����밴2    *****" << endl;
    cout << "*****   ͨ�����߲����밴3        *****" << endl;
    cout << "*****   ͨ������������밴4      *****" << endl;
    cout << "*****   ͨ���ؼ��ʲ����밴5      *****" << endl;
    cout << "*****   �˳������밴0            *****" << endl;
    cout << "**************************************" << endl;
}
void BookManager::showMenu_modifybook()
{
    cout << "**************************************" << endl;
    cout << "*****     ����Ҫ�޸ĸ���������Ϣ *****" << endl;
    cout << "*****     �޸��鼮����밴1      *****" << endl;
    cout << "*****     �޸��鼮���밴2        *****" << endl;
    cout << "*****     �޸������밴3          *****" << endl;
    cout << "*****     �޸ĳ������밴4        *****" << endl;
    cout << "*****     ɾ�������밴5          *****" << endl;
    cout << "*****     �˳��޸��밴0          *****" << endl;
    cout << "**************************************" << endl;
}
void BookManager::showMenu_viewbook()
{
    cout << "**************************************" << endl;
    cout << "*****     ����Ը��鼮�����ִ��� *****" << endl;
    cout << "*****     չʾ�鼮�����밴1      *****" << endl;
    cout << "*****     �����ı������밴2      *****" << endl;
    cout << "*****     �޸��鼮��Ϣ�밴3      *****" << endl;
    cout << "*****     �˳��鿴ϵͳ�밴0      *****" << endl;
    cout << "**************************************" << endl;
}

Book BookManager::search_book(vector<Book>& b)
{
    Book tmp;
    vector<Book>c;//Ϊ��ֹ�鼮������Ϣ�ظ�������Ϣ�ظ��Ĳ��ҽ������c��
    tmp.book_number = 0;
    BookManager::showMenu_searchbook();
    char choose2;
    cin >> choose2;
    switch (choose2)
    {
        case '1'://����������
        {
            BookManager::search_book_name(b, c);
            break;
        }
        case '2'://���
        {
            BookManager::search_book_number(b, c);
            break;
        }
        case '3'://����
        {
            BookManager::search_book_writer(b, c);
            break;
        }
        case '4'://������
        {
            BookManager::search_book_press(b, c);
            break;
        }
        case '5'://�ؼ���
        {
            BookManager::search_book_keyword(b, c);
            break;
        }
        case '0'://�˳�
        {
            cout << "��ӭ�´�ʹ��" << endl;
            tmp.book_number = -1;//�������鼮�ı����Ϊ-1������û���ҵ��鼮
            break;
        }
        default:
        {
            cout << "ָ���������������" << endl;
        }
    }
    if (tmp.book_number != -1)
    {
        if (c.empty())  //û�з�����������
        {
            cout << "���޴���" << endl;
            tmp.book_number = -1;
        }
        else if (c.size() == 1) //����������ֻ��һ����
        {
            //view_book(b, c[0]);
            return c[0];
        }
        else        //���������Ĳ�ֹһ����
        {
            cout << "��ȷ����Ҫ���ҵ��鼮" << endl;
            int i;
            for (i = 0; i < c.size(); ++i) {
                cout << i + 1 << "��\t";
                Book::show_book_info(c[i]);
            }
            cout << "��ѡ����Ҫ���ҵ��鼮��ţ�ע�ⲻ���鼮���" << endl;
            int num;
            cin >> num;
            if (num > i+1 || num < 0)
            {
                cout << "��������δ���б��ڣ�Ĭ��ѡ���һ��" << endl;
                return c[0];
            }
            //view_book(b, c[i]);
            return c[num-1];
        }
    }
    return tmp;
}
void BookManager::search_book_number(vector<Book>& b, vector<Book>& c) {
    cout << "��������Ҫ���ҵ��鼮���" << endl;
    int num;
    cin >> num;
    if (BookManager::book_isValid(num, b) == 2)
    {
        cout << "�����Ϊ������������������" << endl;
        cin.clear();
        cin.ignore();//�����������ܹؼ���û�еĻ���һֱѭ��
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
    cout << "��������Ҫ���ҵ��鼮����" << endl;
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
    cout << "��������Ҫ���ҵ��鼮����" << endl;
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
    cout << "��������Ҫ���ҵ��鼮������" << endl;
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
    cout << "��������Ҫ���ҵĹؼ��ʣ�������ʮ�����֣�" << endl;
    cin >> keyword;
    for (auto& i : b) 
    {   //��������
        int* name_ans;
        name_ans = KMP(i.book_name, keyword, 5);
        int flag_name = *(name_ans);
        //����������
        int* writer_ans;
        writer_ans = KMP(i.book_writer, keyword, 5);
        int flag_writer = *(writer_ans);
        //�����鼮����
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
    cout << "��ӳɹ�" << endl;
    BookManager::save_library(b);
    string record = "����鼮��";
    BookManager::write_log(newbook, record);

}
void BookManager::add_book_number(vector<Book>& b, Book& c) {
    int num;
    cout << "�������ţ������Ϊ�������Ҳ����ظ�" << endl;
    while (true)
    {
        cin >> num;
        if (BookManager::book_isValid(num, b) != 0)
        {
            cout << "�����Ϊ�������Ҳ����ظ�������������" << endl;
            cin.clear();
            cin.ignore();//�����������ܹؼ���û�еĻ���һֱѭ��
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
    cout << "����������" << endl;
    cin >> name;
    c.book_name = name;
}
void BookManager::add_book_writer(vector<Book>& b, Book& c) {
    string writer;
    cout << "����������" << endl;
    cin >> writer;
    c.book_writer = writer;
}
void BookManager::add_book_press(vector<Book>& b, Book& c) {
    string press;
    cout << "�����������" << endl;
    cin >> press;
    c.book_press = press;
}
void BookManager::add_book_address(vector<Book>& b, Book& c)
{
    string address;
    cout << "�뽫txt��ʽ���鼮����������Ŀ¼��'data/book/'�ļ��е��У���ȷ�������ʽΪANSI�������ȡ���Ļ�������룡" << endl;
    cout << "�������鼮�ļ���,��ʽΪ ������.txt�� " << endl;
    while (true)
    {
        cin >> address;
        ifstream ifs;
        string file_path = "data/book/" +  address;
        ifs.open(file_path, ios::in);//���ļ�
        if (!ifs.is_open())//�ж��Ƿ����
        {
            cout << "�ļ�������" << endl;
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
            case '0'://�˳�
            {
                cout << "�˳��޸�ϵͳ" << endl;
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
            case '5'://ɾ��
            {
                int flag = Book::deleteBook(b, c);
                if (flag == 0)
                {
                BookManager::save_library(b);
                cout << "�����ɾ�����˳��޸�ϵͳ" << endl;
                string record = "ɾ���鼮��";
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
                cout << "ָ������޸�ʧ��" << endl;
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
    cout << "�ֱ��Ϊ��" << c.book_number << endl;
    cout << "�������޸ĺ���" << endl;
    cin >> number;
    if (BookManager::book_isValid(number, b) != 0)//�жϱ���Ƿ���Ч
    {
        cout << "����ظ����޸�ʧ��" << endl;
    }
    else {
        int i = 0;
        for (; i < b.size(); ++i) 
        {
            if (b[i].book_number == c.book_number)break;
        }
        c.book_number = number;
        b[i].book_number = number;
        cout << "�޸ĳɹ�" << endl;
        BookManager::save_library(b);
        string record = "�޸��鼮��� ԭ���:";
        record += to_string(pre_number) + " �ֱ��:" + to_string(number) + " ";
        BookManager::write_log(c, record);
    }
}
void BookManager::modify_book_name(vector<Book>& b, Book& c)
{
    string name;
    string pre_name = c.book_name;
    cout << "������Ϊ��" << c.book_name << endl;
    cout << "�������޸ĺ�����" << endl;
    cin >> name;
    int i = 0;
    for (; i < b.size(); ++i)
    {
        if (b[i].book_number == c.book_number)break;
    }
    c.book_name = name;
    b[i].book_name = name;
    cout << "�޸ĳɹ�" << endl;
    BookManager::save_library(b);
    string record = "�޸��鼮���� ԭ����:";
    record += pre_name + " ������:" + name + " ";
    BookManager::write_log(c, record);
}
void BookManager::modify_book_writer(vector<Book>& b, Book& c)
{
    string writer;
    string pre_writer = c.book_writer;
    cout << "������Ϊ��" << c.book_writer << endl;
    cout << "�������޸ĺ�����" << endl;
    cin >> writer;
    int i = 0;
    for (; i < b.size(); ++i) 
    {
        if (b[i].book_number == c.book_number)break;
    }
    c.book_writer = writer;
    b[i].book_writer = writer;
    cout << "�޸ĳɹ�" << endl;
    BookManager::save_library(b);
    string record = "�޸��鼮���� ԭ����:";
    record += pre_writer + " ������:" + writer + " ";
    BookManager::write_log(c, record);
}
void BookManager::modify_book_press(vector<Book>& b, Book& c)
{
    string press;
    string pre_press = c.book_press;
    cout << "�ֳ�����Ϊ��" << c.book_press << endl;
    cout << "�������޸ĺ������" << endl;
    cin >> press;
    int i = 0;
    for (; i < b.size(); ++i) 
    {
        if (b[i].book_number == c.book_number)break;
    }
    c.book_press = press;
    b[i].book_press = press;
    cout << "�޸ĳɹ�" << endl;
    BookManager:: save_library(b);
    string record = "�޸��鼮������ ԭ������:";
    record += pre_press + " �ֳ�����:" + press + " ";
    BookManager::write_log(c, record);
}

void BookManager::view_book(vector<Book>& b, Book& c)
{
    while (true)
    {
        cout << "�鼮��ϢΪ��" << endl;
        Book::show_book_info(c);
        BookManager::showMenu_viewbook();
        char choose_viewBook;
        cin >> choose_viewBook;
        switch (choose_viewBook)
        {
            case '0'://�˳�
            {
                cout << "�˳��鿴ϵͳ" << endl;
                return;
            }
            case '1'://չʾ�鼮����
            {
                Book::show_book_content(c);
                cout << "�밴�����������һ���˵�" << endl;
                break;
            }
            case '2'://�����ı�����
            {
                cout << "������Ҫ�����Ĵ��������ʮ������" << endl;
                string to_find;
                cin >> to_find;
                cout << "���Ե�Ƭ�̣�����������......" << endl << endl;
                string readfile;
                readfile = Book::get_book_content(c);
                if (readfile.length() == 0)
                {
                    cout << c.book_name << "�ļ�Ϊ�գ���鿴" << c.book_address << "�Ƿ����" << endl;
                }
                int max_ans_num = 10;   //���֧�ֵĴ�����
                int* ans;
                ans = KMP(readfile, to_find, max_ans_num);
                int len = 600;    //������������ٸ��ַ�
                int ans_cnt = 0;//ʵ������Ĵ𰸸���
                int ans_valid = *(ans);
                if (ans_valid == -1)
                {
                    cout << "���޴˴ʣ�" << endl;
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
                            s2 = readfile.substr(i, len);//�����������len���ַ�
                            s2 = s2 + "...";
                            cout << "�Ķ�" << j + 1 << "Ϊ��" << endl << s2 << endl;
                            cout << endl;
                        }
                    }

                    cout << "���롰Y����֪ʶ���в�ѯ�����г��ֵ���ҽ����,���롰N�������ϼ��˵�" << endl;
                    string str;
                    cin >> str;
                    if (str == "Y")
                    {
                        cout << "Ҫ����һ��������в�ѯ�������Ӧ�Ķ������" << endl;
                        int para_num;//����Ķ�����
                        cin >> para_num;
                        if (para_num < 1 || para_num > ans_cnt)
                        {
                            cin.clear();
                            cin.ignore();
                            cout << "û�ж�Ӧ������ţ����������ϼ��˵�" << endl;
                            break;
                        }
                        else
                        {
                        vector<Knowledge>base;
                        KnowledgeManager knowledge_base;
                        knowledge_base.base = base;
                        KnowledgeManager::fetch_base(knowledge_base.base);//��ȡKnowledgeBase
                        int start_num = *(ans + para_num - 1) - 1;//���俪ͷ�������е��±�
                        string content_to_search = readfile.substr(start_num, len);
                        KnowledgeManager::search_content_to_knowledge(content_to_search, knowledge_base.base);
                        //��ת��֪ʶ����������
                        }
                        
                    }
                    cout << "�밴�����������һ���˵�" << endl;
                    delete ans;
                    ans = NULL;
                }
                break;
            }
            case '3'://�޸��鼮��Ϣ
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
    cout << "��ǰͼ����ĿΪ" << b.size() << "��" << ",�����鼮��ϢΪ��" << endl;
    for (const auto& i : b)
    {
        Book::show_book_info(i);
    }
}
void BookManager::save_library(vector<Book>& b)
{
    sort(b.begin(), b.end(), book_number_cmp);
    ofstream ofs;
    ofs.open(LIBRARY_FILENAME, ios::out);   //�������ʽ���ļ�
    for (int i = 0; i < b.size(); ++i)  //¼��ÿ������Ϣ 
    {
        ofs << b[i].book_number << " " << b[i].book_name << " " << b[i].book_writer << " " << b[i].book_press << " " << b[i].book_address << endl;
        //��������Ϣ�洢����Ϣ֮���Կո�ָ�����֮���Ի��з��ָ�
    }
    cout << "����ɹ�" << endl;
    ofs.close();//�ر��ļ�
}
void BookManager::fetch_library(vector<Book>& b)
{
    ifstream ifs;
    ifs.open(LIBRARY_FILENAME, ios::in);//���ļ�
    if (!ifs.is_open())//�ж��Ƿ����
    {
        cout << "�ļ�������" << endl;
        ifs.close();
        return;
    }

    Book temp;
    while (ifs >> temp.book_number && ifs >> temp.book_name && ifs >> temp.book_writer && ifs >> temp.book_press >> temp.book_address)//��Ϣ��ȡ��temp��
    {
        b.push_back(temp);//��temp����b��
    }
    ifs.close();
    if (b.empty())
    {
        cout << "�ļ�Ϊ��" << endl;
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