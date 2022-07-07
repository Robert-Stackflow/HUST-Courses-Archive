#include "stdio.h"
#define I 2
#define J 3
int main(void)
{	  int u[I][J],(*p)[J]=u;
	  int j;
	  for(j=0;j<J;j++)     /* 用指向数组元素的指针完成第0行元素的输入 */
		  scanf("%d",(u[0]+j));
	  for(j=0;j<J;j++)     /* 用指向下一级数组的指针完成第1行元素的输入 */
		  scanf("%d",(*(u+1)+j));
	  for(j=0;j<J;j++)     /* 用指向下一级数组的指针完成第0行元素的输出 */
		  printf("%6d",*(*(u+0)+j));
	  printf("\n");
	  for(j=0;j<J;j++)     /* 用指向数组元素的指针完成第1行元素的输出 */
		  printf("%6d",*(u[1]+j)); 
	  printf("\n");
	  return 0;
}