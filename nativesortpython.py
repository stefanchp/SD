import sys
f=open(sys.argv[1],"r")
g=open(sys.argv[2], "w")
n=f.readline()
v=f.readline()
arr=[int(x) for x in v.split()]
arr=sorted(arr)

f.close()
g.close()