#include<iostream>
#include<cstring>
#include<algorithm>
#define ls t[p].l
#define rs t[p].r
using namespace std;
constexpr int MN=1e6+15;
template<typename type>
inline void read(type &x)
{
	x=0;bool flag(0);char ch=getchar();
	while(!isdigit(ch)) flag=ch=='-',ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	flag?x=-x:0;
}
struct fhqtree{
	int l,r,dat,val,size;
	int sum,mpre,covnum,mback,msum;
	bool rev,iscov;
}t[MN];
int n,m,tot,root;
int gcstack[MN],top;
int newnode(int k){
	int i=top?gcstack[top--]:++tot;
	memset(&t[i],0,sizeof(t[i]));
	t[i].dat=rand();
	t[i].sum=t[i].msum=t[i].val=k;
	t[i].mpre=t[i].mback=max(0,k);
	t[i].size=1;
	return i;
}
void gc(int p){
	if(!p) return;
	gcstack[++top]=p;
	gc(ls);
	gc(rs);
}

void doreverse(int p){
	if(!t[p].rev) return;
	
	swap(t[p].mpre,t[p].mback);
	swap(t[p].l,t[p].r);
	
	t[ls].rev^=1;
	t[rs].rev^=1;
	t[p].rev=0;
}

void docover(int p){
	if(!t[p].iscov) return;
	
	int c=t[p].covnum,cs=t[p].size*c;
	
	t[p].val=c;
	t[p].sum=cs;
	t[p].msum=max(c,cs);
	t[p].mpre=t[p].mback=max(cs,0);
	
	t[ls].iscov=t[rs].iscov=1;
	t[ls].covnum=t[rs].covnum=c;
	
	t[p].covnum=t[p].iscov=0;
}

void pushup(int p){
	t[p].size=t[ls].size+t[rs].size+1;
	t[p].sum=t[ls].sum+t[p].val+t[rs].sum;
	t[p].mpre=max({t[ls].mpre,t[ls].sum+t[p].val+t[rs].mpre,0});
	t[p].mback=max({t[rs].mback,t[rs].sum+t[p].val+t[ls].mback,0});
	t[p].msum=max(t[p].val,t[ls].mback+t[p].val+t[rs].mpre);
	if(ls){
		t[p].msum=max(t[p].msum,t[ls].msum);
	}
	if(rs){
		t[p].msum=max(t[p].msum,t[rs].msum);
	}
}

void pushdown(int p){
	if(!p) return;
	docover(p);
	doreverse(p);
	
	if(ls){
		docover(ls);
		doreverse(ls);
	}
	if(rs){
		docover(rs);
		doreverse(rs);
	}
}

void split(int p,int k,int &x,int &y){
	if(!p){
		x=y=0;
		return;
	}
	pushdown(p);
	if(k>t[ls].size){
		x=p;
		k-=t[ls].size+1;
		split(rs,k,rs,y);
	}else{
		y=p;
		split(ls,k,x,ls);
	}
	pushup(p);
}

int merge(int x,int y){
	if(!x||!y){
		return x+y;
	}
	if(t[x].dat<t[y].dat){
		pushdown(x);
		t[x].r=merge(t[x].r,y);
		pushup(x);
		return x;
	}else{
		pushdown(y);
		t[y].l=merge(x,t[y].l);
		pushup(y);
		return y;
	}
}

void getqj(int k,int tott,int &x,int &y,int &z){
	int l=k,r=k+tott-1;
	split(root,r,x,z);
	split(x,l-1,x,y);
}

int toinsert[MN];
int build(int l,int r){
	if(l==r){
		return newnode(toinsert[l]);
	}
	int mid=l+r>>1;
	return merge(build(l,mid),build(mid+1,r));
}

void plinsert(int k,int tott){
	int x,y,z;
	split(root,k,x,z);
	y=build(1,tott);
	root=merge(merge(x,y),z);
}

void del(int k,int tott){
	int x,y,z;
	getqj(k,tott,x,y,z);
	gc(y);
	root=merge(x,z);
}

void pushback(int k){
	root=merge(root,newnode(k));
}

int getmsum(int fl,int fr){
	int x,y,z;
    getqj(fl,fr-fl+1,x,y,z);
    int ans=t[y].msum;
    root=merge(merge(x,y),z);
    return ans;
}

void reverse(int k,int tott){
	int x,y,z;
	getqj(k,tott,x,y,z);
	t[y].rev^=1;
	doreverse(y);
	root=merge(merge(x,y),z);
}

void cover(int k,int tott,int cv){
	int x,y,z;
	getqj(k,tott,x,y,z);
	t[y].iscov=1;
	t[y].covnum=cv;
	docover(y);
	root=merge(merge(x,y),z);
}

int change(int fx,int k){
    int x,y,z;
    getqj(fx,1,x,y,z);
    t[y].val=k;
            
}

int getsum(int k,int tott){
	int x,y,z;
	getqj(k,tott,x,y,z);
	int ans=t[y].sum;
	root=merge(merge(x,y),z);
	return ans;
}

int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int tmp;
		cin>>tmp;
		pushback(tmp);
	}
    int op,x,y;
	while(m--){
		cin>>op>>x>>y;
        if(x>y) swap(x,y);
        if(op==1){
            cout<<getmsum(x,y)<<'\n';
        }else 
	}
	return 0;
}