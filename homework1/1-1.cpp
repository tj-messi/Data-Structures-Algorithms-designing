#include<iostream>
#include<iomanip>
using namespace std;


int a[100005];
void solve()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    k=k%n;
    for(int i=n-k+1;i<=n;i++)
    {
        cout<<a[i]<<" ";
    }
    for(int i=1;i<=n-k;i++)
    {
        cout<<a[i]<<" ";
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