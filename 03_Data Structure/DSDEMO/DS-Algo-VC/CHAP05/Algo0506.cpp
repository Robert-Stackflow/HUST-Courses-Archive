Status CopyGList(GList &T, GList L) {  // �㷨5.6
  // ����ͷβ����洢�ṹ,�ɹ����L���Ƶõ������T��
  if (!L) T = NULL;  // ���ƿձ�
  else {
    if (!(T = (GList)malloc(sizeof(GLNode)))) // ������
      return ERROR; 
    T->tag = L->tag;
    if (L->tag == ATOM) T->atom = L->atom;  // ���Ƶ�ԭ��
    else { 
      CopyGList(T->ptr.hp, L->ptr.hp);
            // ���ƹ����T->ptr.hp�ĸ���L->ptr.hp
      CopyGList(T->ptr.tp, L->ptr.tp);
            // ���ƹ����T->ptr.tp�ĸ���L->ptr.tp
    } // else
  } // else
  return OK;
} // CopyGList
