#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef long long ll;

typedef pair<ll,int> pii;

typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ost;

#define mid (b+e)/2

const int sz=300005,oo=1<<30;

ost mst[sz*4];

ll ara[sz];
int n,q,k=1;

void combine(int node,int left,int right)
{
	for(auto x:mst[left]){
		mst[node].insert({x.first,k++});
	}

	for(auto x:mst[right]){
		mst[node].insert({x.first,k++});
	}
}

void build(int node,int b,int e)
{
	if(b==e){
		mst[node].insert({ara[b],k++});
		return;
	}
	build(node*2,b,mid);
	build(node*2+1,mid+1,e);
	combine(node,node*2,node*2+1);
}

int query(int node,int b,int e,int l,int r,int val)
{
	if(b>r || e<l) return 0;

	if(b>=l && e<=r){
		return mst[node].order_of_key({val,0});
	}
	return query(node*2,b,mid,l,r,val)+query(node*2+1,mid+1,e,l,r,val);
}

void update(int node,int b,int e,int pos,ll val)
{
	if(b>pos || e<pos) return;
	mst[node].erase(mst[node].lower_bound({ara[pos],0}));
	mst[node].insert({val,k++});
	if(b>=pos && e<=pos){
		ara[pos]=val;
		return;
	}
	update(node*2,b,mid,pos,val);
	update(node*2+1,mid+1,e,pos,val);
}


int main()
{
    ll u;
	cin>>n>>q>>u;

	for(int i=1;i<=n;i++){
		cin>>ara[i];
	}

	build(1,1,n);

	char cmd;
	int l,r,v,p;

	while(q--){
		cin>>l>>r>>v>>p;
        int ans=query(1,1,n,l,r,v);
        update(1,1,n,p,(u*ans)/(r-l+1));
        ara[p]=(u*ans)/(r-l+1);
	}


	for(int i=1;i<=n;i++){
        cout<<ara[i]<<endl;
	}





}
