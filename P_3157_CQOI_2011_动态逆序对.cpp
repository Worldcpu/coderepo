#include<bits/stdc++.h>
using namespace std;
const int MN=1e5+15;
struct node{
    int x,y,c;
}a[MN],b[MN];
int n,m,t[MN];
int lowbit(int x){
    return x&-x;
}

void add(int x,int k){
    while (x<=MN)
    {
        t[x]+=k;
        x+=lowbit(x);
    }
}

int query(int x){
    int ret=0;
    while (x)
    {
        ret+=t[x];
        x-=lowbit(x);
    }
}

bool cmp1(node a,node b){
    if(a.x==b.x){
        if(a.y==b.y){
            return a.c<b.c;
        }
        return a.y<b.y;
    }
    return a.x<b.x;
}



int main(){

    return 0;
}