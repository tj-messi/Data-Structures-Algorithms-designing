#include<iostream>
#include<iomanip>
using namespace std;
#define MAX_DEF 1010
#define DOU_MAX 2025
#define max 1000
void Add(int a1[],int a2[],int b[]) {
	for(int i=0; i<1001; i++)
		b[i]=a1[i]+a2[i];
}
void OutPut(int ar[],int range) {
	int p=0;
	for(int i=0; i<=range; i++) {
		if(ar[i]!=0) {
			if(p)putchar(' ');
			printf("%d %d",ar[i],i);
			p=1;
		}
	}
	if(!p)printf("0 0");	
}
void Mul(int a1[],int a2[],int b[]) {
	for(int i=0; i<1001; i++) {
		for(int j=0; j<1001; j++) {
			b[i+j]+=a1[i]*a2[j];
		}
	}
}
void solve()
{
int a,i,b,j,n1,n2;
	int ar2[MAX_DEF]= {0};
	int ar1[MAX_DEF]= {0};
	int ADDar[MAX_DEF] = {0};
	int MULar[DOU_MAX]= {0};
 scanf("%d", &n1);
for(i = 0; i < n1; ++i)
    {
        scanf("%d%d", &a, &b);
        ar1[b] = a;
    }
    scanf("%d", &n2);
    for(i = 0; i < n2; ++i)
    {
        scanf("%d%d", &a, &b);
        ar2[b] = a;
    }

 for(i = 0; i <= max; ++i)
    {
        for(j = 0; j <= max; ++j)
        {
            MULar[i + j] += ar1[i] *ar2[j];
        }
    }
    //计算加法
    for(i = 0; i <= max; ++i)
    {
        ADDar[i] = ar1[i] +ar2[i];
    }
	int op;
	cin>>op;
	if(op==0)
	{
		OutPut (ADDar,1001);
	}
	else if(op==1)
	{
		OutPut(MULar,2001);
	}
	else
	{
		OutPut (ADDar,1001);
		OutPut(MULar,2001);
	}
}

int main()
{
    int t;
    t=1;
    //cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}