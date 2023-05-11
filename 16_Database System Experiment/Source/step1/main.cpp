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

//�������ֵ�ȽϽ��
template <class T> bool EQ(bool& result,const T& a,const T& b){
    bool now = (a==b);
    result = result && now;
    cout << boolalpha << now << endl;
}
//����rid
void setKeyValue(int64_t k, GenericKey<8> &index_key, RID &rid) {
    index_key.SetFromInteger(k);
    int64_t value = k & 0xFFFFFFFF;
    rid.Set((int32_t)(k >> 32), value);
}
//B+��ҳ���ͨ�ú������ܲ���
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

int main() {
    auto key_schema = ParseCreateStatement("a bigint");
    GenericComparator<8> comparator(key_schema.get());
    DiskManager *disk_manager = new DiskManager("test.db");
    BufferPoolManager *bpm = new BufferPoolManagerInstance(50, disk_manager);
    //5��B+�����ڲ���������
    page_id_t PageId;
    Page *Page = bpm->NewPage(&PageId);
    //创建B+内部页，父页IDGetParentPageId，根节点，最大元素为5，页号为PageId
    BPlusTreeInternalPage<GenericKey<8>, page_id_t, GenericComparator<8>> *internal = reinterpret_cast<BPlusTreeInternalPage<GenericKey<8>, page_id_t, GenericComparator<8>> *>(Page->GetData());
    internal->Init(PageId,INVALID_PAGE_ID,5);
    //if(internal->IsLeafPage() == false)
    //    cout << "False Leaf Page Judge Pass" << endl;
    //else
    //    cout << "False Leaf Page Judge Wrong" << endl;
    if(BplusTreePageTest(internal,PageId))
        cout << "内部页(根节点，内部结点，最大元素为5，页号为PageId)测试通过" << endl;
    else
        cout << "内部页(根节点，内部结点，最大元素为5，页号为PageId)测试失败" << endl;

    //5��B+����Ҷ�Ӹ�������
    Page = bpm->NewPage(&PageId);
    BPlusTreeLeafPage<GenericKey<8>, RID, GenericComparator<8>> *leaf = reinterpret_cast<BPlusTreeLeafPage<GenericKey<8>, RID, GenericComparator<8>> *>(Page->GetData());
    leaf->Init(PageId,INVALID_PAGE_ID,5);
    //if(leaf->IsLeafPage() == true)
    //    cout << "TypeJudge Pass" << endl;
    //else
    //    cout << "TypeJudge Wrong" << endl;
    if(BplusTreePageTest(leaf,PageId))
        cout << "页结点(根节点，页结点，最大元素为5，页号为PageId)测试通过" << endl;
    else
        cout << "页结点(根节点，页结点，最大元素为5，页号为PageId)测试通过" << endl;
    delete disk_manager;
    delete bpm;
    remove("test.db");
}