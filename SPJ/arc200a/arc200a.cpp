#include "../testlib.h"
#include <bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
int n,a[MN],b[MN];

// 1-> No 0-> Yes and ok -1 -> Yes but invaild -2 -> invaild output
int getans(InStream &it){
    string qwq=it.readToken();
    if(qwq=="No") return 1;
    else if(qwq!="Yes") return -2;

    long long ansa=0,ansb=0;
    for(int i=1;i<=n;i++){
        int x=it.readInt(-100000000,100000000,"x[i]");
        ansa+=1ll*x*a[i];
        ansb+=1ll*x*b[i];
    }
    if(ansa>0&&ansb<0) return 0;
    return -1;
}

void solve(){
    n=inf.readInt(1,200000,"n");
    for(int i=1;i<=n;i++){
        a[i]=inf.readInt(1,200000,"a[i]");
    }
    for(int i=1;i<=n;i++){
        b[i]=inf.readInt(1,200000,"b[i]");
    }
    int stans=getans(ans),stouf=getans(ouf);
    if(stans==-1){
        quitf(_fail,"Jury says Yes but its answer invalid!");
    }else if(stans==-2){
        quitf(_fail,"Jury's answer format incorrect: expected 'Yes' or 'No', got invaild output");
    }

    if(stans==-1){
        quitf(_wa,"Participant says Yes but its answer invalid!");
    }else if(stans==-2){
        quitf(_wa,"Participant's answer format incorrect: expected 'Yes' or 'No', got invaild output");
    }
    if(stans==1&&stouf==0){
        quitf(_fail,"Jury claims no answer exists, but participant found one");
    }
    if(stans==0&&stouf==1){
        quitf(_wa,"Jury found a valid answer, but participant output 'No'");
    }
}

int main(int argc,char *argv[]){
    registerTestlibCmd(argc,argv);
    int T;
    T=inf.readInt(1,200000,"T");
    while(T--){
        solve();
    }
    quitf(_ok,"All testcases passed.");



    return 0;
}
