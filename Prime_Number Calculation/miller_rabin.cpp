//Think Less do more:-
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp> 
#define ll          unsigned long long
#define pb          push_back
#define setbit(x)   __builtin_popcount(x)
#define scn(t)      scanf("%d",&t);
#define lscn(t)      scanf("%lld",&t);
#define rep(i,a,b)  for(int i=a;i<b;i++)
#define lrep(i,a,b) for(long long i=a;i<b;i++)
// using namespace __gnu_pbds;
using namespace std;
const ll N=1e7+5;
ll mod;
// typedef tree<int, null_type, less<int>, rb_tree_tag, 
//      tree_order_statistics_node_update> pbds;
//
void ap()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    #ifndef ONLINE_JUDGE
	    freopen("input.txt","r",stdin);
	    freopen("output.txt","w",stdout);
	#endif
}
ll mul(ll a,ll b)
{
    ll ans=((__int128)a*b)%mod;

    return ans;
}
ll power(ll x,ll y)
{
    if(y==0)
    return 1;
    
    if(y%2==0)
    return power(mul(x,x)%mod,y/2)%mod;
    else
    return mul(x,power(mul(x,x)%mod,y/2))%mod;
}
vector<ll> miller_prime={2,3,5,7,11,13,17,19,23,29,31,37,41};
bool miller_rabin(ll num)
{
    if(num==1)
    return 0;

    if(num==2 || num==3)
    return 1;

    // other then 2 no other prime is even
    if(num%2==0)
    return 0;

    bool flag=1;

    ll d=num-1;

    ll s=1;

    while(d>0 && d%2==0)
    {
        d=d/2;
        s=s*2;
    }

    mod=num;

    ll s1=s/2;

    for(auto it: miller_prime)
    {
        bool check=1;

        s=s1;

        if((__gcd(it,(ll)num))==1)
        {
            if((power(it,d))%mod==1 || (power(it,d))%mod==mod-1)
            {
                check=0;
                break;
            }

            while(s>1)
            {
                if(power(it,d*(s))==mod-1)
                {
                    check=0;
                    break;
                }

                s=s/2;
            }

            if(check)
            return 0;
        }
    }

    return 1;

    // return true;
}
int main()
{
	int t;
    cin>>t;

    while(t--)
    {
        ll num;
        cin>>num;

        if(miller_rabin(num))
        cout<<"YES"<<endl;
        else
        cout<<"NO"<<endl;
    }
}