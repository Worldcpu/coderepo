#include<bits/stdc++.h>
#define pir pair<double,double>
using namespace std;
constexpr int MN=2501;
constexpr double eps=1e-8;
double p[MN],q[MN];
double f,pref;
int n,a,b;

pir check(double ka,double kb){
    pref=0;
    int cnta=0,cntb=0;
    for(int i=1;i<=n;i++){
        //pref即f[i-1]
        f=max({pref,pref+p[i]-ka,pref+q[i]-kb,pref+p[i]+q[i]-p[i]*q[i]-ka-kb});
        if(f-(pref+p[i]-ka)<eps){
            cnta++;
        }else if(f-(pref+q[i]-kb)<eps) cntb++;
        else if(f-(pref+p[i]+q[i]-p[i]*q[i]-ka-kb)<eps){
            cnta++;
            cntb++;
        }
        pref=f;
    }
    return pir(cnta,cntb);
}

int main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        cin>>q[i];
    }
    double la=0,ra=1,lb,rb,mida,midb;
    while(la+eps<ra){//先a
        mida=(la+ra)/2;
        lb=0,rb=1;
        pir ansb;
        while(lb+eps<rb){// 后b
            midb=(lb+rb)/2;
            ansb=check(mida,midb);
            if(ansb.second>b) lb=midb;
            else if(ansb.second<b)rb=midb;
            else break;//如果找到了就退出
        }
        if(ansb.first>a) la=mida;
        else if(ansb.first<a)ra=mida;
        else break;
    }
    cout<<f+mida*a+midb*b;//因为我们取最小，h(i)是减去k，这里要加上
    return 0;
}