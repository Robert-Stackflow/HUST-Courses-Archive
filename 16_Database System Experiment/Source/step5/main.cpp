#include <cstdio>
#include <random>
#include <string>
#include "storage/index/b_plus_tree.h"
#include "buffer/buffer_pool_manager_instance.h"
#include "test_util.h"
#include <algorithm>

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
    rid.Set(-1, value);
}
/*
 * 测试样例1：
 *  测试插入数据的第一阶段————B+树当前仅包含根结点，且根结点为叶子结点，深度为1
 */
void OnlyRootTest(BufferPoolManager *bpm,GenericComparator<8> comparator,
                  BPlusTree<GenericKey<8>, RID, GenericComparator<8>>& tree){
    GenericKey<8> index_key;
    RID rid;
    bool result = true;


    std::vector<int64_t> keys = {1, 2, 3, 4, 5};
    for (auto key : keys) {
        setKeyValue(key,index_key,rid);
        tree.Insert(index_key, rid);
    }

    std::vector<RID> rids;
    keys = {1, 2, 4, 5};
    for (auto key : keys) {
        index_key.SetFromInteger(key);
        tree.Remove(index_key);
    }
    //重复删除无效
    for (auto key : keys) {
        index_key.SetFromInteger(key);
        tree.Remove(index_key);
    }

    int64_t start_key = 3;
    int64_t current_key = start_key;
    index_key.SetFromInteger(start_key);
    for (auto iterator = tree.Begin(index_key); iterator.IsEnd() == false;
         ++iterator) {
        auto location = (*iterator).second;
        EQ(result,location.GetPageId(), -1);
        EQ(result,(long)location.GetSlotNum(), current_key);
        current_key = current_key + 1;
    }
    EQ(result,(int)current_key,4);
    if(result == true) cout<< "Remove A Key Pass" << endl;
    else cout<< "Remove a Key" << endl;

    result = true;

    keys = {3};
    for (auto key : keys) {
        index_key.SetFromInteger(key);
        tree.Remove(index_key);
    }
    //空树时删除无效
    for (auto key : keys) {
        index_key.SetFromInteger(key);
        tree.Remove(index_key);
    }

    if(tree.IsEmpty()) cout<< "     Remove All Key Pass" << endl;
    else cout<< "       Remove All Key Wrong" << endl;

}
void UpdateNewRootRootTest(BufferPoolManager *bpm,GenericComparator<8> comparator,
                             BPlusTree<GenericKey<8>, RID, GenericComparator<8>>& tree){
    GenericKey<8> index_key;
    RID rid;
    bool result = true;
    std::vector<int64_t> keys = {1, 2, 3, 4, 5, 6};
    for (auto key : keys) {
        setKeyValue(key,index_key,rid);
        tree.Insert(index_key, rid);
    }
    //此时B+树应为
    // | [pageId: 3 parentId: -1]<2> 0(1) 4(2)|
    //| [pageId: 1 parentId: 3]<3> 1 2 3| [pageId: 2 parentId: 3]<3> 4 5 6
    tree.Remove(index_key);
    //此时B+树应为| 1 2 3 4 5|
    int64_t start_key = 1;
    int64_t current_key = start_key;
    index_key.SetFromInteger(start_key);
    for (auto iterator = tree.Begin(index_key); iterator.IsEnd() == false;
         ++iterator) {
        auto location = (*iterator).second;
        EQ(result,location.GetPageId(), -1);
        EQ(result,(long)location.GetSlotNum(), current_key);
        current_key = current_key + 1;
    }
    EQ(result,current_key, (long)6);

    //测试此时B+树结构是否正确,str表示正确的B+树结构
    std::string str = "| 1 2 3 4 5| ";
    std::string treeStr = tree.ToString(false);
    if(str.compare(treeStr) == 0) cout << "     Leaf node coalesce and UpdateNewRoot Pass" << endl;
    else cout << "      Leaf node coalesce and UpdateNewRoot Wrong" << endl;

    //删除剩余元素，生成空树
    result = true;
    keys = {3,4,2,5,1};
    for (auto key : keys) {
        index_key.SetFromInteger(key);
        tree.Remove(index_key);
    }

    if(tree.IsEmpty()) cout<< "     Remove All Key Pass" << endl;
    else cout<< "       Remove All Key Wrong" << endl;
}


void ManyRidsTest(BufferPoolManager *bpm,GenericComparator<8> comparator,
                  BPlusTree<GenericKey<8>, RID, GenericComparator<8>>& tree){
    GenericKey<8> index_key;
    RID rid;
    bool result = true;
    std::vector<int64_t> keys;
    for (int key = 5;key >= 1; key--) {
        keys.push_back(key);
    }
    for(int key : keys){
        setKeyValue(key,index_key,rid);
        tree.Insert(index_key, rid);
    }
    std::random_shuffle(keys.begin(), keys.end());

    std::vector<RID> rids;
    for(int index =0;index < keys.size(); index++){
        int key = keys[index];
        index_key.SetFromInteger(key);
        tree.Remove(index_key);
        //删除后现存数据仍正确
        for (int i = index + 1; i < keys.size(); i++) {
            int k = keys[i];
            rids.clear();
            index_key.SetFromInteger(k);
            tree.GetValue(index_key, &rids);
            EQ(result,(int)rids.size(), 1);
            int64_t value = k & 0xFFFFFFFF;
            EQ(result,(long)rids[0].GetSlotNum(), value);
        }
        int64_t current_key = 0;
        //删除后叶子结点间保持连续性
        for (auto iterator = tree.Begin(); iterator.IsEnd() == false;
             ++iterator) {
            current_key = current_key + 1;
            auto location = (*iterator).second;
            EQ(result,location.GetPageId(), -1);
        }
        EQ(result,current_key,(long)keys.size()-index-1);
    }
    EQ(result,tree.IsEmpty(), true);
    if(result == true) cout<< "     Remove Many Rids Pass" << endl;
    else cout<< "       Remove Many Rids Wrong" << endl;
}

int main() {
    auto key_schema = ParseCreateStatement("a bigint");
    GenericComparator<8> comparator(key_schema.get());
    DiskManager *disk_manager = new DiskManager("test.db");
    BufferPoolManager *bpm = new BufferPoolManagerInstance(5000, disk_manager);
    BPlusTree<GenericKey<8>, RID, GenericComparator<8>> tree("tree", bpm,
                                                             comparator,5,5);
    page_id_t page_id;
    auto header_page = bpm->NewPage(&page_id);
    (void)header_page;

    cout<<"First Stage Test: Only root nodes as leaf nodes in B+tree"<< endl;
    OnlyRootTest(bpm,comparator,tree);

    cout<<"Second Stage Test: Two leaf node coalesce and UpdateNewRoot"<< endl;
    UpdateNewRootRootTest(bpm,comparator,tree);

    cout<<"Third Stage Test: Many Rids are deleted"<< endl;
    ManyRidsTest(bpm,comparator,tree);



    bpm->UnpinPage(HEADER_PAGE_ID, true);
    delete disk_manager;
    delete bpm;
    remove("test.db");
    remove("test.log");
}