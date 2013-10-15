// binarypnkerror.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define intger	unsigned int 	
#include <cmath>
#include <iostream>
#include <memory>
#include <fstream>
int p=3,q=2,n=3;
int tag=0;//linshi 
#define length 27  //数组长度
using namespace std;
#define MaxNum	(unsigned int)(pow(2,1.0*length)-1)

int s[length]={0}; 
int cost[length]={0};
int len=length;
int *b=NULL;
int temp1=0,temp2=0;
ofstream puttext("out.txt");

int yi=0,er=0,ling=0;


bool ifequal(int *s,int p,int l)
{
	for (int j=0;j<l;j++)
	{
		for (int i=0;i<p;i++)
		{
			if (*(s+j)!=*(s+j+i*l))
			{
				return false;
			}
		}
	}
	return	true;
}
int solveLinearComplexity(int *s)
{
	int l=len,c=0;
	while (l!=1)
	{
		l=l/p;
		if (ifequal(s,p,l)==false)
		{
			c+=(p-1)*l;
			for (int i=0;i<l;i++)
			{
				for (int j=1;j<p;j++)
				{
					s[i]+=s[i+j*l];
					s[i]=s[i]%q;
				}
			}
		}
	}
	if (s[0]==1)
	{
		c++;
	}
	return c;
}

void outputs(int s[])
{
	int i=0;
	for (i=0;i<length;i++)
	{
		puttext<<s[i]<<" ";
	}
}

void convert(int s[],unsigned int number)
{
	memset(s,0,length*sizeof(int));
	int i=len-1;
	while (number!=0)
	{
		s[i--]=number%q;
		number/=q;
	}
}
int solvemin(int i,int T)
{
	temp1=0;
	temp2=0;
	for (int j=0;j<p;j++)
	{
		temp1+=(*(s+i+j*T))*cost[i+j*T];
		temp2+=(1-*(s+i+j*T))*cost[i+j*T];
	}

	return	temp1<temp2?temp1:temp2;
}
int solvekerrorLinearComplexity(int *s,int k)
{
	int T=(int)pow(p*1.0,n);
	int LC=0,K=0;
	int i=0,j=0;
	for (i=0;i<T;i++)
	{
		cost[i]=1;
	}
	while (T>1)
	{
		T/=p;
		int *b=(int *)malloc(T*sizeof(int));
		memset(b,0,T*sizeof(int));
		for (i=0;i<T;i++)
		{
			for (j=0;j<p;j++)
			{
				(*(b+i))+=(*(s+j*T+i));
			}
			
		}
		K=0;
		for (i=0;i<T;i++)
		{
			if (*(b+i)<p&&*(b+i)>0)
			{
				K+=solvemin(i,T);
			}
		}		
		if (K<=k)
		{
			k-=K;
			for (i=0;i<T;i++)
			{
				if (0<*(b+i)&&*(b+i)<p)
				{
					solvemin(i,T);
					if (temp1<=temp2)
					{
						cost[i]=temp2-temp1;
						*(s+i)=0;
					}
					else
					{
						cost[i]=temp1-temp2;
						*(s+i)=1;
					}
				}
				else
				{
					for (j=1;j<p;j++)
					{
						cost[i]+=cost[i+j*T];
					}
				}
			}
		}
		else
		{
			LC+=(p-1)*T;
			for (i=0;i<T;i++)
			{
				for (j=1;j<p;j++)
				{
					*(s+i)+=(*(s+i+j*T));
				}
				*(s+i)%=q;
				for (j=1;j<p;j++)
				{
					if (cost[i]>cost[i+j*T])
					{
						cost[i]=cost[i+j*T];
					}
				}
			}
		}
		free(b);
	}
	if ((*s==1)&&(cost[0]>k))
	{
		LC++;
	}
/*
	if (LC==18)
	{
		tag=0;
		switch(k)
		{
		case 0:	er++;tag=1;break;
		case 1:	yi++;break;
		case 2: ling++;break;
		}
	}
	*/
	return LC;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int i=0;
	int ou=0;
//////////////////////////////////
//	/*	

int *backups=(int *)malloc(length*sizeof(int));
memset(backups,0,length*sizeof(int));
int kerror[length+1]={0};


	for (i=0;i<=MaxNum;i++)
	{
		if (i%1000000==0)
		{
			cout<<i/1000000<<"	";
		}
		convert(s,i);
		memcpy(backups,s,length*sizeof(int));
//		outputs(s);
//		puttext<<"	"<<solveLinearComplexity(s)<<"	";
//		memcpy(s,backups,length*sizeof(int));
//		puttext<<solvekerrorLinearComplexity(s,1)<<endl;
//		memcpy(s,backups,length*sizeof(int));
	
		ou=solvekerrorLinearComplexity(s,3);
		kerror[ou]++;
///////////////////////
		/*
		if (ou==6&&tag==1)
		{
			outputs(backups);
			puttext<<endl;
		}
	*/
//////////////////
	}

	


///////

	free(backups);
for (i=0;i<length+1;i++)
{
	puttext<<kerror[i]<<endl;
}
/*
puttext<<"ling="<<ling<<endl;
puttext<<"yi="<<yi<<endl;
puttext<<"er="<<er<<endl;
*/
/////////////////////////////////////////

	return 0;
}

