#include <cstdio>
#include <random>
#include <string>
#include "storage/page/b_plus_tree_page.h"
#include "storage/page/b_plus_tree_internal_page.h"
#include "storage/page/b_plus_tree_leaf_page.h"
#include "buffer/buffer_pool_manager_instance.h"
#include "test_util.h"

using namespace bustub;
using namespace std;
bool output = false;
//输出布尔值比较结果
template <class T> void EQ(bool& result,const T& a,const T& b){
    bool now = (a==b);
    result = result && now;
    if(output) {
        cout << boolalpha << now << endl;
    }
}
//产生rid
void setKeyValue(int64_t k, GenericKey<8> &index_key, RID &rid) {
    index_key.SetFromInteger(k);
    int64_t value = k & 0xFFFFFFFF;
    rid.Set((int32_t)(k >> 32), value);
}
//B+树页结点通用函数功能测试
bool BplusTreePageTest(BPlusTreePage* page,page_id_t page_id){
    if(page->IsLeafPage()){
        if(!(page->GetMinSize() == 1)) return false;
    } else{
        if(!(page->GetMinSize() == 2)) return false;
    }
    if(!(page->GetMaxSize() == 5)) return false;
    if(!(page->IsRootPage() == true)) return false;
    if(!(page->GetParentPageId() == INVALID_PAGE_ID)) return false;
    if(!(page->GetPageId() == page_id)) return false;
    return true;
}

//该函数负责对内部节点进行测试
INDEX_TEMPLATE_ARGUMENTS
bool InternalPageTest(BufferPoolManager * bpm,GenericComparator<8> cmp){
    page_id_t rootPageId;
    Page *newPage = bpm->NewPage(&rootPageId);
    bool result = true;
    B_PLUS_TREE_INTERNAL_PAGE *root = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(newPage->GetData());
    root->Init(rootPageId,INVALID_PAGE_ID,5);
    EQ(result,root->IsLeafPage(),false);
    if(result) cout << "Init Pass!" << endl;
    else cout << "Init Wrong!" << endl;

    //初始化
    page_id_t p[5];
    B_PLUS_TREE_INTERNAL_PAGE * page[5];
    for(int i = 0;i < 5;i++){
        page[i] = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(bpm->NewPage(&(p[i]))->GetData());
        page[i]->Init(p[i],rootPageId,5);
    }

    GenericKey<8> index_key;
    index_key.SetFromInteger(1);
    //测试内部根结点的初始化功能
    root->PopulateNewRoot(p[0],index_key,p[1]);
    result = true;
    EQ(result, 2,root->GetSize());
    EQ(result, p[0],root->ValueAt(0));
    EQ(result, p[1],root->ValueAt(1));
    if(result) cout << "PopulateNewRoot Pass!" << endl;
    else cout << "PopulateNewRoot Wrong!" << endl;

    // 当前数据:[<invalid, p[0]>, <1, p[1]>]
    index_key.SetFromInteger(3);
    root->InsertNodeAfter(p[1], index_key, p[3]);
    // 当前数据:[<invalid, p[0]>, <1, p[1]>, <3, p[3]>]
    index_key.SetFromInteger(2);
    // 当前数据:[<invalid, p[0]>, <1, p[1]>, <2, p[2]>, <3, p[3]>]
    root->InsertNodeAfter(p[1], index_key, p[2]);
    result = true;
    EQ(result, 4,root->GetSize());
    EQ(result, p[0],root->ValueAt(0));
    EQ(result, p[1],root->ValueAt(1));
    EQ(result, p[2],root->ValueAt(2));
    EQ(result, p[3],root->ValueAt(3));
    if(result) cout << "InsertNodeAfter Pass!" << endl;
    else cout << "InsertNodeAfter Wrong!" << endl;

    // 测试Lookup()
    result = true;
    index_key.SetFromInteger(0);
    EQ(result, p[0],root->Lookup(index_key, cmp));
    index_key.SetFromInteger(1);
    EQ(result, p[1],root->Lookup(index_key, cmp));
    index_key.SetFromInteger(4);
    EQ(result, p[3],root->Lookup(index_key, cmp));
    index_key.SetFromInteger(4);
    root->InsertNodeAfter(p[3], index_key, p[4]);
    if(result) cout << "Lookup Pass!" << endl;
    else cout << "Lookup Wrong!" << endl;

    page_id_t new_page_id;
    Page *new_page = bpm->NewPage(&new_page_id);
    B_PLUS_TREE_INTERNAL_PAGE *new_root = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(new_page->GetData());
    new_root->Init(new_page_id,INVALID_PAGE_ID,5);

    // 测试MoveHalfTo()，分裂后root指向的数据:[<invalid, p[0]>, <1, p[1]>]
    // new_root指向的数据:[<2, p[2]> , <3, p[3]>, <4, p[4]>]
    result = true;
    root->MoveHalfTo(new_root, bpm);
    //数量是否正确
    EQ(result, root->GetSize(),2);
    EQ(result, new_root->GetSize(),3);
    //父节点更新是否正确
    EQ(result, new_root->GetPageId(),page[2]->GetParentPageId());
    EQ(result, new_root->GetPageId(),page[3]->GetParentPageId());
    EQ(result, new_root->GetPageId(),page[4]->GetParentPageId());
    index_key.SetFromInteger(2);
    EQ(result, 0,cmp(index_key,new_root->KeyAt(0)));
    if(result) cout << "MoveHalfTo Pass!" << endl;
    else cout << "MoveHalfTo Wrong!" << endl;

    // 生成3层B+树，结构为：
    //          [<invalid, proot>, <2, new_page_id>]
    //[<invalid, p[0]>, <1, p[1]>]  [<2, p[2]> , <3, p[3]>, <4, p[4]>]
    page_id_t proot;
    B_PLUS_TREE_INTERNAL_PAGE *pageRoot = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>((bpm->NewPage(&proot))->GetData());
    pageRoot->Init(proot,INVALID_PAGE_ID,5);
    pageRoot->PopulateNewRoot(rootPageId,index_key,new_page_id);
    root->SetParentPageId(proot);
    new_root->SetParentPageId(proot);

    //测试MoveFirstToEndOf
    //此时结构为：
    //          [<invalid, proot>, <3, new_page_id>]
    //[<invalid, p[0]>, <1, p[1]>, <2, p[2]> ]  [<3, p[3]>, <4, p[4]>]
    result = true;
    new_root->MoveFirstToEndOf(root,bpm);
    index_key.SetFromInteger(3);
    EQ(result, 0,cmp(index_key,pageRoot->KeyAt(1)));
    EQ(result, root->GetPageId(),page[2]->GetParentPageId());
    EQ(result, 2,new_root->GetSize());
    EQ(result, 3,root->GetSize());
    EQ(result, p[2],root->ValueAt(root->GetSize()-1));
    EQ(result, p[3],new_root->ValueAt(0));
    if(result) cout << "MoveFirstToEndOf Pass!" << endl;
    else cout << "MoveFirstToEndOf Wrong!" << endl;

    //测试MoveLastToFrontOf
    //此时结构为：
    //          [<invalid, proot>, <2, new_page_id>]
    //[<invalid, p[0]>, <1, p[1]>]  [<2, p[2]> ,<3, p[3]>, <4, p[4]>]
    result = true;
    root->MoveLastToFrontOf(new_root,bpm);
    index_key.SetFromInteger(2);
    EQ(result, 0,cmp(index_key,pageRoot->KeyAt(1)));
    EQ(result, new_root->GetPageId(),page[2]->GetParentPageId());
    EQ(result, 3,new_root->GetSize());
    EQ(result, 2,root->GetSize());
    EQ(result, p[1],root->ValueAt(root->GetSize()-1));
    EQ(result, p[2],new_root->ValueAt(0));
    if(result) cout << "MoveLastToFrontOf Pass!" << endl;
    else cout << "MoveLastToFrontOf Wrong!" << endl;

    //测试MoveAllto
    //此时结构为：
    //          [<invalid, proot>, <3, new_page_id>]
    //[<invalid, p[0]>, <1, p[1]>, <2, p[2]>,<3, p[3]>, <4, p[4]>]
    result = true;
    new_root->MoveAllTo(root,bpm);
    EQ(result, 5,root->GetSize());
    EQ(result, p[4],root->ValueAt(root->GetSize()-1));
    EQ(result, root->GetPageId(),page[4]->GetParentPageId());
    if(result) cout << "MoveAllTo Pass!" << endl;
    else cout << "MoveAllTo Wrong!" << endl;

    // 测试Remove()，删除后root指向的数据:[<invalid, p[0]>,<2, p[2]>,<3, p[3]>, <4, p[4]>]
    result = true;
    root->Remove(1);
    EQ(result, 4,root->GetSize());
    index_key.SetFromInteger(2);
    EQ(result, p[2], root->ValueAt(1));
    if(result) cout << "Remove Pass!" << endl;
    else cout << "Remove Wrong!" << endl;

    bpm->UnpinPage(new_root->GetPageId(), true);
    bpm->UnpinPage(root->GetPageId(), true);
    bpm->UnpinPage(pageRoot->GetPageId(), true);
    bpm->UnpinPage(p[0], true);
    bpm->UnpinPage(p[1], true);
    bpm->UnpinPage(p[2], true);
    bpm->UnpinPage(p[3], true);
    bpm->UnpinPage(p[4], true);
}

//INDEX_TEMPLATE_ARGUMENTS
//bool LeafPageTest(BufferPoolManager * bpm){
//    page_id_t newPageId;
//    Page *newPage = bpm->NewPage(&newPageId);
//    B_PLUS_TREE_LEAF_PAGE_TYPE *newNode = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(newPage->GetData());
//    newNode->Init(newPageId,INVALID_PAGE_ID,5);
//    //5阶B+树的内部根结点测试
//    //首先测试页的基本功能
//    if(!(newNode->IsLeafPage() == true)) return false;
//    if(!BplusTreePageTest(newNode,newPageId)) return false;
//
//
//    //测试叶子页中结点的移动功能
//    newPage = bpm->NewPage(&newPageId);
//    B_PLUS_TREE_INTERNAL_PAGE *recrootient = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(newPage->GetData());
//    recrootient->Init(newPageId,INVALID_PAGE_ID,5);
//}

int main() {
    auto key_schema = ParseCreateStatement("a bigint");
    GenericComparator<8> comparator(key_schema.get());
    DiskManager *disk_manager = new DiskManager("test.db");
    BufferPoolManager *bpm = new BufferPoolManagerInstance(50, disk_manager);
    InternalPageTest<GenericKey<8>, page_id_t, GenericComparator<8>>(bpm,comparator);
    delete disk_manager;
    delete bpm;
    remove("test.db");
}