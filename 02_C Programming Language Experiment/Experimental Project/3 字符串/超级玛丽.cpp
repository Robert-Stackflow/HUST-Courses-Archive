#include <bits/stdc++.h>
using namespace std;
int mp[100][100];
int last[100];
int n = 22, m = 62;
// ��[x1-x2, y1-y2]����ch
void draw(int x1, int y1, int x2, int y2, char ch = '#'){
    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
            mp[i][j] = ch;
}
// ��[x1, y1]����ch
void draw(int x1, int y1, char ch = '*'){
    draw(x1, y1, x1, y1, ch);
}
// ��[x, y]Ϊ���Ͻǻ�������
void drawland(int x, int y){
    draw(x, y, x+8, y+13);
    for(int i = x+1; i < x+8; i+=2)
        draw(i, y+1, i, y+12, '.');
    draw(x+1, y+4); draw(x+1, y+11);
    draw(x+3, y+3); draw(x+3, y+8);
    draw(x+5, y+6); draw(x+7, y+2);
    draw(x+7, y+5); draw(x+7, y+10);
}
// ��[x, y]Ϊ���Ͻǻ���С��
void drawisland(int x, int y){
    draw(x, y, x+3, y+19);
    draw(x+1, y+1, x+2, y+18, 'G');
    draw(x+4, y+4, x+8, y+15);
    draw(x+4, y+5, x+7, y+14, '-');
}
// ��[x, y]Ϊ���Ͻǻ��ƽ��
void drawcoin(int x, int y){
    draw(x, y, x+5, y+4);
    draw(x+1, y+1, x+4, y+3, '.');
    draw(x+2, y+2, x+3, y+2);
    draw(x, y, ' '); draw(x+5, y, ' ');
    draw(x, y+4, ' '); draw(x+5, y+4, ' ');
}
// ��[x, y]Ϊ���Ͻǻ��������
void drawman(int x, int y){
    draw(x, y+5, x, y+12, '*'); x++;
    draw(x, y+4, x, y+15, '*'); x++;
    draw(x, y+4, x, y+7); draw(x, y+8, x, y+13, '.'); draw(x, y+12); x++;
    draw(x, y+2, x, y+14); draw(x, y+3, x, y+4, '.');
    draw(x, y+8, x, y+12, '.'); draw(x, y+15, x, y+18, '.'); x++;
    draw(x, y+2, x, y+17); draw(x, y+5, x, y+11, '.'); x++;
    draw(x, y+5, x, y+15, '.'); x++;
    draw(x, y+4, x, y+13); draw(x, y+6, '*'); x++;
    draw(x, y+1, x, y+17); draw(x, y+5, x, y+11, '*'); x++;
    draw(x, y, x+2, y+20, '.'); draw(x, y+4, x+2, y+16, '*');
    draw(x, y+3); draw(x, y+14, x+1, y+16); draw(x+1, y+16, '.');
    draw(x+2, y+8, x+2, y+11, ' '); draw(x, y+7, '.'); draw(x, y+12, '.');
    draw(x+3, y, x+4, y+19); draw(x+3, y+6, x+4, y+13, ' ');
    draw(x+3, y, x+3, y+1, ' '); draw(x+3, y+18, x+3, y+19, ' ');
}
// ��ӡ���
void printscreen(){
    for(int i = 1; i <= n; i++){
        last[i] = m;
        while(mp[i][last[i]] == ' ')
            last[i]--;
    }
    for(int i = 1; i <= n; i++,puts(""))
        for(int j = 1; j <= last[i]; j++)
            putchar(mp[i][j]);
}
int main(){
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            mp[i][j] = ' ';
    // ������
    drawman(1, 12);
    // ���������µ���������
    drawland(14,1); drawland(14, 15); drawland(14, 29);
    // ���ƽ��������Ǹ�����
    drawisland(14, 43);
    // �����������
    drawcoin(5, 43); drawcoin(5, 58);
    // ���
    printscreen();
    system("pause"); 
    return 0;
}
