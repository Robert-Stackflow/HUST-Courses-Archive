#include <stdio.h>
enum year{jan,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec};
int main() {
    enum year month;
    int yearnum,yeardays=365;
    char *monthname[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    int monthdays[]={31,28,31,30,31,30,31,31,30,31,30,31};
    scanf("%d",&yearnum);
    if(!(yearnum%4)&&yearnum%100||!(yearnum%400))
        monthdays[1]=29,yeardays=366;
    
    for(month=jan;month<=dec;month++)
        printf("%s: %d\n",monthname[month],monthdays[month]);
        return 0;
}
