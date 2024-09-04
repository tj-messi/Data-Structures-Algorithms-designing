#include<iostream>
#include<iomanip>
using namespace std;
#define int long long
 
void solve()
{
    int n,m;cin>>n>>m;
    int ans=m%2;
    for(int i=2;i<=n-1;i++)
    {
        ans=(ans+m)%(i+1);
    }
    cout<<ans<<endl;
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
