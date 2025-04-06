#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pir;
template<typename type>
inline void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

int n;
map<pir,int> m;
struct node{
    int x,y,g,h;
    bool operator<(const node& a)const{
        return h+g>a.g+a.h;
    }
};
priority_queue<node> q;
void update(int x,int y,int g,int h){

    if(x<y) swap(x,y);
    if(x>n*2) return;
    if(x>n&&y==0) return;
    if(x>n&&y>n) return;
    if(x==y) return;
    if(m[pir(x,y)]&&m[pir(x,y)]<g+1+h) return;
    if(n%__gcd(x,y)) return;

    //使用乘法逼近N并统计操作次数
    int newh=0,k=x;
    while(k<n)k*=2,newh++;
    m[pir(x,y)]=g+newh+1;
    q.push({x,y,g+1,newh});
}
void astar(){
    update(1,0,0,0);
    while(!q.empty()){
        node f=q.top();
        q.pop();
        int x=f.x,y=f.y,g=f.g,h=f.h;
        if(f.x==n||f.y==n){//如果达到目标状态
            cout<<f.g-1;
            return;
        }

        //8个状态转移
        update(x,2*y,g,h);
        update(y,2*x,g,h);
        update(x,2*x,g,h);
        update(y,2*y,g,h);
        update(x,x-y,g,h);
        update(y,x-y,g,h);
        update(x,x+y,g,h);
        update(y,x+y,g,h);
    }
}
int main(){
    ios::sync_with_stdio(0);
    read(n);
    astar();
    return 0;
}