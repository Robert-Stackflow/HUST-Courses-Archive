#include "stdio.h"
int main(void)
{ int i;
	  char devices[3][12]={"hard disk","CRT","keyboard"};
	  devices[0][0]= 'H';  /* "hard disk"变为"Hard disk"*/
	  devices[2][0]= 'K';	/* "keyboard "变为"Keyboard "*/
	  for(i=0;i<3;i++)
		  printf("%s\n", &devices[i][0]);
	  scanf("%s",devices[1]);
	  for(i=0;i<3;i++)
		  printf("%s\n", devices[i]);
	  return 0;
}
