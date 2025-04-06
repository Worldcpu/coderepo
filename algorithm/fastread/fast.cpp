#include<iostream>
using namespace std;
int read(){
    int res=0,neg=0,ch=getchar();
    while (!(isdigit(ch)||ch=='-')&&ch!=EOF)
    {
        ch=getchar();
    }
    if(ch=='-'){
        neg=1;
        ch=getchar();
    }
    while (isdigit(ch))
    {
        res=res*10+(ch-'0');
        ch=getchar();
    }
    return neg?-res:res;
}
int main(){

    return 0;
}