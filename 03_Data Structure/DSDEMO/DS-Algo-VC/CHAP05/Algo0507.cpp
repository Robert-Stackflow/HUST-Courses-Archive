Status CreateGList(GList &L, SString S) {  // �㷨5.7
  // ����ͷβ����洢�ṹ���ɹ�������д��ʽ��S���������L��
  // ��emp="()"��
  char s[3]="()";
  SString emp;
  crt_SString(emp,s);
  SString sub,hsub;
  GList p,q;
  if (StrCompare(S, emp)) L = NULL;  // �����ձ�
  else {
    if (!(L=(GList)malloc(sizeof(GLNode)))) return ERROR;  // ������
    if (StrLength(S)==1) {  // ������ԭ�ӹ����
       L->tag = ATOM;  L->atom =S[1]; }  
    } else { 
      L->tag = LIST;  p = L;  
      SubString(sub, S, 2, StrLength(S)-2);  // ��������� 
      do {  // �ظ���n���ӱ�
        sever(sub, hsub);  // ��sub�з������ͷ�� hsub
        CreateGList(p->ptr.hp, hsub);  q = p;
        if (!StrEmpty(sub)) {   // ��β���� 
          if (!(p = (GLNode *) malloc (sizeof(GLNode)))) return ERROR;  
          p->tag = LIST;  q->ptr.tp = p;  
        }//if
      } while (!StrEmpty(sub));
      q->ptr.tp = NULL;
    } // else
  } // else
  return OK;
} // CreateGList
