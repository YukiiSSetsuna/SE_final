#ifndef INC_3_2_KNOWLEDGEBASE_H
#define INC_3_2_KNOWLEDGEBASE_H

#include "Knowledge.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
constexpr auto BASE_FILENAME = "data/knowledge/KnowledgeBase.txt";

using namespace std;

class KnowledgeManager 
{
	public:
		KnowledgeManager();
		KnowledgeManager(vector<Knowledge> base);
		~KnowledgeManager();
		vector<Knowledge> base;

		static void select_base_mainmenu(vector<Knowledge>& b);

		static bool admin_Login();
		static string read_admininfo();
		static void register_admin();
		static void write_log(Knowledge& new_k, string c);

		static void showMenu_knowledgebase();
		static void showMenu_search_knowledge();
		static void showMenu_modify_knowledge();

		static Knowledge search_knowledge(vector<Knowledge>& b);
		static void search_knowledge_type(vector<Knowledge>& b, vector<Knowledge>& c);
		static void search_knowledge_name(vector<Knowledge>& b, vector<Knowledge>& c);
		static void search_knowledge_keyword(vector<Knowledge>& b, vector<Knowledge>& c);

		static void add_knowledge(vector<Knowledge>& b);
		static void add_knowledge_type(vector<Knowledge>& b, Knowledge& c);
		static void add_knowledge_name(vector<Knowledge>& b, Knowledge& c);
		static void add_knowledge_address(vector<Knowledge>& b, Knowledge& c);

		static void modify_knowledge(vector<Knowledge>& b, Knowledge& c);
		static void modify_knowledge_type(vector<Knowledge>& b, Knowledge& c);
		static void modify_knowledge_name(vector<Knowledge>& b, Knowledge& c);

		static void view_knowledge(Knowledge& c);

		static void show_allknowledge(vector<Knowledge>& b);
		static void save_base(vector<Knowledge>& b);
		static void fetch_base(vector<Knowledge>& b);
		static bool knowledge_type_cmp(const Knowledge& a, const Knowledge& b);
		static int knowledge_type_isExist(const string type, const Knowledge& b);
		static void search_content_to_knowledge(const string content, vector<Knowledge>& b);

};

#endif //INC_3_2_KNOWLEDGEBASE_H