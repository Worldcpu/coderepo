import math

def mu(n):
    ans=1
    i=2
    while i*i<=n:
        if n%i==0:
            n //= i
            if n%i==0:
                return 0;
            ans=-ans
        i+=1
    if n>1:
        ans=-ans
    return ans

def isqrt(x):
    if x < 2:
        return x
    l, r = 1, 10**(len(str(x))//2 + 1)
    while l < r:
        mid = (l + r + 1) // 2
        if mid * mid <= x:
            l = mid
        else:
            r = mid - 1
    return l


def calc_f(n,k):
    lim=min(isqrt(n),k)
    ans=0
    for i in range(1,lim+1):
        if n%i==0:
            ans+=mu(i)*(k//i)
            if i*i!=n and n//i<=k:
                ans+=mu(n//i)*(k//(n//i))
    return ans

def g(n,m,k):
    lim=min(isqrt(n),k)
    ans=0
    for i in range(1,lim+1):
        if n%i==0:
            ans+=calc_f(n//i,m//i)
            if i*i!=n and n//i<=k:
                ans+=calc_f(i,m//(n//i))
    return ans

def bs(n,m,k):
    l=1
    r=n
    while l<r:
        mid=(l+r)>>1
        if g(n,mid,m)<k:
            l=mid+1
        else:
            r=mid
    return l

n,c,f,l,r=map(int,input().split())
x=g(n,n,c)
if f % x == 0: 
    y = (f // x - 1) * n
    f = x
else:
    y = f // x * n
    f %= x
print(bs(n, c, f) + y)
print(g(n, r, c) - g(n, l - 1, c), end = "")
