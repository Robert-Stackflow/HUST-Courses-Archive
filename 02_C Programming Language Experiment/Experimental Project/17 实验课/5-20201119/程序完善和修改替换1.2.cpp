# include<stdio.h>
# include<string.h>
void RemoveDuplicate(char *s);
 
int main( )
{
	char str [200] ;
	printf ("Input strings,end of Ctrl+z\n");
	while (fgets(str,200,stdin)!=NULL)
	{
		RemoveDuplicate(str);
		printf("%s",str);
	}
	return 0;
}

void RemoveDuplicate(char *s)
{
	int i, j, len, remainder;  
    int check[8] = {0};  
    len = strlen(s);  
    for(i = j = 0; i < len; i++)  
    {  
        remainder = s[i] % 32;  
        if((check[s[i] >> 5] & (1 << remainder)) == 0)  
        {  
            s[j++] = s[i];  
            check[s[i] >> 5] |= (1 << remainder);  
        }  
    }  
    s[j] = '\0';  
} 

