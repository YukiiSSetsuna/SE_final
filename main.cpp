#include <vector>
#include "KnowledgeManager.h"
#include "BookManager.h"
#include "Global_Function.h"

using namespace std;
int main()
{
    vector<Book>library;//创建新的library
    BookManager book_manager;
    book_manager.library = library;
    BookManager::fetch_library(book_manager.library);//读取library.txt

    vector<Knowledge>base;//创建新的base
    KnowledgeManager knowledge_base;
    knowledge_base.base = base;
    KnowledgeManager::fetch_base(knowledge_base.base);//读取KnowledgeBase.txt

    
    select_mainmenu(book_manager.library, knowledge_base.base);//进入主菜单
    return 0;
}