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
	cout << "���ͣ�" << TYPE_NAME[knowledge.type] << "\t֪ʶ����" << knowledge.name << endl;
}
void Knowledge::show_knowledge_content(Knowledge knowledge)
{
    cout << "����Ϊ��" << endl;
    string content = get_knowledge_content(knowledge);
    cout << content << endl << endl;
}
int Knowledge::delete_knowledge(vector<Knowledge>& b, Knowledge knowledge)
{
    int i;
    int flag = -1;
    for (i = 0; i < b.size(); i++) //ͨ����Ų����Ȿ��
    {
        if (b[i].name == knowledge.name && b[i].type == knowledge.type)//������ʵ��������⣬��Ϊ֪ʶ��������Ψһ��
        {
            string book_path = "data/knowledge/" + TYPE_NAME[b[i].type] + "/" + b[i].knowledge_address;//ɾ��txt�ļ�
            const char* p = book_path.data();
            flag = remove(p);
            break;
        }
    }
    if (flag == 0)
    {
        b.erase(b.begin() + i);//��base��ɾ���Ȿ��
        cout << "ɾ���ɹ�" << endl;
    }
    else
    {
        cout << "ɾ��ʧ��" << endl;
        //cout << strerror(errno) << endl;
    }
    return flag;
}

string Knowledge::get_knowledge_content(Knowledge knowledge)
{
    ifstream ifs;
    string knowledge_path = "data/knowledge/" + TYPE_NAME[knowledge.type] + "/" + knowledge.knowledge_address;
    //cout << knowledge_path << endl;
    ifs.open(knowledge_path, ios::in);//���ļ�
    if (!ifs.is_open())//�ж��Ƿ����
    {
        cout << knowledge.name << "���ļ�������" << endl;
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