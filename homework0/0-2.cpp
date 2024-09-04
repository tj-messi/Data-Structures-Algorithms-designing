#include<iostream>
#include<iomanip>
using namespace std;
#define int long long
 
void solve()
{
    while(1)
    {
        int n;
        cin>>n;
        if(n==-1)break;
        int man=0,woman=1;
        while(n--)
        {
            int temp=man;
            man=(man+woman);
            woman=temp+1;
        }
        cout<<man<<" "<<man+woman<<endl;
    }
}
 
signed main()
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