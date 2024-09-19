#include<cstdlib>
#include<iostream>
#include <string.h>
# include <cstdio>
#include <limits>
#include <istream>
using namespace std;

const int N = 250;
struct card
{
    string col;//»¨É«
    char num;//ºÅÂë
};
card a[N];

void solve()
{
    int top=0;
    int n;
    cin>>n;
    while(n--)
    {
        string op;
        cin>>op;
        if(op=="Append")
        {
            top++;
            for(int i=top;i>=2;i--)
            {
                a[i].col=a[i-1].col;
                a[i].num=a[i-1].num;
            }
            cin>>a[1].col>>a[1].num;
        }
        else if(op=="Extract")
        {
            string dir;
            cin>>dir;
            int temptop=0;
            int cnt[100];
            memset(cnt,0,sizeof cnt);
            for(int i=1;i<=top;i++)
            {
                if(a[i].col==dir)
                {
                    temptop++;
                    cnt[a[i].num]++;
                    for(int j=i;j<=top;j++)
                    {
                        a[j].col=a[j+1].col;
                        a[j].num=a[j+1].num;
                    }
                }
            }
            for(int i=1;i<=100;i++)
            {
                if(cnt[i]==0)continue;
                while(cnt[i]--)
                {
                    a[top-temptop+1].col=dir;
                    a[top-temptop+1].num=char(i);
                    temptop--;
                }
            }
        }
        else if(op=="Revert")
        {
            for(int i=1;i<=top/2;i++)
            {
                card temp=a[i];
                a[i]=a[top-i+1];
                a[top-i+1]=temp;
            }
        }
        else if(op=="Pop")
        {
            if(top==0)
                cout<<"NULL"<<endl;
            else
            {
                cout<<a[top].col<<" "<<a[top].num<<endl;
                top--;
            }
        }
    }
    for(int i=top;i>=1;i--)
    {
        cout<<a[i].col<<" "<<a[i].num<<endl;
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