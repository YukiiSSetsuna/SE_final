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

string KnowledgeManager::read_admininfo()
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

void KnowledgeManager::register_admin()
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

void KnowledgeManager::write_log(Knowledge& new_k, string c)
{
    string info_path = "data/admin/log_k.txt";
    ofstream ofs;
    ofs.open(info_path, ios::app);//读文件追加
    if (!ofs.is_open())//判断是否存在
    {
        cout << "文件不存在" << endl;
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
        //展示主菜单
        showMenu_knowledgebase();
        char choice;
        cin >> choice;
        switch (choice)
        {
        case'0'://退出
        {
            cout << "欢迎下次使用" << endl;
            return;
        }
        case'1'://添加知识
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
        case'2'://修改知识
        {
            bool suc = BookManager::admin_Login();
            if (suc)
            {
                cout << "请先检索你所需要修改的知识" << endl;
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
        case'3'://展示所有知识
        {
            if (b.empty())
            {
                cout << "当前知识库为空！" << endl;
                break;
            }
            KnowledgeManager::show_allknowledge(b);
            break;
        }
        case'4'://搜索知识
        {
            Knowledge knowledge;
            knowledge = KnowledgeManager::search_knowledge(b);
            if (knowledge.type != -1)
            {
                KnowledgeManager::view_knowledge(knowledge);//是否要对搜索得到的知识做修改
                cout << "输入\"修改\"以对该知识进行修改,输入其他则返回上级菜单" << endl;
                string str;
                cin >> str;
                if (str == "修改")
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
                //执行修改
                KnowledgeManager::register_admin();
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

void KnowledgeManager::showMenu_knowledgebase()
{
    cout << "************************************" << endl;
    cout << "*****     中医基本知识库系统   *****" << endl;
    cout << "*****     添加知识信息请按1    *****" << endl;
    cout << "*****     修改知识信息请按2    *****" << endl;
    cout << "*****     显示全部知识请按3    *****" << endl;
    cout << "*****     搜索知识请按4        *****" << endl;
    cout << "*****     修改管理员信息请按5    *****" << endl;
    cout << "*****     退出系统请按0        *****" << endl;
    cout << "************************************" << endl;
}
void KnowledgeManager::showMenu_search_knowledge()
{
    cout << "************************************" << endl;
    cout << "*****   请选择你要检索什么知识 *****" << endl;
    cout << "*****   根据类型检索请按1      *****" << endl;
    cout << "*****   根据条目名搜索请按2    *****" << endl;
    cout << "*****   根据关键词搜索请按3    *****" << endl;
    cout << "*****   退出检索系统请按0      *****" << endl;
    cout << "************************************" << endl;
}
void KnowledgeManager::showMenu_modify_knowledge()
{
    cout << "**************************************" << endl;
    cout << "*****   您想要修改该知识什么信息 *****" << endl;
    cout << "*****   修改知识类型请按1        *****" << endl;
    cout << "*****   修改知识名请按2          *****" << endl;
    cout << "*****   删除该知识请按3          *****" << endl;
    cout << "*****   退出修改请按0            *****" << endl;
    cout << "**************************************" << endl;
}


Knowledge KnowledgeManager::search_knowledge(vector<Knowledge>& b)
{
    KnowledgeManager::showMenu_search_knowledge();
    Knowledge temp;
    vector<Knowledge>c;//为防止书籍其他信息重复，将信息重复的查找结果存在c中
    temp.type = 0;
    char choice;
    cin >> choice;
    switch (choice)
    {
    case '1'://根据类型搜索
    {
        KnowledgeManager::search_knowledge_type(b, c);
        break;
    }
    case '2'://根据条目名搜索
    {
        KnowledgeManager::search_knowledge_name(b, c);
        break;
    }
    case '3'://根据关键词搜索
    {
        KnowledgeManager::search_knowledge_keyword(b, c);
        break;
    }
    case '0'://退出
    {
        cout << "欢迎下次使用" << endl;
        temp.type = -1;
        break;
    }
    default:
    {
        cout << "指令错误，请重新输入" << endl;
    }
    }
    if (temp.type != -1)
    {
        if (c.empty())  //没有符合条件的知识
        {
            cout << "没有找到对应知识" << endl;
            temp.type = -1;
        }
        else if (c.size() == 1) //符合条件的只有一条知识
        {
            //KnowledgeManager::view_knowledge(base, c[0]);
            return c[0];
        }
        else        //符合条件的不止一条知识
        {
            cout << "请确认您要查找的知识" << endl;
            int i;
            for (i = 0; i < c.size(); ++i) {
                cout << i + 1 << "、\t";
                Knowledge::show_knowledge_info(c[i]);
            }
            cout << "请选择您要查找的知识序号" << endl;
            cin >> i;
            //KnowledgeManager::view_knowledge(base, c[i-1]);
            return c[i - 1];
        }
    }
    return temp;
}
void KnowledgeManager::search_knowledge_type(vector<Knowledge>& b, vector<Knowledge>& c)
{
    cout << "请输入您要查找的知识类型";
    cout << "，知识类型包括 \"方剂\", \"诊断\", \"治法\", \"中医理论\" " << endl;
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
    cout << "请输入您要查找的知识名" << endl;
    string name;
    cin >> name;
    for (auto& i : b) 
    {
        //查找知识名是否包含关键词，例如查找白米，存在知识名：白米饭
        int* name_ans;
        name_ans = KMP(i.name, name, 5);
        int flag_name = *(name_ans);
        //查找关键词中是否包含知识名，例如查找白米饭，存在知识名：白米
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
    cout << "请输入您要查找的关键词" << endl;
    string keyword;
    cin >> keyword;
    for (auto& i : base)
    {
        //查找知识名
        int* name_ans;
        name_ans = KMP(i.name, keyword, 5);
        int flag_name = *(name_ans);
        //查找知识内容
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
    cout << "添加成功" << endl;
    KnowledgeManager::save_base(base);
    string record = "添加知识 知识类型:";
    record += TYPE_NAME[newknowledge.type] + " 知识名:" + newknowledge.name;
    KnowledgeManager::write_log(newknowledge, record);
}
void KnowledgeManager::add_knowledge_type(vector<Knowledge>& b, Knowledge& c)
{
    string type;
    cout << "请输入知识类型" << "\t，知识类型包括 \"方剂\", \"诊断\", \"治法\", \"中医理论\" " << endl;
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
            cout << "类型错误，请重新输入" << endl;
        }
    }
}
void KnowledgeManager::add_knowledge_name(vector<Knowledge>& b, Knowledge& c)
{
    string name;
    cout << "请输入知识名" << endl;
    cin >> name;
    c.name = name;
}
void KnowledgeManager::add_knowledge_address(vector<Knowledge>& b, Knowledge& c)
{
    string address;
    cout << "请将txt格式的知识放入该软件根目录的'data/knowledge/对应知识类型'的文件夹当中，" << endl;
    cout << "并确保编码格式为ANSI，否则读取中文会出现乱码！" << endl;
    cout << "请输入知识文件名,格式为 ‘知识.txt’ " << endl;
    while (true)
    {
        address = "";
        cin >> address;
        string file_path = "data/knowledge/" + TYPE_NAME[c.type] + "/" + address;
        ifstream ifs;
        ifs.open(file_path, ios::in);//读文件
        if (!ifs.is_open())//判断是否存在
        {
            cout << "文件不存在" << endl;
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
        case '0'://退出
        {
            cout << "退出修改系统" << endl;
            return;
        }
        case '1'://修改类型
        {
            KnowledgeManager::modify_knowledge_type(b, c);
            break;
        }
        case '2'://修改知识名
        {
            KnowledgeManager::modify_knowledge_name(b, c);
            break;
        }
        case '3'://删除
        {
            int flag = Knowledge::delete_knowledge(b, c);
            if (flag == 0)
            {
                KnowledgeManager::save_base;
                cout << "已完成删除，退出修改系统" << endl;
                string record = " 删除知识:";
                record += TYPE_NAME[c.type] + " 知识名:" + c.name;
                KnowledgeManager::write_log(c, record);
                return;
            }
            else
                break;
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
void KnowledgeManager::modify_knowledge_type(vector<Knowledge>& b, Knowledge& c)
{
    string type;
    string pre_type = TYPE_NAME[c.type];
    cout << "请输入修改后的知识类型" << "\t，知识类型包括 \"方剂\", \"诊断\", \"治法\", \"中医理论\" " << endl;
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
            string record = "修改知识类型 原知识类型:";
            record += pre_type + " 现知识类型:" + TYPE_NAME[b[i].type];
            KnowledgeManager::write_log(b[i], record);
            break;
        }
        else
        {
            cout << "类型错误，请重新输入" << endl;
        }
    }
    cout << "修改成功" << endl;
    KnowledgeManager::save_base(b);
}
void KnowledgeManager::modify_knowledge_name(vector<Knowledge>& b, Knowledge& c)
{
    string name;
    string pre_name = c.name;
    cout << "请输入修改后知识名" << endl;
    cin >> name;
    int i = 0;
    for (; i < b.size(); ++i)
    {
        if (b[i].name == c.name)break;
    }
    b[i].name = name;
    cout << "修改成功" << endl;
    KnowledgeManager::save_base(b);
    string record = "修改知识名 原知识名:";
    record += pre_name + " 现知识名:" + b[i].name;
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
    cout << "当前知识数目为" << b.size() << "条" << ",现有知识信息为：" << endl;
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
    ofs.open(BASE_FILENAME, ios::out);   //以输出方式打开文件
    for (int i = 0; i < b.size(); ++i)  //录入每条知识的信息 
    {
        ofs << b[i].type << " " << b[i].name << " " << b[i].knowledge_address << endl;
        //将所有信息存储，信息之间以空格分隔，知识与知识之间以换行符分隔
    }
    cout << "保存成功" << endl;
    ofs.close();//关闭文件
}
void KnowledgeManager::fetch_base(vector<Knowledge>& b)
{
    ifstream ifs;
    ifs.open(BASE_FILENAME, ios::in);//读文件
    if (!ifs.is_open())//判断是否存在
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    Knowledge temp;
    while (ifs >>  temp.type && ifs >> temp.name && ifs >> temp.knowledge_address)//信息读取到temp中
    {
        b.push_back(temp);//将temp存在b中
    }
    ifs.close();
    if (b.empty())
    {
        cout << "文件为空" << endl;
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
    cout << "即将进行搜索，与之相关的内容有：" << endl;
    int flag = 0;

    for (auto& i : b)
    {
        //查找知识名
        int* name_ans;
        name_ans = KMP(content, i.name, 5);
        int flag_name = *(name_ans);
        //查找类型名
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
        cout << "在知识库中没有找到对应内容" << endl;
    }
}