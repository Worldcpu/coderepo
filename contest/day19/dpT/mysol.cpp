#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int nxt[MN][2],a[MN],n,ans;

int kua0101(int x){
    int lst=x,ret=0;
    x=nxt[x][1];
    ret+=x-lst;
    lst=x;
    x=nxt[x][0];
    ret+=x-lst;
    lst=x;
    x=nxt[x][1];
    ret+=x-lst;
    x=nxt[x][0];
    ret+=x-lst;
    return ret;
}

int kua101(int x){
    int lst=x,ret=0;
    x=nxt[x][0];
    ret+=x-lst;
    lst=x;
    x=nxt[x][1];
    ret+=x-lst;
    lst=x;
    x=nxt[x][0];
    ret+=x-lst;
    return ret;
}

int kua10(int x){
    int lst=x,ret=0;
    x=nxt[x][0];
    ret+=x-lst;
    lst=x;
    x=nxt[x][1];
    ret+=x-lst;
    return ret;
}

int kua01(int x){
    int lst=x,ret=0;
    x=nxt[x][1];
    ret+=x-lst;
    lst=x;
    x=nxt[x][0];
    ret+=x-lst;
    return ret;
}



int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        --a[i];
    }
    nxt[n+1][0]=nxt[n+1][1]=n+1;
    for(int i=n;i>=1;i--){
        nxt[i][a[i]]=i;
        nxt[i][!a[i]]=nxt[i+1][!a[i]];
    }
    int len=1;
    for(int i=2;i<=n;i++){
        if(a[i]==a[i-1]&&a[i-1]==0){
            ans=max(ans,len+kua0101(i));
        }
        if(a[i]==a[i-1]&&a[i-1]==1){
            ans=max(ans,len+kua101(i));
        }
        if(a[i]!=a[i-1]&&a[i-1]==0){
            ans=max(ans,len+kua101(i));
        }
        if(a[i]!=a[i-1]&&a[i-1]==1){
            ans=max(ans,len+kua01(i));
        }
        if(a[i]==a[i-1]) len++;
        else len=1;
    }
    cout<<ans;
    return 0;
}