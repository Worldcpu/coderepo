#include<iostream>
using namespace std;
int main(){
	freopen("db.out","w",stdout);
	int v[1010]{};
	for(int i=1;i<1010;i++){
		for(int j=1;j<i;j++){
			if(i%j==0){
				v[i]+=j; 
			}
		}
			
	}
	cout<<"int v[1145]={";
	for(int i=0;i<1010;i++){
		if(i==1009) cout<<v[i];
		else cout<<v[i]<<",";
	}
	cout<<"};";
	return 0;
}
