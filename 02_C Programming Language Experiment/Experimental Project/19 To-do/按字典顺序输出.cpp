#include <stdio.h>
#include <string.h>
main()
{
 char a[10000];
 int str;
 char ch;
 printf("input a word:\n");
 scanf("%s",a);
 str=strlen(a);
for(int i=0;i<str;i++)
{
 for(int j=0;j<str-1-i;j++)
 {
  if(a[j]>a[j+1])
  {
  ch=a[j]; 
  a[j]=a[j+1];
  a[j+1]=ch;
  }
 }
}
 printf("%s\n",a);
}
