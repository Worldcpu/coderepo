#include<bits/stdc++.h>
using namespace std;
const int MN=250;
const double eps=1e-6;
int n;
double a[MN][MN];
#undef swap

template<typename T> inline T abs(T val){
	return val>0?val:-val;
}

void Gauss(){//高斯消元
	for(int i=1;i<=n;i++){
		int maxx=i;
		for(int j=1;j<=n;j++){//把枚举范围从i->n改成了1->n
			if(abs(a[j][j])>eps&&j<i) continue;//若在i前，且的确已对应一项系数，不可用
			if(abs(a[j][i])>abs(a[maxx][i])){
				maxx=j;
			}
		}
		for(int j=1;j<=n+1;j++) swap(a[maxx][j],a[i][j]);
		if(abs(a[i][i])<=eps) continue;
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			double delta=a[j][i]/a[i][i];
			for(int k=i;k<=n+1;k++){
				a[j][k]-=delta*a[i][k];
			}
		}
	}
}

void gauss(){
    for(int i=1;i<=n;i++){
        int maxx=i;
        for(int j=1;j<=n;j++){
            if(abs(a[j][j])>eps&&j<i) continue;
            if(abs(a[j][i])>abs(a[maxx][i])){
                maxx=j;
            }
        }
        for(int j=1;j<=n+1;j++) swap(a[maxx][j],a[i][j]);

        if(abs(a[i][i])<=eps) continue;
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            double de=a[j][i]/a[i][i];
            for(int k=i;k<=n+1;k++){
                a[j][k]-=de*a[i][k];
            }
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n+1;j++){
            cin>>a[i][j];
        }
    }
    gauss();
    int ret=1;
    for(int i=1;i<=n;i++){
        if(abs(a[i][i])<=eps){
		// for(int j=1;j<=n+1;j++) printf("%.2lf ",a[i][j]);
		// printf("\n");
            if(abs(a[i][n+1])>eps) ret=-1;
            else if(ret!=-1) ret=0;
        }
    }
    if(ret!=1) cout<<ret;
    else{
        for(int i=1;i<=n;i++){
            cout<<"x"<<i<<"="<<fixed<<setprecision(2)<<((abs(a[i][n+1]/a[i][i])<=eps) ? 0 : a[i][n+1]/a[i][i])<<'\n';
        }
    }
    return 0;
}