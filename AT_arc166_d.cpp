#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
int n,x[MN],y[MN],ans=INF;
priority_queue<pir,vector<pir>,greater<pir>> q;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i];
    }
    for(int i=1;i<=n;i++){
        cin>>y[i];
    }

    x[0]=-INF,x[n+1]=INF;
    for(int i=1;i<=n;i++){
        if(y[i]>y[i-1]){
            q.push(pir(i,y[i]-y[i-1]));
        }else if(y[i]<y[i-1]){
            int tmp=y[i-1]-y[i];
            while(tmp){
                auto tp=q.top();
                q.pop();
                int qwq=min(tmp,tp.second);
                tp.second-=qwq;
                tmp-=qwq;
                ans=min(ans,(x[i]-1)-(x[tp.first-1]+1));
                if(tp.second){
                    q.push(tp);
                }
            }
        }
    }
    cout<<(ans==INF?-1:ans);
    return 0;
}