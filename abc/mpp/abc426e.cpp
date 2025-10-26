#include <bits/stdc++.h>
using namespace std;
constexpr double eps=1e-12;
struct P{ 
    double x,y;

    P(double xx=0,double yy=0){
        x=xx,y=yy;
    }
};
vector<double> tmp;

namespace ly
{
    namespace IO
    {
        #ifndef LOCAL
            constexpr auto maxn=1<<20;
            char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;
            #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,maxn,stdin),p1==p2)?EOF:*p1++)
            #define flush() (fwrite(out,1,p3-out,stdout))
            #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
            class Flush{public:~Flush(){flush();}}_;
        #endif
        namespace usr
        {
            template<typename type>
            inline type read(type &x)
            {
                x=0;bool flag(0);char ch=getchar();
                while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
                while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
                return flag?x=-x:x;
            }
            template<typename type>
            inline void write(type x)
            {
                x<0?x=-x,putchar('-'):0;
                static short Stack[50],top(0);
                do Stack[++top]=x%10,x/=10;while(x);
                while(top) putchar(Stack[top--]|48);
            }
            inline char read(char &x){do x=getchar();while(isspace(x));return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch;read(ch);do *(x++)=ch;while(!isspace(ch=getchar())&&~ch);}
            template<typename type>inline void write(type *x){while(*x)putchar(*(x++));}
            inline void read(string &x){static char ch;read(ch),x.clear();do x+=ch;while(!isspace(ch=getchar())&&~ch);}
            inline void write(const string &x){for(int i=0,len=x.length();i<len;++i)putchar(x[i]);}
            template<typename type,typename...T>inline void read(type &x,T&...y){read(x),read(y...);}
            template<typename type,typename...T>
            inline void write(const type &x,const T&...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar('\n');}
            template<typename type>
            inline void put(const type &x,bool flag=1){write(x),flag?putchar('\n'):putchar(' ');}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    }using namespace IO::usr;
}using namespace ly::IO::usr;

P operator-(const P&a,const P&b){
    return {a.x-b.x,a.y-b.y};
}

P operator+(const P&a,const P&b){
    return {a.x+b.x,a.y+b.y};
}

P operator*(const P&a,double t){
    return {a.x*t,a.y*t};
}

double dot(const P&a,const P&b){
    return a.x*b.x+a.y*b.y;
}

double norm(const P&a){
    return sqrt(dot(a,a));
}

signed main(){
    int T;
    read(T);
    while(T--){
        tmp.clear();
        int axx,axy,ayx,ayy,bxx,bxy,byx,byy;
        read(axx,axy,ayx,ayy,bxx,bxy,byx,byy);
        P ax(axx,axy),ay(ayx,ayy),bx(bxx,bxy),by(byx,byy);

        double Tt=norm(ay-ax), Ta=norm(by-bx);
        P vT={(ay.x-ax.x)/Tt,(ay.y-ax.y)/Tt};
        P vA={(by.x-bx.x)/Ta,(by.y-bx.y)/Ta};
        double mnT=min(Tt,Ta), mxT=max(Tt,Ta);

        tmp.push_back(0.0);
        tmp.push_back(mnT);
        tmp.push_back(mxT);

        P dP=ax-bx;
        P dV={vT.x-vA.x,vT.y-vA.y};
        double a=dot(dV,dV);

        if(a>eps){
            double tim = - dot(dV,dP)/a;
            if(tim>0-eps && tim<mnT+eps) tmp.push_back(max((double)0.0,min(mnT,tim)));
        }
        if(Tt<Ta){
            P dP = ay - bx;
            P dV = { -vA.x, -vA.y };
            double a = dot(dV,dV);
            if(a>eps){
                double tim = - dot(dV,dP)/a;
                if(tim>mnT-eps && tim<mxT+eps) tmp.push_back(max(mnT,min(mxT,tim)));
            }
        }else if(Ta<Tt){
            P dP = ax - by;
            P dV = { vT.x, vT.y };
            double a = dot(dV,dV);
            if(a>eps){
                double tim=-dot(dV,dP)/a;
                if(tim>mnT-eps&&tim<mxT+eps) tmp.push_back(max(mnT,min(mxT,tim)));
            }
        }
        double ans=1e18;
        for(double t:tmp){
            if(t<0) continue;
            P PT=(t<=Tt?P{ax.x+vT.x*t,ax.y+vT.y*t}:ay);
            P PA=(t<=Ta?P{bx.x+vA.x*t,bx.y+vA.y*t}:by);
            double d = sqrt( (PT.x-PA.x)*(PT.x-PA.x) + (PT.y-PA.y)*(PT.y-PA.y) );
            if(d<ans) ans=d;
        }
        cout<<fixed<<setprecision(12)<<ans<<'\n';
    }
    return 0;
}
