Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p) {  
  // �㷨9.5(b)
  // �ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ�
  // �����ҳɹ�����ָ��pָ�������Ԫ�ؽ�㣬������TRUE��
  // ����ָ��pָ�����·���Ϸ��ʵ����һ����㲢����FALSE��
  // ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
  if (!T) { p = f;  return FALSE; }                     // ���Ҳ��ɹ�
  else if (EQ(key, T->data.key)) { p = T;  return TRUE; } // ���ҳɹ�
  else if (LT(key, T->data.key)) 
    return SearchBST(T->lchild, key, T, p);  // ���������м�������
  else  
    return SearchBST(T->rchild, key, T, p);  // ���������м�������
} // SearchBST
