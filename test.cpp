#include <bits/stdc++.h>
using namespace std;

/*********************** Test 1 *************************/
namespace Test1 {
int run() {
    int a=1000000000,b=1;
    while(a) b^=a, a--;
    printf("%d\n",b);
    return 0;
}}
/*********************** Test 2 *************************/
namespace Test2 {
const int MX=50000000;
int p[MX],m[MX],pc;
int run() {
    for(int i=2;i<MX;i++){
        if(!m[i]) p[++pc]=m[i]=i;
        static int k;
        for(int j=1;j<=pc && p[j]<=m[i] && (k=p[j]*i)<MX; j++)
            m[k]=p[j];
    }
    int ans=0;
    for(int i=1;i<=pc;i++) ans^=p[i];
    printf("%d\n",ans);
    return 0;
}}
/*********************** Test 3 *************************/
namespace Test3 {
const int MX=1000;
int G[MX][MX];
int sed=0;
inline int Rand(){ return sed=(sed*sed*73+sed*233+19260817)&0x0000ffff; }
int run(){
    for(int i=0;i<MX;i++)
        for(int j=0;j<MX;j++)
            G[i][j]=Rand();
    for(int i=0;i<MX;i++)
        for(int j=0;j<MX;j++)
            for(int k=0;k<MX;k++)
                if(G[j][k]>G[j][i]+G[i][k]) G[j][k]=G[j][i]+G[i][k];
    int ans=0;
    for(int i=0;i<MX;i++)
        for(int j=0;j<MX;j++)
            ans^=G[i][j];
    printf("%d\n",ans);
    return 0;
}}
/*********************** Test 4 *************************/
namespace Test4 {
const int MX=1000000;
int sed=0;
inline int Rand(){ return sed=(sed*sed*73+sed*233+19260817); }
int run(){
    set<int>S;
    for(int i=0;i<MX;i++) S.insert(Rand());
    int ans=0;
    for(auto &x:S) ans^=x;
    printf("%d\n",ans);
    return 0;
}}
/*********************** Test 5 *************************/
namespace Test5 {
const int MX=20000000;
int *it[MX];
int run(){
    for(int i=0;i<MX;i++) it[i]=new int;
    for(int i=0;i<MX;i++) *it[i]=i;
    int ans=0;
    for(int i=0;i<MX;i++) ans^=*it[i];
    printf("%d\n",ans);
    return 0;
}}
/*********************** Test 6-1 *************************/
namespace Test61 {
const int MX=1<<25;
int a[MX];
inline unsigned int Rand(){
    static unsigned int sed=0;
    return (sed=(sed*233+19260421))&(MX-1);
}
int run(){
    for(int i=0;i<MX;i++) a[Rand()]=i;
    return 0;
}}
/*********************** Test 6-2 *************************/
namespace Test62 {
const int MX=1<<25;
int a[MX];
inline unsigned int Rand(){
    static unsigned int sed=0;
    return (sed=(sed*(MX+1)+1025))&(MX-1);
}
int run(){
    for(int i=0;i<MX;i++) a[Rand()]=i;
    return 0;
}}
/*********************** Test 6-3 *************************/
namespace Test63 {
const int MX=1<<25;
int a[MX];
inline unsigned int Rand(){
    static unsigned int sed=0;
    return (sed=(sed*(MX+1)+1))&(MX-1);
}
int run(){
    for(int i=0;i<MX;i++) a[Rand()]=i;
    return 0;
}}
/*********************** Test 7-1 *************************/
namespace Test71 {
typedef unsigned long long ull;
#define P71 1000000007
const int MX=100000000;
int run(){
    ull ans=1;
    for(int i=1;i<MX;i++) ans=ans*i%P71;
    printf("%llu\n",ans);
    return 0;
}}
/*********************** Test 7-2 *************************/
namespace Test72 {
typedef unsigned long long ull;
int P=1000000007;
const int MX=100000000;
int run(){
    ull ans=1;
    for(int i=1;i<MX;i++) ans=ans*i%P;
    printf("%llu\n",ans);
    return 0;
}}
/*********************** Test 8 *************************/
namespace Test8 {
const int MX=20000000;
int run(){
    double ans=0.61234567898765,t=1,s=0;
    for(int i=1;i<MX;i++) s+=(t*=ans);
    printf("%f\n",s);
    return 0;
}}
/*********************** Test 9-1 *************************/
namespace Test91 {
typedef unsigned int uint;
const int MX=1<<10;
uint a[MX][MX],b[MX][MX];
inline uint Rand(){
    static unsigned int sed=0;
    return (sed=(sed*233+19260421))&(MX-1);
}
int run(){
    register int i,j,k;
    for(i=0;i<MX;i++)
        for(j=0;j<MX;j++)
            a[i][j]=Rand();
    #define A(t) (b[i][k+t]+=a[i][j]*a[j][k+t])
    for(i=0;i<MX;i++)
        for(j=0;j<MX;j++)
            for(k=0;k<MX;k++)
                A(0);
    #undef A
    uint s=0;
    for(i=0;i<MX;i++)
        for(j=0;j<MX;j++)
            s+=a[i][j];
    printf("%u\n",s);
    return 0;
}}
/*********************** Test 9-2 *************************/
namespace Test92 {
typedef unsigned int uint;
const int MX=1<<10;
uint a[MX][MX],b[MX][MX];
inline uint Rand(){
    static unsigned int sed=0;
    return (sed=(sed*233+19260421))&(MX-1);
}
int run(){
    register int i,j,k;
    for(i=0;i<MX;i++)
        for(j=0;j<MX;j++)
            a[i][j]=Rand();
    #define A(t) (b[i][k+t]+=a[i][j]*a[j][k+t])
    for(i=0;i<MX;i++)
        for(j=0;j<MX;j++)
            for(k=0;k<MX;k+=8)
                A(0),A(1),A(2),A(3),A(4),A(5),A(6),A(7);
    #undef A
    uint s=0;
    for(i=0;i<MX;i++)
        for(j=0;j<MX;j++)
            s+=a[i][j];
    printf("%u\n",s);
    return 0;
}}
/*********************** MAIN *************************/
int main(){
    int x;
    cin >> x;
    switch(x){
        case 1: return Test1::run();
        case 2: return Test2::run();
        case 3: return Test3::run();
        case 4: return Test4::run();
        case 5: return Test5::run();
        case 61: return Test61::run();
        case 62: return Test62::run();
        case 63: return Test63::run();
        case 71: return Test71::run();
        case 72: return Test72::run();
        case 8: return Test8::run();
        case 91: return Test91::run();
        case 92: return Test92::run();
        default:
            cout<<"Invalid Test Number\n";
            return 0;
    }
}
