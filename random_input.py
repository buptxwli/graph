import random
#type=random.randint(1,2)
type=1
row=random.randrange(4,30,2)
col=random.randrange(5,30,1)
if col%2==0 :
    lanenum=2
else:
    lanenum=random.randrange(1,3,2)
end=int((row+col)/2)
carnum=random.randint(1,end)
startpoint=[[0 for i in range(2)] for j in range(carnum)]
endpoint=[[0 for i in range(2) ]for j in range(carnum)]
out=[[0 for cols in range(col)]for rows in range(row)]
def graph1(row,col,lanenum):
    for rows in range(row):
        for cols in range(col):
            if rows==0 or rows==row-1:
                out[rows][cols]='#'
            if 1<=rows and rows<row/2 and cols%(lanenum+1)!=0:
                out[rows][cols]='>'
            if rows>=row/2 and rows<row-1 and cols%(lanenum+1)!=0:
                out[rows][cols]='<'
            if (rows%4==1 and rows!=row-1 and cols%(lanenum+1)==0)or(rows%4==2 and rows!=row-1 and cols%(2*lanenum+2)==0)or(rows%4==0 and cols%(2*lanenum+2)==2 and rows!=0):
                out[rows][cols]='X'
            if (rows%4==2 and rows!=row-1 and cols%(2*lanenum+2)==2)or(rows%4==3 and rows!=row-1 and cols%(lanenum+1)==0)or(rows%4==0 and cols%(2*lanenum+2)==0 and rows!=0):
                out[rows][cols]='Y'
def graph2(row,col,lanenum):  #big crossing
    for rows in range(row):
        for cols in range(col):
            if rows==0 or rows==row-1:
                out[rows][cols]='#'
            if rows>0 and rows<row/2 and cols%(lanenum+1)!=0:
                out[rows][cols]='>'
            if rows>=row/2 and rows<row-1 and cols%(lanenum+1)!=0:
                out[rows][cols]='<'
            if rows>0 and rows<row-1 and cols%(lanenum+1)==0:
                out[rows][cols]='X'
print('row:%d;col:%d;carnum:%d' %(row,col,carnum))
if type==1:
    for i in range(carnum):
        startpoint[i][1]=random.randrange(0,col-1,lanenum+1)
        startpoint[i][0]=random.choice((0,row-1))
        while (startpoint[i][0]==0 and startpoint[i][1]>=col-2-lanenum ) and (startpoint[i][0]==row-1 and startpoint[i][1]<=lanenum+1):
            startpoint[i][1]=random.randrange(0,col-1,lanenum+1)
            startpoint[i][0]=random.choice((0,row-1))
        if startpoint[i][0]==0:
            endpoint[i][0]=row-1
        else:
            endpoint[i][0]=0
        endpoint[i][1]=random.randrange(0,col-1,lanenum+1)
        while (endpoint[i][0]==row-1 and endpoint[i][1]>=col-2-lanenum ) or (endpoint[i][0]==0 and endpoint[i][1]<=lanenum+1):
            endpoint[i][1]=random.randrange(0,col-1,lanenum+1)
if type==2:
    for i in range(carnum):
        startpoint[i][1]=random.randrange(0,col-1,lanenum+1)
        startpoint[i][0]=random.choice((0,row-1))
        if startpoint[i][0]==0:
            endpoint[i][0]=row-1
        else:
            endpoint[i][0]=0
        endpoint[i][1]=random.randrange(0,col-1,lanenum+1)
for i in range(carnum):
	print('(%d,%d)->(%d,%d)'%(startpoint[i][0],startpoint[i][1],endpoint[i][0],endpoint[i][1]))
if type==1:
	graph1(row,col,lanenum)
else:
	graph2(row,col,lanenum)
f = open('E:/code/proj/input.txt', 'w+')
print('%d %d' %(row,col),file=f)
for line in out:
    for c in line:
        print ('%c' % str(c), file=f, end='')
    print ('', file=f)
print('%d' % carnum,file=f)
for i in range(carnum):
    print('%d %d %d %d'%(startpoint[i][0],startpoint[i][1],endpoint[i][0],endpoint[i][1]),file=f)