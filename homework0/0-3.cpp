#include<iostream>
#include<iomanip>
#include<istream>
#include<string>
using namespace std;
 
void solve()
{
    while(1)
    {
        string s;
        getline(cin,s);
        if(s[0]=='#')break;
        int ans=0;
        for(int i=0;i<=s.size()-1;i++)
        {
            if(s[i]>='A'&&s[i]<='Z')
            {
                ans+=(s[i]-'A'+1)*(i+1);
            }
        }
        cout<<ans<<endl;
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