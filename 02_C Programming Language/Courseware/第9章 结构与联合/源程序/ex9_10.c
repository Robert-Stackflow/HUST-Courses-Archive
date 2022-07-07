#include "stdio.h"
union chl{ char	c; short	h; long	l; };
void show(union chl *pu);
void show_memoy(union chl *pu);
int main(void)
{	union chl u;
	printf("size of u is %d\n",sizeof(u));
	u.l=0x31323334L;
	show(&u);
	show_memoy(&u);
	u.h=0x3638;
	show(&u);
	show_memoy(&u);
	return 0;
}
void show(union chl *pu)
{	printf("char format: %c\n",(*pu).c);
	printf("int format: %hx\n",pu->h);
	printf("long format: %lx\n",(*pu).l);
}
void show_memoy(union chl *pu)
{	char *p=(char *)pu;
	int i=0;
	while(i<4){
		printf("addr %dth byte of u is 0x%p\t",i,p+i);
		printf("the ASCII in %dth byte of u is %c\n",i,*(p+i));
		i++;
	}
}

