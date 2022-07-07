Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q) {  
  // �㷨5.3
  // �����˻�Q=M?N���������߼����Ӵ洢��ʾ��
  int arow,brow,p,q,t,ctemp[30],l,ccol,tp;
  if (M.nu != N.mu) return ERROR;
  Q.mu = M.mu; Q.nu = N.nu; Q.tu = 0;       // Q��ʼ��
  if (M.tu*N.tu != 0) {   // Q�Ƿ������
    for (arow=1; arow<=M.mu; ++arow) {      // ����M��ÿһ��
      for (l=1; l<=M.nu; ++l) ctemp[l] = 0; // ��ǰ�и�Ԫ���ۼ�������
      Q.rpos[arow] = Q.tu+1; 
      if (arow<M.mu) tp=M.rpos[arow+1];
      else tp=M.tu+1;
      for (p=M.rpos[arow]; p<tp;++p) { // �Ե�ǰ����ÿһ������Ԫ    
        brow=M.data[p].j;          // �ҵ���ӦԪ��N�е��к�
        if (brow < N.mu ) t = N.rpos[brow+1];
        else t = N.tu+1;
        for (q=N.rpos[brow];  q< t;  ++q) {
          ccol = N.data[q].j;            // �˻�Ԫ����Q���к�
          ctemp[ccol] += M.data[p].e * N.data[q].e;
        } // for q
      } // ���Q�е�crow( =arow)�еķ���Ԫ
      for (ccol=1; ccol<=Q.nu; ++ccol) // ѹ���洢���з���Ԫ
        if (ctemp[ccol]) { 
          if (++Q.tu > MAXSIZE) return ERROR;
          Q.data[Q.tu].i=arow;
          Q.data[Q.tu].j=ccol;
          Q.data[Q.tu].e=ctemp[ccol];
        } // if
    } // for arow
  } // if   
  return OK;
} // MultSMatrix
