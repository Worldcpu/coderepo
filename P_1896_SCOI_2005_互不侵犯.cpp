#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
const int MN=(1<<10)+15;
int isok[MN],attack[MN],cnt1[MN],n,k;
ll ans,f[121][MN][121];
int main(){
    cin>>n>>k;
    int tt=1<<n;
    for(int i=0;i<tt;i++){//i的二进制位表示一列上国王的摆放状态
        isok[i]=((i&(i<<1))==0)&&((i&(i>>1))==0);//状态是否合法
        attack[i]=i|(i<<1)|(i>>1);//攻击范围
        cnt1[i]=cnt1[i>>1]+(i&1);//总共多少个1（国王数量）
    }
    f[0][0][0]=1;
    for(int i=0;i<n;i++){//枚举行数
        for(int j=0;j<tt;j++){//枚举状态
            for(int l=0;l<=k;l++){//枚举放多少个国王
                if(f[i][j][l]){//如果当前位置有放置的话
                    for(int p=0;p<tt;p++){
                        if(isok[p]&&(attack[p]&j)==0){
                            //如果状态合法并且攻击范围不在j的状态表示内
                            f[i+1][p][l+cnt1[p]]+=f[i][j][l];
                            //对下一行执行操作累加答案
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<tt;i++){
        ans+=f[n][i][k];
    }
    cout<<ans;
    return 0;
}