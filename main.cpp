#include<iostream>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<chrono>



using namespace std;

int nr,nc,nk,nq,qlist,klist,finalklist; 
int qpos[15][2],kpos[15][2],finalkpos[15][2];//works for 14*14 dimensions maximum
int attackcount[1000];
int diff_in_time[1000];
int itridx[100][2];
double tmax;

struct CB //chessbord structure
{
	int row;
	int col;
	int canQueen; //bool -> 0 - No and 1-yes
	int canKnight;//bool -> 0 - No and 1-yes
}cb[10][10];

void attackingcount(int h)
{
	int i,j,k,l;
	attackcount[h]=0;
	for(i=0;i<qlist;i++)
	{ 
		for(j=0;j<finalklist;j++)
		{
			if(kpos[j][0]==qpos[i][0] || kpos[j][1]==qpos[i][1] || kpos[j][0]==qpos[i][1] && kpos[j][1]==qpos[i][0])
			attackcount[h]=attackcount[h]+1;
			
		for(l=0;l<nr;l++)
		  {
		   for(int m=0;m<nc;m++)	
			{
				if(kpos[j][0]+l==qpos[i][0] && kpos[j][1]+m==qpos[i][1])
				attackcount[h]=attackcount[h]+1;
				if(kpos[j][0]-l==qpos[i][0] && kpos[j][1]-m==qpos[i][1])
				attackcount[h]=attackcount[h]+1;
				if(kpos[j][0]-l==qpos[i][0] && kpos[j][1]+m==qpos[i][1])
				attackcount[h]=attackcount[h]+1;
				if(kpos[j][0]+l==qpos[i][0] && kpos[j][1]-m==qpos[i][1])
				attackcount[h]=attackcount[h]+1;
			}
		  }	
		}
	}
}

void condition1(int row,int col)
{
	qpos[qlist][0]=row;
	qpos[qlist][1]=col;
	int m = 0;
	for(int n=0;n<nr;n++)
	{
		if(m==nc)
		{
		    m=0;
		    break;
		}
		//cb[r][c].canQueen=0;
		cb[row][m].canQueen=0;
		cb[n][col].canQueen=0;
		if(row+n<nr && col+m<nc)
		{
		    cb[row+n][col+m].canQueen=0;
			//cout<<"\nYo";
		    if(row-n>=0 && col-m>=0)
		    {
		    	cb[row+n][col-m].canQueen=0;
		    	cb[row-n][col+m].canQueen=0;
			}
		}
		
		
		if(row-n>=0 && col-m >=0)//diagonals
		{
			cb[row-n][col-m].canQueen=0;
			//cout<<"\nYo";
		}
	
	    m++;
	}

}

void condition2()
{
	int i,j,row,col;
	for(i=0;i<=qlist;i++)
	{
		if(qpos[i][0]-2>=0)
		{
			if(qpos[i][1]+1<nc)
			{
				row=qpos[i][0]-2;
				col=qpos[i][1]+1;
				//cout<<"\nYo1-1";
				cb[row][col].canKnight=0;
			}
			if(qpos[i][1]-1>=0)
			{
				row=qpos[i][0]-2;
				col=qpos[i][1]-1;
				//cout<<"\nYo1-2";
				cb[row][col].canKnight=0;
			}
		}
		if(qpos[i][0]+2<nr)
		{
			if(qpos[i][1]+1<nc)
			{
				row=qpos[i][0]+2;
				col=qpos[i][1]+1;
				//cout<<"\nYo1-3";
				cb[row][col].canKnight=0;
			}
			if(qpos[i][1]-1>=0)
			{
				row=qpos[i][0]+2;
				col=qpos[i][1]-1;
				//cout<<"\nYo1-4";
				cb[row][col].canKnight=0;
			}
		}
		if(qpos[i][1]-2>=0)
		{
			if(qpos[i][0]+1<nr)
			{
				row=qpos[i][0]+1;
				col=qpos[i][1]-2;
				//cout<<"\nYo1-5";
				cb[row][col].canKnight=0;
			}
			if(qpos[i][0]-1>=0)
			{
				row=qpos[i][0]-1;
				col=qpos[i][1]-2;
				//cout<<"\nYo1-6";
				cb[row][col].canKnight=0;
			}
		}
		if(qpos[i][1]+2<nc)
		{
			if(qpos[i][0]+1<nr)
			{
				row=qpos[i][0]+1;
				col=qpos[i][1]+2;
				//cout<<"\nYo1-7";
				cb[row][col].canKnight=0;
			}
			if(qpos[i][0]-1>=0)
			{
				row=qpos[i][0]-1;
				col=qpos[i][1]+2;
				//cout<<"\nYo1-8";
				cb[row][col].canKnight=0;
			}
		}
	}
	
	for(i=0;i<nr;i++)
	{
		for(j=0;j<nc;j++)
		{
			if(cb[i][j].canKnight==1)
			{
				//cout<<"\nYo";
				kpos[klist][0]=i;
				kpos[klist][1]=j;
				klist=klist+1;
			}
		}
	}
}

void condition3()
{
	int i,row,col,j;
	for(i=0;i<klist;i++)
    {
   	     if(kpos[i][0]-2>=0)
		{
			if(kpos[i][1]+1<nc)
			{
				row=kpos[i][0]-2;
				col=kpos[i][1]+1;
				//cout<<"\nYo1-1";
				cb[row][col].canKnight=0;
			}
			if(kpos[i][1]-1>=0)
			{
				row=kpos[i][0]-2;
				col=kpos[i][1]-1;
				//cout<<"\nYo1-2";
				cb[row][col].canKnight=0;
			}
		}
		if(kpos[i][0]+2<nr)
		{
			if(kpos[i][1]+1<nc)
			{
				row=kpos[i][0]+2;
				col=kpos[i][1]+1;
				//cout<<"\nYo1-3";
				cb[row][col].canKnight=0;
			}
			if(kpos[i][1]-1>=0)
			{
				row=kpos[i][0]+2;
				col=kpos[i][1]-1;
				//cout<<"\nYo1-4";
				cb[row][col].canKnight=0;
			}
		}
		if(kpos[i][1]-2>=0)
		{
			if(kpos[i][0]+1<nr)
			{
				row=kpos[i][0]+1;
				col=kpos[i][1]-2;
				//cout<<"\nYo1-5";
				cb[row][col].canKnight=0;
			}
			if(kpos[i][0]-1>=0)
			{
				row=kpos[i][0]-1;
				col=kpos[i][1]-2;
				//cout<<"\nYo1-6";
				cb[row][col].canKnight=0;
			}
		}
		if(kpos[i][1]+2<nc)
		{
			if(kpos[i][0]+1<nr)
			{
				row=kpos[i][0]+1;
				col=kpos[i][1]+2;
				//cout<<"\nYo1-7";
				cb[row][col].canKnight=0;
			}
			if(kpos[i][0]-1>=0)
			{
				row=kpos[i][0]-1;
				col=kpos[i][1]+2;
				//cout<<"\nYo1-8";
				cb[row][col].canKnight=0;
			}
		} 	
	}	
	
	for(i=0;i<nr;i++)
	{
		for(j=0;j<nc;j++)
		{
			if(cb[i][j].canKnight==1)
			{
				//cout<<"\nYo";
				kpos[finalklist][0]=i;
				kpos[finalklist][1]=j;
				finalklist=finalklist+1;
			}
		}
	}
}





void optimalconfiguration(int randQC,int randQR)
{
	int i,j,k;
	qlist=0;
	klist=0;
	finalklist=0;
	
	for(k=0;k<nr*nc;k++)
	{
	for(i=0;i<nr;i++)
	{
		for(j=0;j<nc;j++)
		{
		  cb[i][j].row=i;
		  cb[i][j].col=j;
		  cb[i][j].canQueen=1;
		  cb[i][j].canKnight=1;	
		}
	}
	}
	
//for first Queen
condition1(randQR,randQC);
qlist=qlist+1;	
for(i=0;i<nr;i++)
{
	for(j=0;j<nc;j++)
	{
		if(cb[i][j].canQueen==1)
		{
			condition1(i,j);
			//cout<<"\n"<<i<<j;
			
			qlist=qlist+1;
			
			cb[i][j].canKnight=0;//so that the knight doesnt co-incide with queen
		}
	}
}

	for(i=1;i<nq+1;i++)
	{
		cout<<"\nPos Queen:"<<i<<":"<<qpos[i][0]<<qpos[i][1];
	}
	
	condition2();
	//for(i=0;i<kpp;i++)
	{
	//	cout<<"\nPos Knight:"<<i<<":"<<posK[i][0]<<posK[i][1];
	}

	cout<<"\nExperimental after Game3:";
	condition3();
	for(i=1;i<nk+1;i++)
	{
		cout<<"\nPos Knight:"<<i<<":"<<kpos[i][0]<<kpos[i][1];
	}	
}

int SimulatedAnnealing(int k)
{
	    int optimalindex=0;
	 	//srand((unsigned)systime);
	 	double alpha = 0.005;
	 	const double e = 2.718281828;
	 	 int cnt_diff;

#include<cmath>

for(int T=90;T > 0.000005;T=T*alpha)  
	  {
	 	for(int x=1;x<k;x++)
	 	{
	 		 int index = rand() % k;
	 	     int cnt_diff = attackcount[index]-attackcount[optimalindex];
	 		 
	 		if(diff_in_time[index]<=tmax)
			 {
			 	if(attackcount[optimalindex]<=attackcount[index]|| (rand() / (double)RAND_MAX ) <= pow(e,-(cnt_diff)/T))
			 	{
			 	  optimalindex=index;	
				}
			 }
                     x++;	
	   	}
	  }
	 return optimalindex; 
} 

int HillClimbing(int y)//k is total number of samples
{
	 int i,j,optimalindex;
	 	optimalindex=0;
	 	for(j=1;j<y;j++)
	 	{
	 		if(diff_in_time[j]<=tmax)
			 {
			 	if(attackcount[optimalindex]>=attackcount[j])
			 	{
			 	  optimalindex=j;	
				}
			 }	
		}
		return optimalindex;
}
	

int main()

{
	int i,j,k,opindex,m,cnt;
	string method;
	ofstream fout;
	fout.open("solution.txt",ios::out);
	cout<<"\nEnter n - Board Dimensions:";
	cin>>nr;
	fout<<nr;
	cout<<"\nenter m - Board Dimensions:";
	cin>>nc;
	fout<<nc;
	cout<<"\nEnter number of Queens:";
	cin>>nq;
	fout<<nq;
	cout<<"\nEnter number of Knights:";
	cin>>nk;
	fout<<nk;
	cout<<"\nEnter tmax value in microseconds:";
	cin>>tmax;
	fout<<tmax;
	cout<<"\nEnter the method:";
	cin>>method;
	fout<<method;
	
	k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			
			optimalconfiguration(i,j);
			itridx[k][0]=i;
			itridx[k][1]=j;
			
			std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
			
			diff_in_time[k]=std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
			attackingcount(k);
			cout<<"\nDuration of execution"<<diff_in_time[k];
			cout<<"\nNumber of attackings:"<<attackcount[k];
			k=k+1;
		}
	}
	if (method == "sa"){
	
	    opindex = SimulatedAnnealing(k);
	    
	}
	if(method == "hc"){
	    opindex = HillClimbing(k);
	    
	}
	else cout<<"insufficient information "<<endl;
	cout<<"\n\n";
	cout<<"\nIndex with the minimum number of Conflicts:"<<opindex;
	cout<<"\nattackings:"<<attackcount[opindex];
	optimalconfiguration(itridx[opindex][0],itridx[opindex][1]);
	cout<<endl;
	
	for(i=0;i<nr;i++)
	{
		for(j=0;j<nc;j++)
		{
			cnt=0;
		  for(m=0;m<nk;m++)
		  {
		  	if(cb[i][j].row==kpos[m][0] && cb[i][j].col==kpos[m][1])
		  	{
		  		cout<<"K";
		  		fout<<"K";
		  		cnt=1;
		  		break;
			}
			
		  }
		  if(cnt!=1)
                   {
                    for(m=0;m<nq;m++)
		     {
		  	if(cb[i][j].row==qpos[m][0] && cb[i][j].col==qpos[m][1])
		  	{
		  		cout<<"Q";
		  		fout<<"Q";
				cnt=1;	
				break;
			}
		     }
                    }
		  if(cnt==0)
		  {
		  	cout<<"A";
		  	fout<<"A";
		  	continue;
		  }
		}
		cout<<""<<endl;
		fout<<""<<endl;
	}
    fout.close();
	return 0;
}
