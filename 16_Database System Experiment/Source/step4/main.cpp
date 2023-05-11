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
    for (auto key : keys) {
        rids.clear();
        index_key.SetFromInteger(key);
        tree.GetValue(index_key, &rids);
        EQ(result,(int)rids.size(), 1);

        int64_t value = key & 0xFFFFFFFF;
        EQ(result,(long)rids[0].GetSlotNum(), value);
    }
    if(result == true) cout<< "     GetValue And StartNewTree Pass" << endl;
    else cout<< "       GetValue And StartNewTree Wrong" << endl;

    result = true;
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

    EQ(result,current_key, (long)keys.size() + 1);
    if(result == true) cout<< "     indexIterator Pass" << endl;
    else cout<< "       indexIterator Wrong" << endl;

}
void PopulateNewRootRootTest(BufferPoolManager *bpm,GenericComparator<8> comparator,
                             BPlusTree<GenericKey<8>, RID, GenericComparator<8>>& tree){
    GenericKey<8> index_key;
    RID rid;
    bool result = true;
    //若第一阶段正常，则此时B+树根结点处于要分裂的状态
    setKeyValue(6,index_key,rid);
    tree.Insert(index_key, rid);
    //此时B+树应为
    // | [pageId: 3 parentId: -1]<2> 0(1) 4(2)|
    //| [pageId: 1 parentId: 3]<3> 1(page_id: -1 slot_num: 1) 2(page_id: -1 slot_num: 2) 3(page_id: -1 slot_num: 3)| [pageId: 2 parentId: 3]<3> 4(page_id: -1 slot_num: 4) 5(page_id: -1 slot_num: 5) 6(page_id: -1 slot_num: 6)|

    //测试迭代是否正常
    result = true;
    std::vector<int64_t> keys = {1, 2, 3, 4, 5,6};
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
    EQ(result,current_key, (long)keys.size() + 1);
    if(result == true) cout<< "     indexIterator Pass" << endl;
    else cout<< "       indexIterator Wrong" << endl;

    //测试此时B+树结构是否正确,str表示正确的B+树结构
    std::string str = "| 4| \n| 1 2 3| 4 5 6| ";
    std::string treeStr = tree.ToString(false);
    if(str.compare(treeStr) == 0) cout << "     Split and PopulateNewRoot Pass" << endl;
    else cout << "      Split and PopulateNewRoot Wrong" << endl;
}


void ManyRidsTest(BufferPoolManager *bpm,GenericComparator<8> comparator,
                  BPlusTree<GenericKey<8>, RID, GenericComparator<8>>& tree){
    GenericKey<8> index_key;
    RID rid;
    bool result = true;
    int bSize = 2000;
    //生成多层B+树，判断B+树是否可以正确生成
    std::vector<int64_t> keys;
    for (int key = bSize;key >= 1; key--) {
        keys.push_back(key);
    }
    //随机插入，检测B+树插入功能健壮性
    std::random_shuffle(keys.begin(), keys.end());
    for (int key : keys) {
        setKeyValue(key,index_key,rid);
        tree.Insert(index_key, rid);
    }
    //检测B+树是否仅支持unique key，重复插入相同key值
    for (int key = bSize;key >= 1; key--) {
        setKeyValue(key,index_key,rid);
        tree.Insert(index_key, rid);
    }

    std::vector<RID> rids;
    for (int key = 1;key <= bSize; key++) {
        rids.clear();
        index_key.SetFromInteger(key);
        tree.GetValue(index_key, &rids);
        EQ(result,(int)rids.size(), 1);

        int64_t value = key & 0xFFFFFFFF;
        EQ(result,(long)rids[0].GetSlotNum(), value);
    }
    if(result == true) cout<< "     B+Tree Build Pass" << endl;
    else cout<< "       B+Tree Build Wrong" << endl;

    result = true;
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

    EQ(result,(int)current_key,bSize+1);
    if(result == true) cout<< "     indexIterator Pass" << endl;
    else cout<< "       indexIterator Wrong" << endl;
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

    cout<<"Second Stage Test: Root node is split into two leaf nodes and PopulateNewRoot"<< endl;
    PopulateNewRootRootTest(bpm,comparator,tree);

    cout<<"Third Stage Test: Many Rids are inserted into B+tree"<< endl;
    ManyRidsTest(bpm,comparator,tree);

    
    bpm->UnpinPage(HEADER_PAGE_ID, true);
    delete disk_manager;
    delete bpm;
    remove("test.db");
    remove("test.log");
}