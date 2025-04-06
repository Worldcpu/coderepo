#include<bits/stdc++.h>
using namespace std;
const int PY=400,MN=801;
int a[MN],b[MN],f[MN][MN],pre[201][MN][MN];
int n,m;

void getans(int i,int j,int k){
    vector<int> ans;
    int ans1=0,ans2=0;
    while (j)
    {
        if(pre[i][j][k]==pre[i-1][j][k]){
            i--;
        }else{
            ans.push_back(i);
            ans1+=a[i];
            ans2+=b[i];
            j--;
            k-=(a[i]-b[i]);
            i--;
        }
    }
    cout<<"Best jury has value "<<ans1<<" for prosecution and value "<<ans2<<" for defence:\n ";
    for(int i=ans.size()-1;i>=0;i--){
        cout<<ans[i]<<" ";
    }
    cout<<"\n\n";
}


int main(){
    int cnt=0;
    while (1)
    {
        cnt++;
        cin>>n>>m;
        if(!n&&!m){
            break;
        }
        cout<<"Jury #"<<cnt<<'\n';
        for(int i=1;i<=n;i++){
            cin>>a[i]>>b[i];
        }
        memset(f,128,sizeof(f));
        f[0][400]=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){
                for(int k=0;k<=800;k++){
                    pre[i][j][k]=pre[i-1][j][k];
                }
            }
            for(int j=m;j>=1;j--){
                for(int k=0;k<=800;k++){

                    if(k-(a[i]-b[i])>=0&&k-(a[i]-b[i])<=800&&f[j][k]<f[j-1][k-(a[i]-b[i])]+a[i]+b[i]){
                        f[j][k]=f[j-1][k-(a[i]-b[i])]+a[i]+b[i];
                        pre[i][j][k]=i;
                    }
                }
            }
        }
        for(int i=0;i<=400;i++){
            if(f[m][400-i]>=0||f[m][400+i]>=0){
                if(f[m][400-i]>f[m][400+i]){
                    getans(n,m,400-i);
                    break;
                }else{
                    getans(n,m,400+i);
                    break;
                }
            }
        }
    }
    
    return 0;
}