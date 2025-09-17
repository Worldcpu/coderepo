#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6+15;
int st[MN],top,a[MN],b[MN],n,m,K;


int main(){
    cin>>n>>m>>K;
    for(int i=1;i<=n;i++){
        char x;
        cin>>x;
        a[i]=(x-'0');
    }
    for(int i=1;i<=m;i++){
        char x;
        cin>>x;
        b[i]=(x-'0');
    }
    reverse(a+1,a+1+n);
    reverse(b+1,b+1+m);
    st[++top]=max(n,m)+K+1;
    for(int i=max(n,m);i>=1;i--){
        vector<int> tmp;
        for(int j=i,k=K;;){
            tmp.push_back(j);
            while(top&&st[top]<=j) top--;
            int nxt=st[top];
            if(a[j]==1&&b[j]==1&&k){
                a[j]=b[j]=0;
                if(k>=nxt-j) k-=nxt-j;
                else nxt=j+k,k=0;
                a[nxt]++;
                b[nxt]++;
                j=nxt;
            }else if(a[j]==2||b[j]==2){
                a[j+1]+=a[j]>>1;
                b[j+1]+=b[j]>>1;
                a[j]&=1,b[j]&=1;
                j++;
            }else break;
        }
        for(int j=tmp.size()-1;j>=0;j--){
            if(a[tmp[j]]||b[tmp[j]]){
                st[++top]=tmp[j];
            }
        }
    }
    for(n+=K;!a[n];n--);
    for(m+=K;!b[m];m--);
    for(int i=n;i>=1;i--) cout<<a[i];
    cout<<'\n';
    for(int i=m;i>=1;i--) cout<<b[i];

    return 0;
}