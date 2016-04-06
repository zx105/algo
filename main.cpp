#include <bits/stdc++.h>
using namespace std;
#define FOR(i,n) for(int i=0;i<n;++i)

#define SIZE 1<<20 // max size of result

typedef unsigned long long ull;

ull p = 4194304001llu; // finite field Z_p
ull g = 347132723llu; // generator of Z_p

ull modpow(ull a,ull e) {
	ull ans=1;
	while(e) {
		if(e&1) ans = (ans*a)%p;
		a = (a*a)%p;
		e>>=1;
	}
	return ans;
}

inline ull modinverse(ull a) {
	return modpow(a,p-2);
}

ull unity[2][SIZE]; // powers of root of unity
unsigned int rev[65536]; // reversing array

void fill() {
	for(int i=0;i<65536;++i) {
		rev[i] = 0;
		int x = i;
		for(int j=0;j<16;++j) {
			rev[i]<<=1;
			rev[i]|=x%2;
			x>>=1;
		}
	}
}


void do_fft(vector<ull> &in,int index,int k,vector<ull> &out,int inverse) {
	if((in.size()>>k)==0) out[index] = in[((rev[index&65535]<<16)|rev[index>>16])>>(33-k)];
	else {
		do_fft(in,2*index,k+1,out,inverse);
		do_fft(in,2*index+1,k+1,out,inverse);
		int length = in.size()>>k;
		int begin = index*length*2;
		for(int i=0;i<length;++i) {
			ull a = out[begin+i];
			ull b = (out[begin+i+length]*unity[inverse][i<<(k-1)])%p;
			out[begin+i] = (a+b)%p;
			out[begin+i+length] = (a-b+p)%p;
		}
	}
}

void fft(vector<ull> in,vector<ull> &out, bool inverse) {
	out.resize(in.size(),0);
	do_fft(in,0,1,out,inverse?1:0);
	if(inverse) {
		for(int i=0;i<out.size();++i) {
			out[i] = (out[i]*modinverse(in.size()))%p;
		}
	}
}

int main(void) {
	int n;
	scanf("%d",&n);
	int nb = 1;
	while(n>nb) nb<<=1;
	nb<<=1;
	ull ord = (p-1)/nb;
	ull mul = modpow(g,ord);
	// generate field
	unity[0][0] = 1;
	for(int i=1;i<nb;++i) {
		unity[0][i] = (mul*unity[0][i-1])%p;
	}
	for(int i=0;i<nb;++i) unity[1][i] = modinverse(unity[0][i]);
	// generate rev array
	fill();
	// do stuff
	
}
