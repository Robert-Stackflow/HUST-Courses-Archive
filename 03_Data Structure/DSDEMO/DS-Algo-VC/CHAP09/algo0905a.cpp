BiTree SearchBST (BiTree T, KeyType key) {  // �㷨9.5(a)
   // �ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ�
   // �����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ�룬���򷵻ؿ�ָ��
   if (!T || EQ(key, T->data.key)) return T;  // ���ҽ���
   else if (LT(key, T->data.key)) 
      return SearchBST(T->lchild, key);  // ���������м������� 
   else 
      return SearchBST(T->rchild, key);  // ���������м�������
} // SearchBST
