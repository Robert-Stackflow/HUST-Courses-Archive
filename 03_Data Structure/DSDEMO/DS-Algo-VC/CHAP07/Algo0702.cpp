Status CreateUDN(MGraph &G) {//  �㷨 7.2
  // �������飨�ڽӾ��󣩱�ʾ��������������G��
  int i,j,k,w; 
  VertexType  v1,v2; 
  printf("G.vexnum :" );  scanf("%d",&G.vexnum);
  printf("G.arcnum :");   scanf("%d",&G.arcnum);   
  getchar();  /*** ���ϴ˾�getchar()!!! ***/
  // scanf("%d,%d,%d",&G.vexnum, &G.arcnum, &IncInfo);      
  for (i=0; i<G.vexnum; i++ ) { 
    printf("G.vexs[%d] : ",i);
    scanf("%c",&G.vexs[i]); 
    getchar();
  } // ���춥������
  for (i=0; i<G.vexnum; ++i )  // ��ʼ���ڽӾ���
    for (j=0; j<G.vexnum; ++j ) {
      G.arcs[i][j].adj = INFINITY; //{adj,info}
      G.arcs[i][j].info= NULL;
    }
  for (k=0; k<G.arcnum; ++k ) {  // �����ڽӾ���
    printf("v1 (char) : ");  scanf("%c", &v1);getchar();
    printf("v2 (char) : ");  scanf("%c", &v2);getchar();
    printf("w (int) : " );   scanf("%d", &w); getchar();   
                             // ����һ���������Ķ��㼰Ȩֵ
    i = LocateVex(G, v1);  j = LocateVex(G, v2);    
          // ȷ��v1��v2��G��λ��
    G.arcs[i][j].adj = w;                // ��<v1,v2>��Ȩֵ
    // if (IncInfo) scanf(G.arcs[i][j].info); // ���뻡���������Ϣ
    G.arcs[j][i].adj = G.arcs[i][j].adj; // ��<v1,v2>�ĶԳƻ�<v2,v1>
  }
  return OK;
} // CreateUDN
