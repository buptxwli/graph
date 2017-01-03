row=int(input('row:'))
col=int(input('col:'))
type=int(input('type:'))
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