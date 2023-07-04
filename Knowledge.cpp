#include "Knowledge.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

Knowledge::Knowledge()
{
	
}
Knowledge::~Knowledge()
{

}

void Knowledge::show_knowledge_info(Knowledge knowledge)
{
	cout << "类型：" << TYPE_NAME[knowledge.type] << "\t知识名：" << knowledge.name << endl;
}
void Knowledge::show_knowledge_content(Knowledge knowledge)
{
    cout << "内容为：" << endl;
    string content = get_knowledge_content(knowledge);
    cout << content << endl << endl;
}
int Knowledge::delete_knowledge(vector<Knowledge>& b, Knowledge knowledge)
{
    int i;
    int flag = -1;
    for (i = 0; i < b.size(); i++) //通过编号查找这本书
    {
        if (b[i].name == knowledge.name && b[i].type == knowledge.type)//这里其实会出现问题，因为知识名并不是唯一的
        {
            string book_path = "data/knowledge/" + TYPE_NAME[b[i].type] + "/" + b[i].knowledge_address;//删除txt文件
            const char* p = book_path.data();
            flag = remove(p);
            break;
        }
    }
    if (flag == 0)
    {
        b.erase(b.begin() + i);//在base中删除这本书
        cout << "删除成功" << endl;
    }
    else
    {
        cout << "删除失败" << endl;
        //cout << strerror(errno) << endl;
    }
    return flag;
}

string Knowledge::get_knowledge_content(Knowledge knowledge)
{
    ifstream ifs;
    string knowledge_path = "data/knowledge/" + TYPE_NAME[knowledge.type] + "/" + knowledge.knowledge_address;
    //cout << knowledge_path << endl;
    ifs.open(knowledge_path, ios::in);//读文件
    if (!ifs.is_open())//判断是否存在
    {
        cout << knowledge.name << "该文件不存在" << endl;
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