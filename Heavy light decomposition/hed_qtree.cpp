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
#define endl "\n"
// using namespace __gnu_pbds;
using namespace std;
const ll mod=1000000007;
// typedef tree<int, null_type, less<int>, rb_tree_tag, 
//      tree_order_statistics_node_update> pbds;
//
void ap()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // #ifndef ONLINE_JUDGE
	//     freopen("input.txt","r",stdin);
	//     freopen("output.txt","w",stdout);
	// #endif
}
// ###########################################
const int N = 1e4+2;
const int LG = log2(N) + 1;
int n, tim=0;
int a[N], level[N], tin[N], tout[N], rtin[N], nxt[N], sub_size[N], parent[LG][N];
vector<pair<int,int>> v[N];
// apna dfs
// void dfs(int node,int par)
// {
//     for(auto it: v[node])
//     {
//         if(it.first==par)
//         continue;

//         a[it.first]=it.second;

//         dfs(it.first,node);
//     }
// }

//Heavy Light Decomposition

void dfs_hld1(int u, int par, int lvl)
{	
	parent[0][u] = par;
	level[u] = lvl;

	for(auto &it: v[u])
	{
		if(it.first==par)
			continue;

            a[it.first]=it.second;

		dfs_hld1(it.first, u, lvl+1);
	}
}

void dfs_hld2(int u, int par)
{
	sub_size[u] = 1;
	for(auto &it: v[u])
	{
		if(it.first==par)
			continue;

		dfs_hld2(it.first, u);
		sub_size[u] += sub_size[it.first];
		if(sub_size[it.first] > sub_size[v[u][0].first])
			swap(it, v[u][0]);
	}
}

void dfs_hld(int u, int par)
{
	tin[u] = ++tim;
	rtin[tim] = u;
	for(auto &it: v[u])
	{
		if(it.first==par)
			continue;
		nxt[it.first] = (it.first==v[u][0].first ? nxt[u]:it.first);
		dfs_hld(it.first, u);
	}

	tout[u] = tim;
}
// ###################################################################################
//LCA
// ###################################################################################
int walk(int u, int h)
{
	for(int i=LG-1;i>=0;i--)
	{
		if((h>>i) & 1)
			u = parent[i][u];
	}
	return u;
}

void precompute()
{
	for(int i=1;i<LG;i++)
		for(int j=1;j<=n;j++)
				parent[i][j]=parent[i-1][parent[i-1][j]];
}

int LCA(int u, int v)
{
	if(level[u]<level[v])
		swap(u,v);
	int diff=level[u]-level[v];
	for(int i=LG-1;i>=0;i--)
	{
		if((1<<i) & diff)
		{
			u=parent[i][u];
		}
	}
	if(u==v)
		return u;
	for(int i=LG-1;i>=0;i--)
	{
		if(parent[i][u] && parent[i][u]!=parent[i][v])
		{
			u=parent[i][u];
			v=parent[i][v];
		}
	}
	return parent[0][u];
}

int dist(int u, int v)
{
	return level[u] + level[v] - 2 * level[LCA(u, v)];
}
// #############################################################################
//Segment Tree code for hld
// #############################################################################
int seg_tree[4*N];

void build(int node, int L, int R)
{
	if(L==R)
	{
		seg_tree[node]=a[rtin[L]];
		return;
	}

	int M=(L+R)/2;
	build(node*2, L, M);
	build(node*2+1, M+1, R);

	seg_tree[node]=max(seg_tree[node*2], seg_tree[node*2+1]);
}

// void propagate(int node, int L, int R)
// {	
// 	if(L!=R)
// 	{
// 		lazy[node*2]+=lazy[node];
// 		lazy[node*2+1]+=lazy[node];
// 	}
// 	seg_tree[node]+=lazy[node];
// 	lazy[node]=0;
// }

int query(int node, int L, int R, int i, int j)
{
	// if(lazy[node])
	// 	propagate(node, L, R);
	if(j<L || i>R)
		return 0;

	if(i<=L && R<=j)
		return seg_tree[node];

	int M=(L+R)/2;
	int left=query(node*2, L, M, i, j);
	int right=query(node*2 + 1, M+1, R, i, j);
	return max(left, right);
}

// void update(int node, int L, int R, int i, int j, int val)
// {
// 	// if(lazy[node])
// 	// 	propagate(node, L, R);

// 	if(j<L || i>R)
// 		return;

// 	if(i<=L && R<=j)
// 	{
// 		lazy[node]+=val;
// 		// propagate(node, L, R);
// 		return;
// 	}
// 	int M=(L+R)/2;
// 	update(node*2, L, M, i, j, val);
// 	update(node*2 + 1, M+1, R, i, j, val);
// 	seg_tree[node]=max(seg_tree[node*2], seg_tree[node*2 + 1]);
// }
//$$$$$$$$$$$$$$$$$$ for point update
void update(int node, int L, int R, int ind, int val)
{
    if(L==R)
    {
        seg_tree[node]=val;
        return ;
    }

	int M=(L+R)/2;

    if(ind<=M)
	update(node*2, L, M,ind, val);
    else
	update(node*2 + 1, M+1, R, ind, val);

	seg_tree[node]=max(seg_tree[node*2], seg_tree[node*2 + 1]);
}

// void upd(int l, int r, int val)
// {
// 	update(1, 1, n, l, r, val);
// }

int get(int l, int r)
{
	return query(1, 1, n, l, r);
}
//Utility Functions

int query_up(int x, int y) //Assuming Y is an ancestor of X
{
	int res = 0;
	while(nxt[x] != nxt[y])
	{
		res = max(res,get(tin[nxt[x]], tin[x]));
		x = parent[0][nxt[x]];
	}
	res = max(res,get(tin[y] + 1, tin[x])); //use tin[y] to include Y
	return res;
}

int query_hld(int x, int y)
{
	int lca = LCA(x, y);
	int res = max(query_up(x, lca), query_up(y, lca));
	return res;
}

// void update_up(int x, int y, int val) //Assuming Y is an ancestor of X
// {
// 	while(nxt[x] != nxt[y])
// 	{
// 		upd(tin[nxt[x]], tin[x], val);
// 		x = parent[0][nxt[x]];
// 	}
// 	upd(tin[y] + 1, tin[x], val); //use tin[y] to include Y
// }

// void update_hld(int x, int y, int val)
// {
// 	int lca = LCA(x, y);
// 	update_up(x, lca, val);
// 	update_up(y, lca, val);
// }

void hld()
{
	dfs_hld1(1, 0, 1);
	dfs_hld2(1, 0);
	dfs_hld(1, 0);
	precompute();
	build(1, 1, n);
}
// ###########################################
int main()
{
    ap();

    int t;
    cin>>t;

    while(t--)
    {
        tim = 0;

        int node;
        cin>>node;

        n=node;

        for(int i=0;i<=node;i++)
        {
            v[i].clear();
        }

        vector<pair<int,int>> uts;

        for(int i=0;i<node-1;i++)
        {
            int a,b,c;
            cin>>a>>b>>c;

            v[a].pb({b,c});
            v[b].pb({a,c});

            uts.pb({a,b});
        }

        // dfs(1,0);

        hld();

        while(1)
        {
            string s;
            cin>>s;

            if(s=="DONE")
            break;

            if(s=="QUERY")
            {
                int a,b;
                cin>>a>>b;

                cout<<query_hld(a,b)<<endl;
            }
            else
            {
                int a,b;
                cin>>a>>b;

                int ind;

                int u=uts[a-1].first;
                int v=uts[a-1].second;

                if(level[u]<level[v])
                ind=v;
                else
                ind=u;

                update(1,1,n,tin[ind],b);
            }
        }
    }
}