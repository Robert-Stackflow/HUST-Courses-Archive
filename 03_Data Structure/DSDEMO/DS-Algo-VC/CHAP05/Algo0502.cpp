Status  FastTransposeSMatrix(TSMatrix M, TSMatrix &T) {  // �㷨5.2
  // ������Ԫ��˳���洢��ʾ����ϡ�����M��ת�þ���T
  int col, t, p, q;
  int num[20], cpot[20];
  T.mu = M.nu;  T.nu = M.mu;  T.tu = M.tu;
  if (T.tu) {
    for (col=1; col<=M.nu; ++col) num[col] = 0;
    for (t=1; t<=M.tu; ++t) // �� M ��ÿһ����������Ԫ�ĸ���
       ++num[M.data[t].j];
    cpot[1] = 1;         
    // �� M ��ÿһ�еĵ�һ������Ԫ�� b.data �е����
    for (col=2; col<=M.nu; ++col) cpot[col] = cpot[col-1]+num[col-1];
    for (p=1; p<=M.tu; ++p) {    
      col = M.data[p].j;   q = cpot[col];
      T.data[q].i =M.data[p].j;  T.data[q].j =M.data[p].i;
      T.data[q].e =M.data[p].e;  ++cpot[col]; 
    } // for
  } // if
  return OK;
} // FastTransposeSMatrix
                             
