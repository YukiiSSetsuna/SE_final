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
    int* ans = new int[max_num];    //����������ٸ����
    for (int j = 0; j < max_num; j++)//��ʼ��Ϊ-1�����Կ��Ը���*(ans)�Ƿ����-1���ж������������
    {
        *(ans + j) = -1;
    }
    const char* S = Str.data();
    const char* T = Str_to_search.data();
    int i = 1;
    int j = 1;
    int cnt = 0;
    int next[21];   //���֧������ʮ������
    Next(T, next);  //����ģʽ��T,��ʼ��next����   
    while (i <= strlen(S) && cnt < max_num)
    {
        j = 1;
        while (i <= strlen(S) && j <= strlen(T)) {
            //j==0:����ģʽ���ĵ�һ���ַ��ͺ͵�ǰ���Ե��ַ�����ȣ�S[i-1]==T[j-1],�����Ӧλ���ַ���ȣ���������£�ָ��ǰ���Ե�����ָ���±�i��j�������
            if (j == 0 || S[i - 1] == T[j - 1]) {
                i++;
                j++;
            }
            else {
                j = next[j];//������Ե������ַ�����ȣ�i������j��Ϊ��ǰ�����ַ�����nextֵ
            }
        }
        if (j > strlen(T)) {//�������Ϊ�棬˵��ƥ��ɹ�
            ans[cnt] = i - (int)strlen(T);//����������������ַ������ı��е��±�
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
        cout <<b.book_name<< "�ļ�Ϊ�գ���鿴" <<b.book_address<< "�Ƿ����" << endl;
    }
    int max_ans_num = 10;   //���֧�ֵĴ�����
    int* ans;
    ans = KMP(readfile, str_to_find, max_ans_num);
    int len = 600;    //������������ٸ��ַ������ĵĻ�Ҫ��2��len=600��������300��
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
            s2 = readfile.substr(i-1, len);//�����������len���ַ���-1����������ռ�����ַ�
            s2 = s2 + "...";
            cout << "�Ķ�" << j + 1 << "Ϊ��" << endl << s2 << endl;
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
        //չʾ���˵�
        show_mainmenu();
        char choice;
        cin >> choice;
        switch (choice)
        {
        case'0'://�˳�
        {
            cout << "��ӭ�´�ʹ��" << endl;
            return 0;
        }
        case '1'://�����鼮���Ͽ�
        {
            BookManager::select_library_mainmenu(library);
            break;
        }
        case '2'://�������֪ʶ��
        {
            KnowledgeManager::select_base_mainmenu(base);
            break;
        }
        case '3'://����ȫ������
        {
            vector<Book>temp_lib;
            vector<Knowledge>temp_base;
            select_global_keyword(library, base, temp_lib, temp_base);
            if (temp_lib.empty() && temp_base.empty())  //û�з�����������
            {
                cout << "ȫ������û���ҵ��������" << endl;
            }
            else        
            {
                cout << "���ѵ���֪ʶ��" << temp_base.size() << "�����ֱ��ǣ�" << endl;
                for (int i = 0; i < temp_base.size(); ++i) {
                    Knowledge::show_knowledge_info(temp_base[i]);
                }
                cout <<endl<< "���ѵ����鼮������" << temp_lib.size() << "�����ֱ��ǣ�" << endl;
                for (int i = 0; i < temp_lib.size(); ++i) {
                    Book::show_book_info(temp_lib[i]);
                }
                cout << "�����һ���鿴��������Ӧ֪ʶ����в��ġ�" << endl;
            }
            break;
        }
        default:
        {
            cout << "ָ���������������" << endl;
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
    cout << "*****   ��ҽ֪ʶ��ϵͳ         *****" << endl;
    cout << "*****   �����鼮���Ͽ��밴1    *****" << endl;
    cout << "*****   �������֪ʶ���밴2    *****" << endl;
    cout << "*****   Ҫ����ȫ�������밴3    *****" << endl;
    cout << "*****   �˳�֪ʶ��ϵͳ�밴0    *****" << endl;
    cout << "************************************" << endl;
}
void select_global_keyword(vector<Book> library, vector<Knowledge> base, vector<Book>& temp_lib, vector<Knowledge>& temp_base)
{
    //library��base��ŵ���֪ʶ���е��鼮��֪ʶ��temp_lib��temp_base����Ƿ��������������鼮��֪ʶ
    cout << "��������Ҫ���ҵĹؼ���" << endl;
    string keyword;
    cin >> keyword;
    for (auto& i : base)
    {
        //�ж�֪ʶ�����Ƿ��йؼ���
        int* name_ans;
        name_ans = KMP(i.name, keyword, 5);
        int flag_name = *(name_ans);
        //�ж��������Ƿ��йؼ���
        string content = Knowledge::get_knowledge_content(i);
        int* content_ans;
        content_ans = KMP(content, keyword, 5);
        int flag_content = *(content_ans);
        if (flag_content != -1 || flag_name != -1)
        {
            temp_base.push_back(i);//�еĻ��ͷ���temp_base
        }
        delete name_ans;
        name_ans = NULL;
        delete content_ans;
        content_ans = NULL;
    }

    for (auto& i : library)
    {
        //�ж������Ƿ��йؼ���
        int* name_ans;
        name_ans = KMP(i.book_name, keyword, 2);
        int flag_name = *(name_ans);
        //�ж��������Ƿ��йؼ���
        int* writer_ans;
        writer_ans = KMP(i.book_writer, keyword, 2);
        int flag_writer = *(writer_ans);
        //�ж��������Ƿ��йؼ���
        string content = Book::get_book_content(i);
        int* content_ans;
        content_ans = KMP(content, keyword, 10);
        int flag_content = *(content_ans);

        if (flag_content != -1 || flag_writer != -1 || flag_name != -1 || i.book_name == keyword || i.book_writer == keyword || i.book_press == keyword)
        {
            temp_lib.push_back(i);//�еĻ��ͷ���temp_lib
        }
        delete name_ans;
        name_ans = NULL;
        delete writer_ans;
        writer_ans = NULL;
        delete content_ans;
        content_ans = NULL;
    }
}

void get_files_list(string path, vector<string>& files) //���ڻ�ȡ�ļ����������ļ����ļ���������python�е�listdir
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