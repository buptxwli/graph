import random
type=3
row=8
col=88
carnum=100
startpoint=[[0 for i in range(2)] for j in range(carnum)]
endpoint=[[0 for i in range(2) ]for j in range(carnum)]
out=[[0 for cols in range(col)]for rows in range(row)]
for rows in range(row):
    for cols in range(col):
        if rows==0 or rows==row-1:
            out[rows][cols]='#'
        else :
            if rows>0 and rows<row/2 and cols%3!=0:
                out[rows][cols]='>'
            if rows>=row/2 and rows<row-1 and cols%3!=0:
                out[rows][cols]='<'
            if (rows==1 or rows==5) and cols%3==0 :
                out[rows][cols]='X'
            if rows==3 and cols%3==0:
                out[rows][cols]='Y'
            if (rows==2 or rows==6) and cols%6==0:
                out[rows][cols]='X'
            if (rows==2 or rows==6) and cols%3==0 and cols%6!=0:
                out[rows][cols]='Y'
            if rows==4 and cols%6==0:
                out[rows][cols]='Y'
            if rows==4 and cols%3==0 and cols%6!=0:
                out[rows][cols]='X'
for i in range(carnum):
    startpoint[i][1]=random.randrange(0,col,3)
    if startpoint[i][1]%6==3:
        startpoint[i][0]=random.choice((0,row-1))
    else :
        startpoint[i][0]=0
    if startpoint[i][1]==3:
        startpoint[i][0]=0
    if startpoint[i][1]>=81 and startpoint[i][0]==0:
        if startpoint[i][1]!=84:
            startpoint[i][0]=7
        else:
            startpoint[i][1]=81
            startpoint[i][0]=7
    if startpoint[i][0]==0:
        endpoint[i][0]=row-1
        endpoint[i][1]=random.randrange(0,78,3)
        while endpoint[i][1]%6!=3:
            endpoint[i][1]=random.randrange(0,78,3)
    else:
        endpoint[i][0]=0
        endpoint[i][1]=random.randrange(6,col-1,3)
f = open('E:/code/proj/input.txt', 'w+')
print('%d %d' %(row,col),file=f)
for line in out:
    for c in line:
        print ('%c' % str(c), file=f, end='')
    print ('', file=f)
print('%d' % carnum,file=f)
for i in range(carnum):
    print('%d %d %d %d'%(startpoint[i][0],startpoint[i][1],endpoint[i][0],endpoint[i][1]),file=f)