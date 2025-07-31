#include<bits/stdc++.h>
#define ll long long
using namespace std;
mt19937 rd(time(0));
const int N=2e5+5;
int n,m,mx[N<<4];
multiset<int> tg[N<<2];
void pushup(int o){
	mx[o]=max(mx[o<<1],mx[o<<1|1]);
	if(tg[o].size())mx[o]=max(mx[o],*--tg[o].end());
}
void update(int o,int l,int r,int x,int y,int v){
	if(x<=l&&r<=y)return tg[o].insert(v),mx[o]=max(mx[o],v),void();
	int mid=(l+r)>>1;
	if(x<=mid)update(o<<1,l,mid,x,y,v);
	if(y>mid)update(o<<1|1,mid+1,r,x,y,v);
	pushup(o);
}
int query(int o,int l,int r,int x,int y){
	if(x<=l&&r<=y)return mx[o];
	int mid=(l+r)>>1,s=-1;
	if(x<=mid)s=max(s,query(o<<1,l,mid,x,y));
	if(y>mid)s=max(s,query(o<<1|1,mid+1,r,x,y));
	if(tg[o].size())s=max(s,*(--tg[o].end()));
	return s;
}
void downtag(int o){
	auto it=--tg[o].end();
	int x=*it;tg[o].erase(it);
	tg[o<<1].insert(x),tg[o<<1|1].insert(x);
	pushup(o<<1),pushup(o<<1|1);
}
void del(int o,int l,int r,int x,int y,int v){
//	cout<<l<<" "<<r<<" "<<mx[o]<<" "<<v<<endl;
	if(mx[o]<v)return ;
	if(x<=l&&r<=y&&(tg[o].size()&&(*--tg[o].end())==v)){
		auto it=tg[o].end();
		it--,tg[o].erase(it),pushup(o);
//		cout<<" "<<l<<" "<<r<<" "<<mx[o]<<endl;
		return ;
	}
	int mid=(l+r)>>1;
	if((tg[o].size()&&(*--tg[o].end())==v))downtag(o);
	if(x<=mid)del(o<<1,l,mid,x,y,v);
	if(y>mid)del(o<<1|1,mid+1,r,x,y,v);
	pushup(o);
//	cout<<l<<" "<<r<<" "<<x<<" "<<y<<" "<<mx[o]<<endl;
}
int main(){
	memset(mx,-1,sizeof(mx));
	freopen("memory.in","r",stdin);
	freopen("memory.ans","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,ty,x,y,z;i<=m;i++){
		scanf("%d",&ty);
		if(ty==1)scanf("%d%d%d",&x,&y,&z),update(1,1,n,x,y,z);
		else if(ty==3)scanf("%d%d",&x,&y),printf("%d\n",query(1,1,n,x,y));
		else {
			scanf("%d%d",&x,&y);
			int v=query(1,1,n,x,y);
			if(v>0)del(1,1,n,x,y,v);
//			cout<<v<<" "<<query(1,1,n,x,y)<<endl;
		}
//		cout<<query(1,1,n,5,6)<<endl;
	}
	return 0;
}
