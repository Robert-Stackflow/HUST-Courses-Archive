int GListDepth(GList L) {  // �㷨5.5
  // ����ͷβ����洢�ṹ,������L����ȡ�
  int max, dep;
  GList pp;
  if (!L) return 1;                // �ձ����Ϊ1
  if (L->tag == ATOM) return 0;    // ԭ�����Ϊ0
  for (max=0, pp=L;  pp;  pp=pp->ptr.tp) {
    dep = GListDepth(pp->ptr.hp);  // ����pp->ptr.hpΪͷָ����ӱ����
    if (dep > max) max = dep;
  }
  return max + 1;        // �ǿձ������Ǹ��ӱ����ȵ����ֵ��1
} // GListDepth
                            

