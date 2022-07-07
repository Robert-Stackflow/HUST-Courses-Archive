

count=0
def move(n, a, b, c):
    global count
    if n==1:
        print (a,'-->',c)
        count=count+1
        return
    else:
        move(n-1,a,c,b)  #首先需要把 (N-1) 个圆盘移动到 b
        move(1,a,b,c)    #将a的最后一个圆盘移动到c
        move(n-1,b,a,c)  #再将b的(N-1)个圆盘移动到c
        
n=int(input('请输入盘子的个数：'))
move(n, 'A', 'B', 'C')
print("总共移动的次数：",count)
