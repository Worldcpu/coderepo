#include<bits/stdc++.h>
using namespace std;
const int MN=4200000+1145;

int f[MN],num[MN],w[MN],v[MN],tot,sum;
bool flag=0;
int main(){
    
    while(1)
    {
        tot=0;
        flag=0;
        sum=0;
        memset(f,0,sizeof(f));
        for(int i=1;i<=6;i++){
            cin>>num[i];
            sum+=i*num[i];
        }
        if(sum==0) break;
        if(sum%2!=0){
            cout<<"Can't\n";
            continue;
        }
        for(int i=1;i<=6;i++){
            if(num[i]>0){ 
                for(int j=1;j<=num[i];j<<=1){
                    tot++;
                    w[tot]=j*i;
                    v[tot]=j;
                    num[i]-=j;
                }
                if(num[i]){
                    tot++;
                    w[tot]=num[i]*i;
                    v[tot]=num[i];
                }
            }
        }
        for(int i=1;i<=tot;i++){
            for(int j=sum/2;j>=w[i];j--){
                if(f[j])
            }
        }
        if(!f[sum/2]){
            cout<<"Can't\n";
        }else cout<<"Can\n";
    }
    
    return 0;
}