#include"Book.h"
#include"BookManager.h"
using namespace std;


Book::Book()
{

}
Book::~Book()
{

}
void Book::show_book_info(Book b)
{
    cout << "��ţ�" << b.book_number << "\t\t������" << b.book_name << "\t\t���ߣ�"
        << b.book_writer << "\t\t�����磺" << b.book_press << endl;
}
string Book::get_book_content(Book b)
{
    ifstream ifs;
    string book_path = "data/book/" + b.book_address;
    ifs.open(book_path, ios::in);//���ļ�
    if (!ifs.is_open())//�ж��Ƿ����
    {
        //cout << "�ļ�������" << endl;
        ifs.close();
        string str_empty = "";
        return str_empty;
    }
    else
    {
        string content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
        ifs.close(); // ��ʱ�ر�fstream
        return content;
    }
}
void Book::show_book_content(Book b)
{
        string content;
        cout << b.book_address << endl << endl;
        cout << endl << endl;
        content = get_book_content(b);
        cout << content << endl << endl;
}
int Book::deleteBook(vector<Book>& b, Book c)
{
    int i;
    int flag = -1;
    for (i = 0; i < b.size(); i++) //ͨ����Ų����Ȿ��
    {
        if (b[i].book_number == c.book_number)
        {
            string book_path = "data/book/" + b[i].book_address;//ɾ��txt�ļ�
            const char* p = book_path.data();
            flag = remove(p);
            break;
        }
    }
    if (flag == 0)
    {
        b.erase(b.begin() + i);//��library��ɾ���Ȿ��
        cout << "ɾ���ɹ�" << endl;
    }
    else
    {
        cout << "ɾ��ʧ��" << endl;
        //cout << strerror(errno) << endl;
    }
    return flag;
}
