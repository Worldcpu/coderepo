#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
struct Node{
    int val,id;
}a[MN];
int K,n;

bool cmp(Node x,Node y){
    return x.val<y.val;
}

int main(){
    cin>>K;
    n=3*K;
    for(int i=1;i<=n;i++){
        cin>>a[i].val;
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=K;i++){
        cout<<a[i].id<<'\n';
    }
    while(1){
        random_shuffle(a+K+2,a+n+1);
        int ans=0,cnt=0,re=500*K;
        for(int i=K+1;i<=2*K;i++){
            ans+=a[i].val;
            if(ans>re){
                cnt++;
                break;
            }
        }
        ans=0;
        for(int i=2*K+1;i<=n;i++){
            ans+=a[i].val;
            if(ans>re){
                cnt++;
                break;
            }
        }
        if(cnt==2){
            for(int i=K+1;i<=n;i++){
                cout<<a[i].id<<'\n';
            }
            break;
        }
    }

    return 0;
}
