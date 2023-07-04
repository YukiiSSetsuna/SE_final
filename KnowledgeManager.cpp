#include "KnowledgeManager.h"
#include "Knowledge.h"
#include "Global_Function.h"

using namespace std;

KnowledgeManager::KnowledgeManager()
{

}
KnowledgeManager::KnowledgeManager(vector<Knowledge> base)
{
	base = base;
}
KnowledgeManager::~KnowledgeManager()
{

}

bool KnowledgeManager::admin_Login()
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

string KnowledgeManager::read_admininfo()
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

void KnowledgeManager::register_admin()
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

void KnowledgeManager::write_log(Knowledge& new_k, string c)
{
    string info_path = "data/admin/log_k.txt";
    ofstream ofs;
    ofs.open(info_path, ios::app);//���ļ�׷��
    if (!ofs.is_open())//�ж��Ƿ����
    {
        cout << "�ļ�������" << endl;
        ofs.close();
    }
    time_t now = time(NULL);
    string time = convertTimeStamp2TimeStr(now);
    ofs << time + " " + c << endl;
}

void KnowledgeManager::select_base_mainmenu(vector<Knowledge>& b)
{
    while (true)
    {
        //չʾ���˵�
        showMenu_knowledgebase();
        char choice;
        cin >> choice;
        switch (choice)
        {
        case'0'://�˳�
        {
            cout << "��ӭ�´�ʹ��" << endl;
            return;
        }
        case'1'://���֪ʶ
        {
            bool suc = BookManager::admin_Login();
            if (suc)
            {
                KnowledgeManager::add_knowledge(b);
                break;
            }
            else
                break;
            
        }
        case'2'://�޸�֪ʶ
        {
            bool suc = BookManager::admin_Login();
            if (suc)
            {
                cout << "���ȼ���������Ҫ�޸ĵ�֪ʶ" << endl;
                Knowledge temp = KnowledgeManager::search_knowledge(b);
                if (temp.type != -1)
                {
                    KnowledgeManager::modify_knowledge(b, temp);
                }
                break;
            }
            else
                break;

        }
        case'3'://չʾ����֪ʶ
        {
            if (b.empty())
            {
                cout << "��ǰ֪ʶ��Ϊ�գ�" << endl;
                break;
            }
            KnowledgeManager::show_allknowledge(b);
            break;
        }
        case'4'://����֪ʶ
        {
            Knowledge knowledge;
            knowledge = KnowledgeManager::search_knowledge(b);
            if (knowledge.type != -1)
            {
                KnowledgeManager::view_knowledge(knowledge);//�Ƿ�Ҫ�������õ���֪ʶ���޸�
                cout << "����\"�޸�\"�ԶԸ�֪ʶ�����޸�,���������򷵻��ϼ��˵�" << endl;
                string str;
                cin >> str;
                if (str == "�޸�")
                    KnowledgeManager::modify_knowledge(b, knowledge);
                else
                    break;
            }
            break;
        }
        case '5':
        {
            bool legal = KnowledgeManager::admin_Login();
            if (!legal) { break; }
            else
            {
                //ִ���޸�
                KnowledgeManager::register_admin();
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

void KnowledgeManager::showMenu_knowledgebase()
{
    cout << "************************************" << endl;
    cout << "*****     ��ҽ����֪ʶ��ϵͳ   *****" << endl;
    cout << "*****     ���֪ʶ��Ϣ�밴1    *****" << endl;
    cout << "*****     �޸�֪ʶ��Ϣ�밴2    *****" << endl;
    cout << "*****     ��ʾȫ��֪ʶ�밴3    *****" << endl;
    cout << "*****     ����֪ʶ�밴4        *****" << endl;
    cout << "*****     �޸Ĺ���Ա��Ϣ�밴5    *****" << endl;
    cout << "*****     �˳�ϵͳ�밴0        *****" << endl;
    cout << "************************************" << endl;
}
void KnowledgeManager::showMenu_search_knowledge()
{
    cout << "************************************" << endl;
    cout << "*****   ��ѡ����Ҫ����ʲô֪ʶ *****" << endl;
    cout << "*****   �������ͼ����밴1      *****" << endl;
    cout << "*****   ������Ŀ�������밴2    *****" << endl;
    cout << "*****   ���ݹؼ��������밴3    *****" << endl;
    cout << "*****   �˳�����ϵͳ�밴0      *****" << endl;
    cout << "************************************" << endl;
}
void KnowledgeManager::showMenu_modify_knowledge()
{
    cout << "**************************************" << endl;
    cout << "*****   ����Ҫ�޸ĸ�֪ʶʲô��Ϣ *****" << endl;
    cout << "*****   �޸�֪ʶ�����밴1        *****" << endl;
    cout << "*****   �޸�֪ʶ���밴2          *****" << endl;
    cout << "*****   ɾ����֪ʶ�밴3          *****" << endl;
    cout << "*****   �˳��޸��밴0            *****" << endl;
    cout << "**************************************" << endl;
}


Knowledge KnowledgeManager::search_knowledge(vector<Knowledge>& b)
{
    KnowledgeManager::showMenu_search_knowledge();
    Knowledge temp;
    vector<Knowledge>c;//Ϊ��ֹ�鼮������Ϣ�ظ�������Ϣ�ظ��Ĳ��ҽ������c��
    temp.type = 0;
    char choice;
    cin >> choice;
    switch (choice)
    {
    case '1'://������������
    {
        KnowledgeManager::search_knowledge_type(b, c);
        break;
    }
    case '2'://������Ŀ������
    {
        KnowledgeManager::search_knowledge_name(b, c);
        break;
    }
    case '3'://���ݹؼ�������
    {
        KnowledgeManager::search_knowledge_keyword(b, c);
        break;
    }
    case '0'://�˳�
    {
        cout << "��ӭ�´�ʹ��" << endl;
        temp.type = -1;
        break;
    }
    default:
    {
        cout << "ָ���������������" << endl;
    }
    }
    if (temp.type != -1)
    {
        if (c.empty())  //û�з���������֪ʶ
        {
            cout << "û���ҵ���Ӧ֪ʶ" << endl;
            temp.type = -1;
        }
        else if (c.size() == 1) //����������ֻ��һ��֪ʶ
        {
            //KnowledgeManager::view_knowledge(base, c[0]);
            return c[0];
        }
        else        //���������Ĳ�ֹһ��֪ʶ
        {
            cout << "��ȷ����Ҫ���ҵ�֪ʶ" << endl;
            int i;
            for (i = 0; i < c.size(); ++i) {
                cout << i + 1 << "��\t";
                Knowledge::show_knowledge_info(c[i]);
            }
            cout << "��ѡ����Ҫ���ҵ�֪ʶ���" << endl;
            cin >> i;
            //KnowledgeManager::view_knowledge(base, c[i-1]);
            return c[i - 1];
        }
    }
    return temp;
}
void KnowledgeManager::search_knowledge_type(vector<Knowledge>& b, vector<Knowledge>& c)
{
    cout << "��������Ҫ���ҵ�֪ʶ����";
    cout << "��֪ʶ���Ͱ��� \"����\", \"���\", \"�η�\", \"��ҽ����\" " << endl;
    string type;
    cin >> type;
    for (auto& i : b) 
    {
        if (TYPE_NAME[i.type] == type)
        {
            c.push_back(i);
        }
    }
}
void KnowledgeManager::search_knowledge_name(vector<Knowledge>& b, vector<Knowledge>& c)
{
    cout << "��������Ҫ���ҵ�֪ʶ��" << endl;
    string name;
    cin >> name;
    for (auto& i : b) 
    {
        //����֪ʶ���Ƿ�����ؼ��ʣ�������Ұ��ף�����֪ʶ�������׷�
        int* name_ans;
        name_ans = KMP(i.name, name, 5);
        int flag_name = *(name_ans);
        //���ҹؼ������Ƿ����֪ʶ����������Ұ��׷�������֪ʶ��������
        int* reverse_name_ans;
        reverse_name_ans = KMP(name, i.name, 5);
        int flag_reverse_name = *(reverse_name_ans);
        if (i.name == name || flag_name != -1 || flag_reverse_name != -1)
        {
            c.push_back(i);
        }
    }
}
void KnowledgeManager::search_knowledge_keyword(vector<Knowledge>& base, vector<Knowledge>& c)
{
    cout << "��������Ҫ���ҵĹؼ���" << endl;
    string keyword;
    cin >> keyword;
    for (auto& i : base)
    {
        //����֪ʶ��
        int* name_ans;
        name_ans = KMP(i.name, keyword, 5);
        int flag_name = *(name_ans);
        //����֪ʶ����
        string content = Knowledge::get_knowledge_content(i);
        int* content_ans;
        content_ans = KMP(content, keyword, 5);
        int flag_content = *(content_ans);
        if (flag_content != -1 || flag_name != -1)
        {
            c.push_back(i);
        }
        delete name_ans;
        name_ans = NULL;
        delete content_ans;
        content_ans = NULL;
    }
}

void KnowledgeManager::add_knowledge(vector<Knowledge>& base)
{
    Knowledge newknowledge;
    KnowledgeManager::add_knowledge_type(base, newknowledge);
    KnowledgeManager::add_knowledge_name(base, newknowledge);
    KnowledgeManager::add_knowledge_address(base, newknowledge);
    base.push_back(newknowledge);
    cout << "��ӳɹ�" << endl;
    KnowledgeManager::save_base(base);
    string record = "���֪ʶ ֪ʶ����:";
    record += TYPE_NAME[newknowledge.type] + " ֪ʶ��:" + newknowledge.name;
    KnowledgeManager::write_log(newknowledge, record);
}
void KnowledgeManager::add_knowledge_type(vector<Knowledge>& b, Knowledge& c)
{
    string type;
    cout << "������֪ʶ����" << "\t��֪ʶ���Ͱ��� \"����\", \"���\", \"�η�\", \"��ҽ����\" " << endl;
    while (true)
    {
        cin >> type;
        int type_num = KnowledgeManager::knowledge_type_isExist(type, c);
        if (type_num != -1)
        {
            c.type = type_num;
            break;
        }
        else
        {
            cout << "���ʹ�������������" << endl;
        }
    }
}
void KnowledgeManager::add_knowledge_name(vector<Knowledge>& b, Knowledge& c)
{
    string name;
    cout << "������֪ʶ��" << endl;
    cin >> name;
    c.name = name;
}
void KnowledgeManager::add_knowledge_address(vector<Knowledge>& b, Knowledge& c)
{
    string address;
    cout << "�뽫txt��ʽ��֪ʶ����������Ŀ¼��'data/knowledge/��Ӧ֪ʶ����'���ļ��е��У�" << endl;
    cout << "��ȷ�������ʽΪANSI�������ȡ���Ļ�������룡" << endl;
    cout << "������֪ʶ�ļ���,��ʽΪ ��֪ʶ.txt�� " << endl;
    while (true)
    {
        address = "";
        cin >> address;
        string file_path = "data/knowledge/" + TYPE_NAME[c.type] + "/" + address;
        ifstream ifs;
        ifs.open(file_path, ios::in);//���ļ�
        if (!ifs.is_open())//�ж��Ƿ����
        {
            cout << "�ļ�������" << endl;
            ifs.close();
        }
        else break;
    }
    c.knowledge_address = address;
}

void KnowledgeManager::modify_knowledge(vector<Knowledge>& b, Knowledge& c)
{
    while (true)
    {
        KnowledgeManager::showMenu_modify_knowledge();
        char choice;
        cin >> choice;
        switch (choice)
        {
        case '0'://�˳�
        {
            cout << "�˳��޸�ϵͳ" << endl;
            return;
        }
        case '1'://�޸�����
        {
            KnowledgeManager::modify_knowledge_type(b, c);
            break;
        }
        case '2'://�޸�֪ʶ��
        {
            KnowledgeManager::modify_knowledge_name(b, c);
            break;
        }
        case '3'://ɾ��
        {
            int flag = Knowledge::delete_knowledge(b, c);
            if (flag == 0)
            {
                KnowledgeManager::save_base;
                cout << "�����ɾ�����˳��޸�ϵͳ" << endl;
                string record = " ɾ��֪ʶ:";
                record += TYPE_NAME[c.type] + " ֪ʶ��:" + c.name;
                KnowledgeManager::write_log(c, record);
                return;
            }
            else
                break;
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
void KnowledgeManager::modify_knowledge_type(vector<Knowledge>& b, Knowledge& c)
{
    string type;
    string pre_type = TYPE_NAME[c.type];
    cout << "�������޸ĺ��֪ʶ����" << "\t��֪ʶ���Ͱ��� \"����\", \"���\", \"�η�\", \"��ҽ����\" " << endl;
    while (true)
    {
        cin >> type;
        int type_num = KnowledgeManager::knowledge_type_isExist(type, c);
        if (type_num != -1)
        {
            int i = 0;
            for (; i < b.size(); ++i)
            {
                if (b[i].name == c.name && b[i].type == c.type)break;
            }
            b[i].type = type_num;
            string record = "�޸�֪ʶ���� ԭ֪ʶ����:";
            record += pre_type + " ��֪ʶ����:" + TYPE_NAME[b[i].type];
            KnowledgeManager::write_log(b[i], record);
            break;
        }
        else
        {
            cout << "���ʹ�������������" << endl;
        }
    }
    cout << "�޸ĳɹ�" << endl;
    KnowledgeManager::save_base(b);
}
void KnowledgeManager::modify_knowledge_name(vector<Knowledge>& b, Knowledge& c)
{
    string name;
    string pre_name = c.name;
    cout << "�������޸ĺ�֪ʶ��" << endl;
    cin >> name;
    int i = 0;
    for (; i < b.size(); ++i)
    {
        if (b[i].name == c.name)break;
    }
    b[i].name = name;
    cout << "�޸ĳɹ�" << endl;
    KnowledgeManager::save_base(b);
    string record = "�޸�֪ʶ�� ԭ֪ʶ��:";
    record += pre_name + " ��֪ʶ��:" + b[i].name;
    KnowledgeManager::write_log(b[i], record);
}

void KnowledgeManager::view_knowledge(Knowledge& c)
{
    Knowledge::show_knowledge_info(c);
    Knowledge::show_knowledge_content(c);
}

void KnowledgeManager::show_allknowledge(vector<Knowledge>& b)
{
    sort(b.begin(), b.end(), knowledge_type_cmp);
    cout << "��ǰ֪ʶ��ĿΪ" << b.size() << "��" << ",����֪ʶ��ϢΪ��" << endl;
    for (const auto& i : b)
    {
        Knowledge::show_knowledge_info(i);
    }
    return;
}
void KnowledgeManager::save_base(vector<Knowledge>& b)
{
    sort(b.begin(), b.end(), knowledge_type_cmp);
    ofstream ofs;
    ofs.open(BASE_FILENAME, ios::out);   //�������ʽ���ļ�
    for (int i = 0; i < b.size(); ++i)  //¼��ÿ��֪ʶ����Ϣ 
    {
        ofs << b[i].type << " " << b[i].name << " " << b[i].knowledge_address << endl;
        //��������Ϣ�洢����Ϣ֮���Կո�ָ���֪ʶ��֪ʶ֮���Ի��з��ָ�
    }
    cout << "����ɹ�" << endl;
    ofs.close();//�ر��ļ�
}
void KnowledgeManager::fetch_base(vector<Knowledge>& b)
{
    ifstream ifs;
    ifs.open(BASE_FILENAME, ios::in);//���ļ�
    if (!ifs.is_open())//�ж��Ƿ����
    {
        cout << "�ļ�������" << endl;
        ifs.close();
        return;
    }

    Knowledge temp;
    while (ifs >>  temp.type && ifs >> temp.name && ifs >> temp.knowledge_address)//��Ϣ��ȡ��temp��
    {
        b.push_back(temp);//��temp����b��
    }
    ifs.close();
    if (b.empty())
    {
        cout << "�ļ�Ϊ��" << endl;
    }
}
bool KnowledgeManager::knowledge_type_cmp(const Knowledge& a, const Knowledge& b)
{
    return a.type < b.type;
}
int KnowledgeManager::knowledge_type_isExist(const string type, const Knowledge& b)
{
    for (int i = 0; i < TYPE_NAME.size(); i++)
    {
        if (type == TYPE_NAME[i])
            return i;
    }
    return -1;
}
void KnowledgeManager::search_content_to_knowledge(const string content, vector<Knowledge>& b)
{
    cout << "����������������֮��ص������У�" << endl;
    int flag = 0;

    for (auto& i : b)
    {
        //����֪ʶ��
        int* name_ans;
        name_ans = KMP(content, i.name, 5);
        int flag_name = *(name_ans);
        //����������
        int* type_ans;
        type_ans = KMP(content, TYPE_NAME[i.type], 5);
        int flag_type = *(type_ans);
        if (flag_name != -1 || flag_type != -1)
        {
            flag = 1;
            Knowledge::show_knowledge_info(i);
            Knowledge::show_knowledge_content(i);
        }
        delete name_ans;
        name_ans = NULL;
        delete type_ans;
        type_ans = NULL;
    }
    if (flag == 0)
    {
        cout << "��֪ʶ����û���ҵ���Ӧ����" << endl;
    }
}