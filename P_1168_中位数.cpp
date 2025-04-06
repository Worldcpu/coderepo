#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
namespace pbds=__gnu_pbds;
const int MN=1e5+15;
int n,a;
pbds::priority_queue<int,less<int>,thin_heap_tag> y;
pbds::priority_queue<int,greater<int>,thin_heap_tag> x;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a;
        if(i==1){
            x.push(a);
            cout<<x.top()<<'\n';
            cout<<"SIZE:"<<x.size()<<" "<<y.size()<<'\n';
        }
        if(i>1&&(i&1)==0){
            int c=x.top();
            if(a<=c) y.push(a);
            else{
                x.pop();
                x.push(a);
                y.push(c);
            }
            cout<<((x.top()+y.top())>>1)<<'\n';
            cout<<"SIZE:"<<x.size()<<" "<<y.size()<<'\n';
        }else if(i>1&&(i&1)){
            int c=y.top();
            if(a>=c) x.push(a);
            else{
                y.pop();
                y.push(a);
                x.push(c);
            }
            cout<<x.top()<<'\n';
            cout<<"SIZE:"<<x.size()<<" "<<y.size()<<'\n';
        }
    }

    return 0;
}