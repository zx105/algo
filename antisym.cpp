#include <bits/stdc++.h>
using namespace std;
#define FOR(i,n) for(int i=0;i<n;++i)

int main(int argc, char** argv) {
    int n;
    scanf("%d",&n);
    char s[600000];
    int c[550000];
    s[0]=2;
    scanf("%s",s+1);
    for(int i=1;i<=n;++i) s[i]-='0';
    ++n;
    s[n]=2;
    for(int i=0;i<550000;++i) c[i]=0;
    int index=1;
    while(index<n-1) {
        while((s[index-c[index]]^s[index+1+c[index]])==1) ++c[index];
        int m=0;
        for(int i=1;i<c[index];++i) {
            c[index+i]=min(c[index-i],c[index]-i);
            // prefix
            if(c[index+i]==c[index]-i) {
                index+=i;
                m=1;
                break;
            }
        }
        if(m==0) ++index;
    }
    long long ans=0;
    for(int i=0;i<n-1;++i) ans+=c[i];
    printf("%lld\n",ans);
}