Status CreateSMatrix_OL (CrossList &M) { // �㷨5.4
  // ����ϡ�����M������ʮ������洢��ʾ��
  // if (M) free(M);
  // scanf(&m, &n, &t );    // ����M�������������ͷ���Ԫ����
  OLNode *p,*q;
  int i,j,e;
  int m=random(4,6), n=random(4,6), t=random(4,5);
  M.mu=m;  M.nu=n;  M.tu=t; 
  if (!(M.rhead = (OLink *)malloc((m+1)*sizeof(OLink)))) return ERROR;
  if (!(M.chead = (OLink *)malloc((n+1)*sizeof(OLink)))) return ERROR;
  for(int a=1;a<=m;a++)  // ��ʼ������ͷָ������������������Ϊ������
     M.rhead[a]=NULL;
  for(int b=1;b<=n;b++) M.chead[b]=NULL;
  for ( int c=1; c<=t; c++) { // ����������������Ԫ
    scanf(&i,&j,&e);
    if (!(p = (OLNode *)malloc(sizeof(OLNode)))) return ERROR;
    p->i=i;  p->j=j;  p->e=e;  p->down=NULL;  p->right=NULL; // �½��
    if (M.rhead[i] == NULL || M.rhead[i]->j > j) {
      p->right = M.rhead[i];   M.rhead[i]= p;  
    } else {  // Ѱ�����б��еĲ���λ��
      for (q=M.rhead[i]; (q->right) && (q->right->j<j);  q=q->right);
      p->right = q->right;  q ->right = p;     
    }  // ����в���
    if (M.chead[j] == NULL || M.chead[j]->i > i) {
      p->down = M.chead[j];   M.chead[j]= p;  
    } else {  // Ѱ�����б��еĲ���λ��
      for ( q=M.chead[j]; (q->down) && q->down->i <i;  q = q->down );
        p->down = q->down;  q->down = p;    
    }  // ����в���
  } // for
  return OK;
} // CreateSMatrix_OL
                            

