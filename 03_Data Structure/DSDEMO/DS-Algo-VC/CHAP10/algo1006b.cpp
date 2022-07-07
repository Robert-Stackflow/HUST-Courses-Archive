int Partition(SqList &L, int low, int high) {  // �㷨10.6(b)
   // ����˳���L��������L.r[low..high]�ļ�¼��ʹ�����¼��λ��
   // ������������λ�ã���ʱ������֮ǰ���󣩵ļ�¼������С������
   KeyType pivotkey;
   L.r[0] = L.r[low];            // ���ӱ�ĵ�һ����¼�������¼
   pivotkey = L.r[low].key;      // �����¼�ؼ���
   while (low<high) {            // �ӱ�����˽�������м�ɨ��
      while (low<high && L.r[high].key>=pivotkey) --high;
      L.r[low] = L.r[high];      // ���������¼С�ļ�¼�Ƶ��Ͷ�
      while (low<high && L.r[low].key<=pivotkey) ++low;
      L.r[high] = L.r[low];      // ���������¼��ļ�¼�Ƶ��߶�
   }
   L.r[low] = L.r[0];            // �����¼��λ
   return low;                   // ��������λ��
} // Partition
