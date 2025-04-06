#include<iostream>
#include<cstring>
using namespace std;
const int MN=1e5+15;
int t[MN],n;
int lowbit(int x){
    return x & -x;
}
void add(int x,int k){
    while (x<=n)
    {
        t[x]+=k;
        x+=lowbit(x);
    }
}
int ask(int x){
    int ans=0;
    while (x>0)
    {
        ans+=t[x];
        x-=lowbit(x);
    }
    return ans;
}
int main(){
    while (1)
    {
        memset(t,0,sizeof(t));
        cin>>n;
        if(!n) break;
        for(int i=1;i<=n;i++){
            int a,b;
            cin>>a>>b;
            add(a,1);
            add(b+1,-1);
        }
        for(int i=1;i<=n;i++){
            cout<<ask(i)<<" ";
        }
        cout<<endl;
    }
    
    return 0;
}