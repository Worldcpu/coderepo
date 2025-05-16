#include<bits/stdc++.h>
#define ls t[p].lson
#define rs t[p].rson
using namespace std;
constexpr int MN=5e4+15;
struct Point{
    int x[3],w;
}pt[MN];
struct Node{
    int l:son,rson;
    int L[3],R[3];
}t[MN];
struct Query{
    int x[4];
}qry[MN];
int n,s[MN],top,tot,id[MN];

int add(){
    if(!top) return ++tot;
    return s[top--];
}

void pushup(int p){
    t[p].
}

int build(int l,int r,int k){
    if(l>r) return 0;
    int mid=(l+r)>>1,p;
    nth_element(id+l,id+mid,id+r+1,[&](int x,int y){
            return pt[x].x[k]<pt[y].x[k];
    });
    p=id[mid];
    ls=build(l,mid-1,(k+1)%3);
    rs=build(mid+1,r,(k+1)%3);
    pushup(p);
}

int main(){

    return 0;
}
