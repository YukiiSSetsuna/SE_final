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
    cout << "编号：" << b.book_number << "\t\t书名：" << b.book_name << "\t\t作者："
        << b.book_writer << "\t\t出版社：" << b.book_press << endl;
}
string Book::get_book_content(Book b)
{
    ifstream ifs;
    string book_path = "data/book/" + b.book_address;
    ifs.open(book_path, ios::in);//读文件
    if (!ifs.is_open())//判断是否存在
    {
        //cout << "文件不存在" << endl;
        ifs.close();
        string str_empty = "";
        return str_empty;
    }
    else
    {
        string content((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
        ifs.close(); // 及时关闭fstream
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
    for (i = 0; i < b.size(); i++) //通过编号查找这本书
    {
        if (b[i].book_number == c.book_number)
        {
            string book_path = "data/book/" + b[i].book_address;//删除txt文件
            const char* p = book_path.data();
            flag = remove(p);
            break;
        }
    }
    if (flag == 0)
    {
        b.erase(b.begin() + i);//在library中删除这本书
        cout << "删除成功" << endl;
    }
    else
    {
        cout << "删除失败" << endl;
        //cout << strerror(errno) << endl;
    }
    return flag;
}
