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
/*
 * 函数功能：
 *  根据K值产生叶子结点中的元素(key,rid)
 *  RID表示记录存储的位置：pageID + 插槽号
 */
void setKeyValue(int64_t k, GenericKey<8> &index_key, RID &rid) {
    index_key.SetFromInteger(k);
    int64_t value = k & 0xFFFFFFFF;
    rid.Set((int32_t)(k >> 32), value);
}

//该函数负责对内部节点进行测试
INDEX_TEMPLATE_ARGUMENTS
bool LeafPageTest(BufferPoolManager * bpm,GenericComparator<8> cmp){
    page_id_t leafID;
    Page *newPage = bpm->NewPage(&leafID);
    bool result;
    GenericKey<8> index_key;
    RID rid;
    //生成叶子根结点
    B_PLUS_TREE_LEAF_PAGE_TYPE *leaf1 = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(newPage->GetData());
    leaf1->Init(leafID,INVALID_PAGE_ID,5);

    //对单个叶子节点功能进行测试
    //测试KeyIndex()和Insert()
    result = true;
    index_key.SetFromInteger(3);
    EQ(result,0, leaf1->KeyIndex(index_key, cmp));
    for(int k = 5;k >= 1; k--){
        if(k == 3) continue;
        setKeyValue(k, index_key, rid);
        leaf1->Insert(index_key, rid, cmp);
    }
    EQ(result,4,leaf1->GetSize());
    index_key.SetFromInteger(3);
    EQ(result,2, leaf1->KeyIndex(index_key, cmp));
    setKeyValue(3, index_key, rid);
    leaf1->Insert(index_key, rid, cmp);
    for(int k = 1;k <= 5; k++){
        EQ(result,k&0xFFFFFFFF, leaf1->GetItem(k-1).second.GetSlotNum());
    }
    if(result) cout << "KeyIndex And Insert Pass!" << endl;
    else cout << "KeyIndex And Insert Wrong!" << endl;

    //测试RemoveAndDeleteRecord()
    result = true;
    //记录不存在时返回size大小
    index_key.SetFromInteger(6);
    EQ(result,5,leaf1->RemoveAndDeleteRecord(index_key,cmp));
    //删除key=3后，size以及键值对是否前移
    index_key.SetFromInteger(3);
    EQ(result, 4,leaf1->RemoveAndDeleteRecord(index_key,cmp));
    index_key.SetFromInteger(4);
    EQ(result,0,cmp(leaf1->KeyAt(2),index_key));
    index_key.SetFromInteger(5);
    EQ(result,0,cmp(leaf1->KeyAt(leaf1->GetSize()-1),index_key));
    if(result) cout << "RemoveAndDeleteRecord Pass!" << endl;
    else cout << "RemoveAndDeleteRecord Wrong!" << endl;
    setKeyValue(3,index_key,rid);
    leaf1->Insert(index_key,rid,cmp);


    // 测试Lookup()
    result = true;
    index_key.SetFromInteger(0);
    EQ(result, false,leaf1->Lookup(index_key,&rid,cmp));
    index_key.SetFromInteger(1);
    EQ(result,true,leaf1->Lookup(index_key,&rid,cmp));
    EQ(result,1&0xFFFFFFFF, rid.GetSlotNum());
    //key=7 此时lookup中调用KeyIndex会返回索引，但由于key不存在，应当返回false
    index_key.SetFromInteger(7);
    EQ(result, false,leaf1->Lookup(index_key,&rid,cmp));
    setKeyValue(7,index_key,rid);
    leaf1->Insert(index_key, rid, cmp);
    //key=6,此时lookup中调用KeyIndex会返回key=7的索引,但key=6并不存在，应当返回false
    index_key.SetFromInteger(6);
    EQ(result, false,leaf1->Lookup(index_key,&rid,cmp));
    if(result) cout << "Lookup Pass!" << endl;
    else cout << "Lookup Wrong!" << endl;
    index_key.SetFromInteger(7);
    leaf1->RemoveAndDeleteRecord(index_key,cmp);




    //生成B+树，测试叶子结点其它功能
    newPage = bpm->NewPage(&leafID);
    B_PLUS_TREE_LEAF_PAGE_TYPE *leaf2 = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(newPage->GetData());
    leaf2->Init(leafID,INVALID_PAGE_ID,5);

    // 测试MoveHalfTo()，分裂后leaf1指向的数据:[<1, r1>, <2, r2>]
    // leaf2指向的数据:[<3, r3> , <4, r4>, <5, r5>]
    //[<1, r1>, <2, r2>] --> [<3, r3> , <4, r4>, <5, r5>]
    result = true;
    //假设leaf1原相邻结点的PageId为20
    page_id_t endPageId = 20;
    leaf1->SetNextPageId(endPageId);
    leaf1->MoveHalfTo(leaf2, bpm);
    //数量是否正确
    EQ(result, leaf1->GetSize(),2);
    EQ(result, leaf2->GetSize(),3);
    //相邻节点更新是否正确
    EQ(result,leaf1->GetNextPageId(),leaf2->GetPageId());
    EQ(result,leaf2->GetNextPageId(),endPageId);
    index_key.SetFromInteger(3);
    EQ(result,0, cmp(index_key,leaf2->KeyAt(0)));
    if(result) cout << "MoveHalfTo Pass!" << endl;
    else cout << "MoveHalfTo Wrong!" << endl;

    // 生成2层B+树，结构为：
    //          [<1, leaf1>, <3, leaf2>]
    //[<1, r1>, <2, r2>]  [<3, r3> , <4, r4>, <5, r5>]
    page_id_t proot;
    B_PLUS_TREE_INTERNAL_PAGE *pageRoot = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>((bpm->NewPage(&proot))->GetData());
    pageRoot->Init(proot,INVALID_PAGE_ID,5);
    index_key.SetFromInteger(3);
    pageRoot->PopulateNewRoot(leaf1->GetPageId(),index_key,leaf2->GetPageId());
    leaf1->SetParentPageId(proot);
    leaf2->SetParentPageId(proot);

    //测试MoveFirstToEndOf
    //此时结构为：
    //          [<1, leaf1>, <4, leaf2>]
    //[<1, r1>, <2, r2>, <3, r3>] , [<4, r4>, <5, r5>]
    result = true;
    leaf2->MoveFirstToEndOf(leaf1,bpm);
    index_key.SetFromInteger(4);
    EQ(result, 0,cmp(index_key,pageRoot->KeyAt(1)));
    EQ(result, 2,leaf2->GetSize());
    EQ(result, 3,leaf1->GetSize());
    EQ(result,0,cmp(leaf2->KeyAt(0),index_key));
    index_key.SetFromInteger(3);
    EQ(result,0,cmp(leaf1->KeyAt(leaf1->GetSize()-1),index_key));
    if(result) cout << "MoveFirstToEndOf Pass!" << endl;
    else cout << "MoveFirstToEndOf Wrong!" << endl;

    //测试MoveLastToFrontOf
    //此时结构为：
    //          [<1, leaf1>, <3, leaf2>]
    //[<1, r1>, <2, r2>] [<3, r3>, <4, r4>, <5, r5>]
    result = true;
    leaf1->MoveLastToFrontOf(leaf2,bpm);
    index_key.SetFromInteger(3);
    EQ(result, 0,cmp(index_key,pageRoot->KeyAt(1)));
    EQ(result, 2,leaf1->GetSize());
    EQ(result, 3,leaf2->GetSize());
    EQ(result,0,cmp(leaf2->KeyAt(0),index_key));
    index_key.SetFromInteger(2);
    EQ(result,0,cmp(leaf1->KeyAt(leaf1->GetSize()-1),index_key));
    if(result) cout << "MoveLastToFrontOf Pass!" << endl;
    else cout << "MoveLastToFrontOf Wrong!" << endl;

    //测试MoveAllTo
    //此时结构为：
    //[<1, r1>, <2, r2>, <3, r3>, <4, r4>, <5, r5>]
    result = true;
    leaf2->MoveAllTo(leaf1,bpm);
    EQ(result, endPageId,leaf1->GetNextPageId());
    EQ(result, 5,leaf1->GetSize());
    index_key.SetFromInteger(5);
    EQ(result, 0,cmp(leaf1->KeyAt(leaf1->GetSize()-1),index_key));
    if(result) cout << "MoveAllTo Pass!" << endl;
    else cout << "MoveAllTo Wrong!" << endl;

    bpm->UnpinPage(leaf1->GetPageId(), true);
    bpm->UnpinPage(leaf2->GetPageId(), true);
    bpm->UnpinPage(pageRoot->GetPageId(), true);
}

int main() {
    auto key_schema = ParseCreateStatement("a bigint");
    GenericComparator<8> comparator(key_schema.get());
    DiskManager *disk_manager = new DiskManager("test.db");
    BufferPoolManager *bpm = new BufferPoolManagerInstance(50, disk_manager);
    LeafPageTest<GenericKey<8>, RID, GenericComparator<8>>(bpm,comparator);
    delete disk_manager;
    delete bpm;
    remove("test.db");
}