#ifndef INC_3_2_KNOWLEDGE_H
#define INC_3_2_KNOWLEDGE_H

#include <string>
#include <vector>
using namespace std;

const vector<string>TYPE_NAME = {"方剂", "诊断", "治法", "中医理论"};

class Knowledge
{
	public:
		Knowledge();
		~Knowledge();
		string name;
		int type;
		//string knowledge_content;
		string knowledge_address;

		static void show_knowledge_info(Knowledge knowledge);
		static void show_knowledge_content(Knowledge knowledge);
		static string get_knowledge_content(Knowledge knowledge);
		static int delete_knowledge(vector<Knowledge>& b, Knowledge knowledge);
};


#endif //INC_3_2_KNOWLEDGE_H