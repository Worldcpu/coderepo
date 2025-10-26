#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,nxtp[MN],nxts[MN],ans2;
string st;

void getnxt(int nxt[]){
    nxt[1]=0;
    for(int i=2,j=0;i<=n;i++){
        while(j&&st[j+1]!=st[i]){
            j=nxt[j];
        }
        if(st[j+1]==st[i]) j++;
        nxt[i]=j;
    }
}

bool issame(){
    for(int i=1;i<n;i++){
        if(st[i]!=st[i+1]){
            return 0;
        }
    }
    return 1;
}

bool iscyl(int nxt[],int pos){
    if(nxt[pos]*2<pos) return 0;
    return pos%(pos-nxt[pos])==0;
}

int main(){
    cin>>st;
    n=st.length();
    st=" "+st;
    getnxt(nxtp);
    reverse(st.begin(),st.end());
    st=" "+st;
    getnxt(nxts);

    if(issame()){
        cout<<n<<'\n'<<1<<'\n';
        return 0;
    }
    if(!iscyl(nxtp,n)){
        cout<<1<<'\n'<<1<<'\n';
        return 0;
    }

    for(int i=1;i<n;i++){
        if(!iscyl(nxtp,i)&&!iscyl(nxts,n-i)){
            ans2++;
        }
    }
    cout<<2<<'\n'<<ans2<<'\n';
    

    return 0;
}