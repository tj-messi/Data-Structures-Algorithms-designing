#include<iostream>
#include<iomanip>
using namespace std;
 
void solve()
{
    int n;
    n=12;
    double ans=0;
    for(int i=1;i<=n;i++)
    {
        double temp;
        cin>>temp;
        ans+=temp;
    }
    cout<<"¥"<<setiosflags(ios::fixed)<<setprecision(2)<<ans/(double)12<<endl;
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
