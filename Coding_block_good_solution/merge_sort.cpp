//Think Less do more:-
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp> 
#define ll          long long
#define pb          push_back
#define setbit(x)   __builtin_popcount(x)
#define scn(t)      scanf("%d",&t);
#define lscn(t)      scanf("%lld",&t);
#define rep(i,a,b)  for(int i=a;i<b;i++)
#define lrep(i,a,b) for(long long i=a;i<b;i++)
#define endl        "\n"
// using namespace __gnu_pbds;
using namespace std;
const ll N=1e7+5;
const ll mod=1000000007;
// typedef tree<int, null_type, less<int>, rb_tree_tag, 
//      tree_order_statistics_node_update> pbds;
//
ll ans=0;
void merge(int arr[],int st,int end)
{
    int temp[end-st+1];

    int mid=(st+end)/2;

    int x=st,y=mid+1;
    int ind=0;

    while(x<=mid && y<=end)
    {
        if(arr[x]<=arr[y])
        {
            temp[ind++]=arr[x++];
        }
        else
        {
            ans=ans+(ll)arr[y]*(mid-x+1);
            temp[ind++]=arr[y++];
        }
    }
    
    while(x<=mid)
    temp[ind++]=arr[x++];
    
    while(y<=end)
    temp[ind++]=arr[y++];
    
    for(int i=st;i<=end;i++)
    {
        arr[i]=temp[i-st];
    }
}
void merge_sort(int arr[],int st,int end)
{
    if(st>=end)
        return ;

    int mid=(st+end)/2;

    merge_sort(arr,st,mid);
    merge_sort(arr,mid+1,end);

    merge(arr,st,end);
}
int main()
{
    // #ifndef ONLINE_JUDGE
    //     freopen("input.txt","r",stdin);
    //     freopen("output.txt","w",stdout);
    // #endif

    int t;
    t=1;

    while(t--)
    {
        int n;
        scn(n);

        int arr[n];

        for(int i=0;i<n;i++)
            scn(arr[i]);

	    for(int i=0;i<n/2;i++)
		{
			swap(arr[i],arr[n-1-i]);
		}

        ans=0;

        merge_sort(arr,0,n-1);

        cout<<ans<<endl;
    }
}