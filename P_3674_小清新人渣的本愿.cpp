#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
struct Query{
    int l,r,op,x,id;
}qry[MN];
int n,m,blen,a[MN],cnt[MN],ans[MN];
bitset<MN> s1,s2;

bool cmp(Query x,Query y){
    if((x.l-1)/blen+1==(y.l-1)/blen+1){
        return x.r<y.r;
    }else return (x.l-1)/blen+1<(y.l-1)/blen+1;
}

void add(int x){
    if(++cnt[a[x]]==1){
        s1[a[x]]=1;
        s2[MN-a[x]]=1;
    }
}

void del(int x){
    if(--cnt[a[x]]==0){
        s1[a[x]]=0;
        s2[MN-a[x]]=0;
    }
}

int main(){
    cin>>n>>m;
    blen=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        int op,l,r,x;
        cin>>qry[i].op>>qry[i].l>>qry[i].r>>qry[i].x;
        qry[i].id=i;
    }
    sort(qry+1,qry+1+m,cmp);
    int ql=1,qr=0;
    for(int i=1;i<=m;i++){
        while(qr<=n&&qr<qry[i].r){
            add(++qr);
        }
        while(qr&&qr>qry[i].r){
            del(qr--);
        }
        while(ql&&ql>qry[i].l){
            add(--ql);
        }
        while(ql<=n&&ql<qry[i].l){
            del(ql++);
        }
        if(qry[i].op==1){
            if((s1&(s1<<qry[i].x)).any()){
                ans[qry[i].id]=1;
            }
        }else if(qry[i].op==2){
            if((s1&(s2>>(MN-qry[i].x))).any()){
                ans[qry[i].id]=1;
            }
        }else{
            for(int j=1;j*j<=qry[i].x;j++){
                if((qry[i].x%j)) continue;
                if(s1[j]&&s1[qry[i].x/j]){
                    ans[qry[i].id]=1;
                    break;
                }
            }
        }
    }
    for(int i=1;i<=m;i++){
        cout<<(ans[i]?"hana":"bi")<<'\n';
    }
    return 0;
}