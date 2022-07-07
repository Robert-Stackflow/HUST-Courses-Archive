#include <bits/stdc++.h>
using namespace std;
int mp[100][100];
int last[100];
int n = 22, m = 62;
// 在[x1-x2, y1-y2]绘制ch
void draw(int x1, int y1, int x2, int y2, char ch = '#'){
    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
            mp[i][j] = ch;
}
// 在[x1, y1]绘制ch
void draw(int x1, int y1, char ch = '*'){
    draw(x1, y1, x1, y1, ch);
}
// 以[x, y]为左上角绘制泥土
void drawland(int x, int y){
    draw(x, y, x+8, y+13);
    for(int i = x+1; i < x+8; i+=2)
        draw(i, y+1, i, y+12, '.');
    draw(x+1, y+4); draw(x+1, y+11);
    draw(x+3, y+3); draw(x+3, y+8);
    draw(x+5, y+6); draw(x+7, y+2);
    draw(x+7, y+5); draw(x+7, y+10);
}
// 以[x, y]为左上角绘制小岛
void drawisland(int x, int y){
    draw(x, y, x+3, y+19);
    draw(x+1, y+1, x+2, y+18, 'G');
    draw(x+4, y+4, x+8, y+15);
    draw(x+4, y+5, x+7, y+14, '-');
}
// 以[x, y]为左上角绘制金币
void drawcoin(int x, int y){
    draw(x, y, x+5, y+4);
    draw(x+1, y+1, x+4, y+3, '.');
    draw(x+2, y+2, x+3, y+2);
    draw(x, y, ' '); draw(x+5, y, ' ');
    draw(x, y+4, ' '); draw(x+5, y+4, ' ');
}
// 以[x, y]为左上角绘制马里奥
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
// 打印输出
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
    // 绘制人
    drawman(1, 12);
    // 绘制他脚下的三块泥土
    drawland(14,1); drawland(14, 15); drawland(14, 29);
    // 绘制金币下面的那个岛屿
    drawisland(14, 43);
    // 绘制两个金币
    drawcoin(5, 43); drawcoin(5, 58);
    // 输出
    printscreen();
    system("pause"); 
    return 0;
}
