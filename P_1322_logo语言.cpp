#include<iostream>
#include<cstring>
using namespace std;
int work(){
    int ans=0,k;
    char t;
    string s;
    char op;
    while (cin>>op)
    {
        if(op==']') break;
        cin>>s>>k;
        if(op=='R'){
            t=getchar();
            ans+=k*work();
            t=getchar();
        }
        if(op=='F'){
            t=getchar();
            ans+=k;
        }
        if(op=='B'){
            t=getchar();
            ans-=k;
        }
        if(t==']'){
            break;
        }
    }
    return ans;
}
// int work(){
//     int ans=0,k;
//     char op,t;
//     string s;
//     while (cin>>op)
//     {
//         if(op==']') break;
//         cin>>s>>k;
//         if(op=='R'){
//             cin>>t;
//             ans+=k*work();
//             cin>>t;
//         }
//         if(op=='F'){
//             cin>>t;
//             ans+=k;
//         }
//         if(op=='B'){
//             cin>>t;
//             ans-=k;
//         }
//         if(t==']'){
//             break;
//         }
//     }
//     return ans;
// }
int main(){
    cout<<abs(work());
    return 0;
}