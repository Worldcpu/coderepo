#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
struct Query{
    int l,r,op,x,id;
}qry[MN];
struct Node{
    int l,r,x,id;
};
int n,m,blen,a[MN],cnt[MN],ans[MN],qtot,lst[MN],mx[MN];
bitset<MN> s1,s2;
vector<Node> qq[MN];

bool cmp(Query x,Query y){
    if((x.l)/blen+1==(y.l)/blen+1){
        return x.r<y.r;
    }else return (x.l)/blen+1<(y.l)/blen+1;
}

void add(int x){
    if(++cnt[a[x]]==1){
        s1[a[x]]=1;
        s2[1e5-a[x]]=1;
    }
}

void del(int x){
    if(--cnt[a[x]]==0){
        s1[a[x]]=0;
        s2[1e5-a[x]]=0;
    }
}

void solve(){
    for(int i=1;i<=316;i++){
        if(qq[i].empty()) continue;
        memset(lst,0,sizeof(lst));
        memset(mx,0,sizeof(mx));
        for(int j=1,p=0;j<=n;j++){
            lst[a[j]]=j;
            if(i*a[j]<=1e5){
                p=max(p,lst[i*a[j]]);
            }
            if(a[j]%i==0) p=max(p,lst[a[j]/i]);
            mx[j]=p;
        }
        for(auto p:qq[i]) ans[p.id]=(p.l<=mx[p.r]);
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
        cin>>op>>l>>r>>x;
        if(op==4&&x<=316){
            qq[x].push_back({l,r,x,i});
        }else qry[++qtot]={l,r,op,x,i};
        
    }
    sort(qry+1,qry+1+qtot,cmp);
    solve();
    int ql=1,qr=0;
    for(int i=1;i<=qtot;i++){
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
            if((s1&(s2>>(1e5-qry[i].x))).any()){
                ans[qry[i].id]=1;
            }
        }else if(qry[i].op==3){
            for(int j=1;j*j<=qry[i].x;j++){
                if((qry[i].x%j)) continue;
                if(s1[j]&&s1[qry[i].x/j]){
                    ans[qry[i].id]=1;
                    break;
                }
            }
        }else{
            if(qry[i].x==0){
                ans[qry[i].id]=(s1[0]&&s1.size()>1);
            }
            else{
                for(int j=1;j*qry[i].x<=1e5;j++){
                    if(s1[j]&&s1[j*qry[i].x]){
                        ans[qry[i].id]=1;
                        break;
                    }
                }
            }
        }
    }
    for(int i=1;i<=m;i++){
        cout<<(ans[i]?"yuno":"yumi")<<'\n';
    }
    return 0;
}