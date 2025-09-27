#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

int n,m,a[1000005],ok[1000005];
int &ep (int a[],int x,int y) {
    return a[(x-1)*m+y];
}
const int dx[]={0,1,0,-1,0},dy[]={1,0,-1,0,0};
int readAns (InStream &in) {
    int used=0;
    for (int i=1;i<=n;i++) {
        string cur=in.readWord ();
        if (cur.length ()!=m) in.quitf (_wa,"wth is this wasabi");
        for (int j=1;j<=m;j++) {
            char ch=cur[j-1];
            if (ch!='.'&&ch!='0'&&ch!='1') in.quitf (_wa,"wth is %c newbie",ch);
            if (ep (a,i,j)) {
                if (ch=='.') in.quitf (_wa,"no ocean here newbie");
                if (ch=='1') {
                    used++;
                    ep (ok,i,j)=1;
                }
            }
            else {
                if (ch!='.') in.quitf (_wa,"no land here newbie");
            }
        }
    }
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            if (ep (a,i,j)==1) {
                bool flag=0;
                for (int d=0;d<5;d++) {
                    int nx=i+dx[d],ny=j+dy[d];
                    if (1<=nx&&nx<=n&&1<=ny&&ny<=m&&ep (ok,nx,ny)) flag=1; 
                }
                if (!flag) in.quitf (_wa,"we can't see indians here newbie");
            }
        }
    }
    return used;
}
int main (int argc,char *argv[]) {
    registerTestlibCmd(argc, argv);
    n=inf.readInt ();
    m=inf.readInt ();
    int sum=0;
    for (int i=1;i<=n;i++) {
        string cur=inf.readToken ();
        assert (cur.size()==m);
        for (int j=1;j<=m;j++) {
            if (cur[j-1]=='#') ep (a,i,j)=1;
        }
    }
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            if (ep (a,i,j)) {
                sum++;
                for (int d=0;d<4;d++) {
                    int nx=i+dx[d],ny=j+dy[d];
                    if (1>nx||nx>n||1>ny||ny>m||!ep(a,nx,ny)) sum++;
                }
            }
        }
    }
    sum/=5;
    int jans=readAns (ans);
    cerr<<"JANS: "<<jans<<" "<<sum<<'\n';
    if (jans>sum) quitf (_fail,"our newbie problemsetter has too much india on his map");
    if (readAns (ouf)>sum) quitf (_wa,"india territory is too much newbie!!!");
    quitf (_ok,"no more indian cheaters!");
    return 0;
}