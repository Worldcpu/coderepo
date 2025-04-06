#include<bits/stdc++.h>
#define ls t[p].l
#define rs t[p].r
#define ull unsigned long long
using namespace std;
const int P=131,MN=1e5+15;
string s;
ull hp[MN];
struct fhqtreap{
    int l,r,dat,siz;
    ull hsh;
    int c;
}t[MN];
int root,tot,m,len;

void init(){
    hp[0]=1;
    for(int i=1;i<MN;i++){
        hp[i]=hp[i-1]*P;
    }
}

int newnode(int k){
    tot++;
    memset(&t[tot],0,sizeof(t[tot]));
    t[tot].siz=1;
    t[tot].hsh=t[tot].c=k;
    t[tot].dat=rand();
    return tot;
}

void pushup(int p){
    t[p].siz=t[ls].siz+t[rs].siz+1;
    t[p].hsh=t[ls].hsh*hp[t[rs].siz+1]+t[p].c*hp[t[rs].siz]+t[rs].hsh;
}

void split(int p,ull k,int &x,int &y){
    if(!p){
        x=y=0;
        return;
    }
    if(k>t[ls].siz){
        x=p;
        k-=t[ls].siz+1;
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
        t[x].r=merge(t[x].r,y);
        pushup(x);
        return x;
    }else{
        t[y].l=merge(x,t[y].l);
        pushup(y);
        return y;
    }
}

void insert(int pos,int k){
    int x,y;
    split(root,pos,x,y);
    root=merge(merge(x,newnode(k)),y);
}

void getqj(int fl,int fr, int &x, int &y, int &z)
{
    split(root, fr, x, z);
    split(x, fl - 1, x, y);
}

void getqjl(int k, int tott, int &x, int &y, int &z)
{
    int l = k, r = k + tott - 1;
    split(root, r, x, z);
    split(x, l - 1, x, y);
}

ull queryhsh(int k,int len){
    int x,y,z;
    ull ans;
    getqjl(k,len,x,y,z);
    ans=t[y].hsh;
    root=merge(merge(x,y),z);
    return ans;
}

bool query(int x,int y,int len){
    return queryhsh(x,len)==queryhsh(y,len);
}

int main(){
    init();
    cin>>s;
    len=s.length();
    for(int i=0;i<s.size();i++){
        root=merge(root,newnode(s[i]-'a'));
    }
    cin>>m;
    while (m--)
    {
        char op,p;
        int x,y;
        cin>>op;
        if(op=='Q'){
            cin>>x>>y;
            if(x>y) swap(x,y);
            int l=1,r=t[root].siz-y+1;
            while(l<=r){
                int mid=l+r>>1;
                if(query(x,y,mid)) l=mid+1;
                else r=mid-1;
            }
            cout<<r<<'\n';
        }else if(op=='I'){
            cin>>x>>p;
            insert(x,p-'a');
        }else{
            int pos;
            cin>>pos>>p;
            int x,y,z;
            split(root,pos,x,z);
            split(x,pos-1,x,y);
            t[y].hsh=t[y].c=p-'a';
            root=merge(merge(x,y),z);
        }
    }
    
    return 0;
}