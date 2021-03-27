#include <bits/stdc++.h>
#define ll          long long
#define pb          push_back
#define vec         vector<int>
#define map         map<int,int>
#define x           first
#define y           second
#define scn(t)      scanf("%d",&t);
#define lscn(t)      scanf("%lld",&t);
#define mod         1000000007
#define rep(i,a,b)  for(int i=a;i<b;i++)
#define endl        "\n"
using namespace std;
struct util
{
    int l,r,ans,idx;
};
int cnt=0;
unordered_map<int,int> mp; 
int arr[100005];
util brr[100005];
int b_size;
int comp1(util a,util b)
{
    int a1=a.l/b_size;
    int b1=b.l/b_size;
    
    if(a1==b1)
    return a.r<b.r;
    else
    return a.l<b.l;
}
bool comp2(util a,util b)
{
    if(a.idx<b.idx)
    return true;
    else
    return false;
}
void add(int ind)
{
    if(mp[arr[ind]]==arr[ind])
    {
        cnt--;
        mp[arr[ind]]++;
    }
    else
    {
        mp[arr[ind]]++;
        if(mp[arr[ind]]==arr[ind])
        cnt++;
    }
}
void rem(int ind)
{
    if(mp[arr[ind]]==arr[ind])
    {
        cnt--;
        mp[arr[ind]]--;
    }
    else
    {
        mp[arr[ind]]--;
        if(mp[arr[ind]]==arr[ind])
        cnt++;
    }
}
int main()
{
    int n;
    scn(n);
    
    int q;
    scn(q);
    
    rep(i,0,n)
    scn(arr[i]);
    b_size=sqrt(n);
    rep(i,0,q)
    {
        brr[i].idx=i;
        scn(brr[i].l);
        scn(brr[i].r);
        brr[i].l--;
        brr[i].r--;
    }
    
    sort(brr,brr+q,comp1);
    
    int l1=0,r1=-1;
    for(int i=0;i<q;i++)
    {
        while(r1<brr[i].r)
        {
            r1++;
            add(r1);
        }
        while(r1>brr[i].r)
        {
            rem(r1);
            r1--;
        }
        while(l1<brr[i].l)
        {
            rem(l1);
            l1++;
        }
        while(l1>brr[i].l)
        {
            l1--;
            add(l1);
        }
        
        brr[i].ans=cnt;
    }
    sort(brr,brr+q,comp2);
    rep(i,0,q)
    printf("%d\n",brr[i].ans);
}


// question link - https://codeforces.com/contest/220/problem/B