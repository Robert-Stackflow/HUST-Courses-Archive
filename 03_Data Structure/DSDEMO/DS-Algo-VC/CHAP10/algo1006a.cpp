int Partition(SqList &L, int low, int high) {  // �㷨10.6(a)
   // ����˳���L��������L.r[low..high]�ļ�¼��ʹ�����¼��λ��
   // ������������λ�ã���ʱ������֮ǰ���󣩵ļ�¼������С������
   KeyType pivotkey;
   RedType temp;
   pivotkey = L.r[low].key;     // ���ӱ�ĵ�һ����¼�������¼
   while (low<high) {           // �ӱ�����˽�������м�ɨ��
      while (low<high && L.r[high].key>=pivotkey) --high;
      temp=L.r[low];
      L.r[low]=L.r[high];
      L.r[high]=temp;           // ���������¼С�ļ�¼�������Ͷ�
      while (low<high && L.r[low].key<=pivotkey) ++low;
      temp=L.r[low];
      L.r[low]=L.r[high];
      L.r[high]=temp;           // ���������¼��ļ�¼�������߶�
   }
   return low;                  // ������������λ��
} // Partition
