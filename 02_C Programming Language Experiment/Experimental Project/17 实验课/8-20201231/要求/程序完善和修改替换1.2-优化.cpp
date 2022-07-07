# include<stdio.h>
# include<string.h>
void RemoveDuplicate(char *s);
 
int main( )
{
	char str [200] ;
	fgets(str,200,stdin); 
		RemoveDuplicate(str);
		printf("%s",str);
	return 0;
}

void RemoveDuplicate(char *s)
{
	char t[256] = { 0 };  
    int i, j, len;  
    len = strlen(s);  
    for(i = j = 0; i < len; i++)  
    {  
        if(t[s[i]] == 0)  
        {  
            s[j++] = s[i];  
            t[s[i]] = 1;  
        }  
    }  
    s[j] = '\0';  
} 

