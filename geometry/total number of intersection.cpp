			//If you have nothing then you have opportunity to do the  best
#include <bits/stdc++.h>
#define ll          long long
#define pb          push_back
#define scn(t)      scanf("%d",&t);
#define lscn(t)      scanf("%lld",&t);
#define rep(i,a,b)  for(ll i=a;i<b;i++)
#define endl        "\n"
using namespace std;
const ll N=4e5+5;
int bit[N];
void update(int ind,int val)
{
	for(;ind<N;ind+=(ind&(-ind)))
	bit[ind]+=val;
}
int query(int ind)
{
	int sum=0;
	for(;ind>0;ind-=(ind&(-ind)))
	sum=sum+bit[ind];

	return sum;
}
int main()
{
	int n;
	scn(n);

	map<int,vector<pair<int,int>>> mpx;
	map<int,vector<pair<int,int>>> mpx1;
	map<int,vector<pair<int,int>>> mpy;

	for(int i=0;i<n;i++)
	{
		int x1,x2,y1,y2;
		cin>>x1>>y1>>x2>>y2;

		if(x1==x2)
		{
			mpx[x1].push_back({min(y1,y2),max(y1,y2)});
		}
		else
		{
			mpy[y1].push_back({min(x1,x2),max(x1,x2)});
		}
	}

	for(auto& it: mpx)
	{
		sort(it.second.begin(),it.second.end());
	}

	for(auto& it: mpy)
	{
		sort(it.second.begin(),it.second.end());
	}

	for(auto& it: mpx)
	{
		int st=0,sz=it.second.size();

		for(int i=0;i<sz;i++)
		{
			if(i==0)
			{
				continue;
			}
			else
			{
				if(it.second[i].first<=it.second[st].second)
				{
					it.second[st].second=max(it.second[st].second,it.second[i].second);
				}
				else
				{
					it.second[++st]=it.second[i];
					
				}
			}
		}

		it.second.resize(st+1);
	}

	for(auto& it: mpy)
	{
		int st=0,sz=it.second.size();

		for(int i=0;i<sz;i++)
		{
			if(i==0)
			{
				continue;
			}
			else
			{
				if(it.second[i].first<=it.second[st].second)
				{
					it.second[st].second=max(it.second[st].second,it.second[i].second);
				}
				else
				{
					it.second[++st]=it.second[i];
				}
			}
		}

		it.second.resize(st+1);
	}

	ll ans=0;

	map<int,int> mp;

	for(auto it: mpy)
	{
		mp[it.first]=1;
		for(auto it1: it.second)
		{
			ans=ans+(ll)(it1.second-it1.first)+1;
			mp[it1.first]=1;
			mp[it1.second]=1;
		}
	}

	for(auto it: mpx)
	{
		mp[it.first]=1;
		for(auto it1: it.second)
		{
			mp[it1.first]=1;
			mp[it1.second]=1;
			ans=ans+(ll)(it1.second-it1.first)+1;
		}
	}

	int cnt=2;
	for(auto it: mp)
	{
		mp[it.first]=cnt++;
	}

	vector<int> v[N];

	for(auto it: mpy)
	{
		for(auto it1: it.second)
		{
			v[mp[it1.first]].pb(mp[it.first]);
			v[mp[it1.second]+1].pb(-mp[it.first]);
		}
	}

	ll ans1=0;

	for(auto it: mpx)
	{
		for(auto it1: it.second)
		{
			mpx1[mp[it.first]].pb({mp[it1.first],mp[it1.second]});
		}
	}

	for(int i=1;i<N;i++)
	{
		for(auto it: v[i])
		{
			if(it>0)
			update(it,1);
			else
			update(abs(it),-1);
		}

		for(auto it: mpx1[i])
		{
			ans1=ans1+(query(it.second)-query(it.first-1));
		}
	}

	cout<<ans-ans1<<endl;
}



// link====https://codeforces.com/contest/610/problem/D