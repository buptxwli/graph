import random
type=random.randint(1,2)
row=random.randrange(4,50,2)
col=random.randrange(3,50,2)
end=int((row+col)/2)
carnum=random.randint(1,end)
startpoint=[[0 for i in range(2)] for j in range(carnum)]
endpoint=[[0 for i in range(2) ]for j in range(carnum)]
for i in range(carnum):
	startpoint[i][1]=random.randrange(0,col-1,2)
	if startpoint[i][1]%4==2:
		startpoint[i][0]=random.choice((0,row-1))
	else:
		startpoint[i][0]=0
	if startpoint[i][1]==col-1:
		startpoint[i][0]=row-1
	if startpoint[i][1]==2:
		startpoint[i][0]=0
	if startpoint[i][0]==0:
		endpoint[i][0]=row-1
		endpoint[i][1]=random.randrange(0,col,2)
		while endpoint[i][1]%4!=2 or endpoint[i][1]==col-1:
			endpoint[i][1]=random.randrange(0,col,2)
	else:
		endpoint[i][0]=0
		endpoint[i][1]=random.randrange(0,col,2)
		while endpoint[i][1]==0:
			endpoint[i][1]=random.randrange(0,col,2)
print('type:%d;row:%d;col:%d;carnum:%d' %(type,row,col,carnum))
for i in range(carnum):
	print('(%d,%d)->(%d,%d)'%(startpoint[i][0],startpoint[i][1],endpoint[i][0],endpoint[i][1]))
out=[[0 for cols in range(col)]for rows in range(row)]
def graph1(row,col):  #small crossing
	for rows in range(row):
		for cols in range (col):
			if rows==0 or rows==row-1:
				out[rows][cols]='#'
			if 1<=rows and rows<row/2 and cols%2!=0:
				out[rows][cols]='>'
			if rows<=row-2 and rows>=row/2 and cols%2!=0:
				out[rows][cols]='<'
			if (rows%4==1 and rows!=row-1 and cols%2==0)or(rows%4==2 and rows!=row-1 and cols%4==0)or(rows%4==0 and cols%4==2 and rows!=0):
				out[rows][cols]='X'
			if (rows%4==2 and rows!=row-1 and cols%4==2)or(rows%4==3 and rows!=row-1 and cols%2==0)or(rows%4==0 and cols%4==0 and rows!=0):
				out[rows][cols]='Y'
def graph2(row,col): #big crossing
	for rows in range(row):
		for cols in range(col):
			if rows==0 or rows==row-1:
				out[rows][cols]='#'
			if 1<=rows and rows<row/2 and cols%2!=0:
				out[rows][cols]='>'
			if rows<=row-2 and rows>=row/2 and cols%2!=0:
				out[rows][cols]='<'
			if rows!=0 and rows!=row-1 and cols%2==0:
				out[rows][cols]='X'
if type==1:
	graph1(row,col)
else:
	graph2(row,col)
f = open('output.txt', 'w+')
for line in out:
    for c in line:
        print ('%c' % str(c), file=f, end='')
    print ('', file=f)