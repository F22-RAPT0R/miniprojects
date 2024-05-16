"""
1403/02/27
user enters number of rows and columns for a 2d matrix
program prints sorted matrix
"""
import random

class Sort():

    def __init__(self):
        self.get_arr()
        self.create_arr()
        self.sort_arr()
        self.print_arr()
        # self.test_left_right()

    def create_arr(self):
        self.arr=[[0 for _ in range(self.n)] for _ in range(self.m)]
        
        random.seed()
        for i in range(self.m):
            for j in range(self.n):
                self.arr[i][j]=random.randint(0,100)

    def print_arr(self):
        print("")
        for i in range(self.m):
            for j in range(self.n):
                print("[{:02}*{:02}]:{:2}".format(i,j,self.arr[i][j]),end="\t")
            print()    

    def sort_arr(self):
        for i in range(0,self.m):
            for j in range(0,self.n):
                key=self.arr[i][j]
                index=self.left(i,j)
                while(index!=None and self.arr[index[0]][index[1]]>key): 
                    rgt=self.right(index[0],index[1])
                    self.arr[rgt[0]][rgt[1]]=self.arr[index[0]][index[1]]
                    index=self.left(index[0],index[1])
                if(index==None):
                    self.arr[0][0]=key
                else:
                    rgt=self.right(index[0],index[1])
                    self.arr[rgt[0]][rgt[1]]=key

    def left(self,x,y):      
        if(y>0):
            xx=x
            yy=y-1
            return (xx,yy)
        elif(y==0):  
            if(x>0):
                xx=x-1
                yy=self.n-1
                return (xx,yy)

        return None        
                    
    def right(self,x,y):
        if(0<=y<self.n-1):
            xx=x
            yy=y+1
            return (xx,yy)
        elif(y==self.n-1):  
            if(0<=x<self.m-1):
                xx=x+1
                yy=0
                return (xx,yy)

        return None  

    def test_left_right(self):
        for i in range(self.m):
            for j in range(self.n):
                lft=self.left(i,j)
                if(not lft):
                    print(f"LEFT: None",end="\t")
                else:
                    print(f"LEFT: [{lft[0]}*{lft[1]}]",end="\t")

                print(f"[{i}*{j}]",end="\t")

                rgt=self.right(i,j)
                if(not rgt):
                    print(f"RIGHT: None",end="\n")
                else:
                    print(f"RIGHT: [{rgt[0]}*{rgt[1]}]",end="\n")

    def get_arr(self):
        # self.m=4
        # self.n=6
        self.m=int(input("enter number of rows:"))   #row
        self.n=int(input("enter number of columns:"))   #column
        
Sort()