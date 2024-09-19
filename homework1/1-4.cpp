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
    string num;//ºÅÂë
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
                if(i==1)
                    break;
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
            int Temp[100];
            memset(Temp,0,sizeof Temp);
            for(int i=1;i<=top-temptop;i++)
            {
                if(a[i].col==dir)
                {
                    temptop++;
                   if (a[i].num==  "A")  Temp[1]++;
                     if (a[i].num==  "2")  Temp[2]++;
                    if (a[i].num==  "3")  Temp[3]++;
                    if (a[i].num==  "4")  Temp[4] ++;
                  if (a[i].num==  "5")  Temp[5]++;
                     if (a[i].num==  "6")  Temp[6] ++;
                    if (a[i].num==  "7")  Temp[7] ++;
                  if (a[i].num==  "8")  Temp[8] ++;
                    if (a[i].num== "9")  Temp[9] ++;
                    if (a[i].num== "10") Temp[10]++;
                    if (a[i].num==  "J")  Temp[11] ++;
                    if (a[i].num== "Q")  Temp[12] ++;
                    if (a[i].num== "K")  Temp[13] ++;
                    //cout<<"num"<<a[i].num<<endl;
                    for(int j=i;j<=top-temptop;j++)
                    {
                        a[j].col=a[j+1].col;
                        a[j].num=a[j+1].num;
                    }
                    i--;
                    //cout<<temptop<<endl;
                }
            }
            for(int i=13;i>=1;i--)
            {
                //cout<<Temp[i]<<" ";
            }
            //cout<<endl;
            for(int i=13;i>=1;i--)
            {
                if(Temp[i]==0)continue;
                while(Temp[i]--)
                {
                    a[top-temptop+1].col=dir;
                    
            if (i == 1)  a[top-temptop+1].num = "A";
            if (i == 2)  a[top-temptop+1].num = "2";
            if (i == 3)  a[top-temptop+1].num = "3";
            if (i == 4)  a[top-temptop+1].num = "4";
            if (i == 5)  a[top-temptop+1].num = "5";
            if (i == 6)  a[top-temptop+1].num = "6";
            if (i == 7)  a[top-temptop+1].num= "7";
            if (i == 8)  a[top-temptop+1].num = "8";
            if (i == 9)  a[top-temptop+1].num= "9";
            if (i == 10) a[top-temptop+1].num = "10";
            if (i == 11) a[top-temptop+1].num = "J";
            if (i == 12) a[top-temptop+1].num= "Q";
            if (i == 13) a[top-temptop+1].num = "K";

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
    if(top==0)
        return;
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