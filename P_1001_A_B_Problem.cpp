#include<bits/stdc++.h>
using namespace std;
template<typename type>
void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
template<typename type>
void write(type &x,bool mode=1){
    x<0?x=-x,putchar('-'):0;static short s[60],top(0);
    do s[++top]=x%10,x/=10; while (x);
    while(top) putchar(s[top--]|48);
    mode?putchar('\n'):putchar(' ');
}
int main(){
    __int128 c,a,b;
    read(a);
    read(b);
    c=a+b;
    write(c);
    return 0;
}