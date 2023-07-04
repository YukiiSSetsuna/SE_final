#include <vector>
#include "KnowledgeManager.h"
#include "BookManager.h"
#include "Global_Function.h"

using namespace std;
int main()
{
    vector<Book>library;//�����µ�library
    BookManager book_manager;
    book_manager.library = library;
    BookManager::fetch_library(book_manager.library);//��ȡlibrary.txt

    vector<Knowledge>base;//�����µ�base
    KnowledgeManager knowledge_base;
    knowledge_base.base = base;
    KnowledgeManager::fetch_base(knowledge_base.base);//��ȡKnowledgeBase.txt

    
    select_mainmenu(book_manager.library, knowledge_base.base);//�������˵�
    return 0;
}