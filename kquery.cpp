#include <bits/stdc++.h>
using namespace std;
#define FOR(i,n) for(int i=0;i<n;++i)

// sarch for <=x
int search(vector<int> v,int x) {
	if(v.size()==0 || v[0]>x) return 0;
	int b=0;
	int e=v.size();
	while(e-b>1) {
		int mid = (b+e)/2;
		if(v[mid]<=x) b=mid;
		else e=mid;
	}
	return b+1;
}

class segment{
public:
	vector<vector<int> > data;
	int* raw;
	int x;
	segment(int n) {
		x = sqrt(n)+1;
		data.resize(x);
		raw = new int[n];
		FOR(i,x) data[i].resize(x,1e9);
		FOR(i,n) raw[i] = 1e9;
		
	}
	~segment() {
		delete[] raw;
	}
	// <b,e>
	int query(int b,int e,int val) {
		int l_block = b/x;
		int r_block = e/x;
		if(e-b+1<=2*x) {
			int ans=0;
			for(int i=b;i<=e;++i) if(raw[i]<=val) ++ans;
			return ans;
		}
		int ans=0;
		for(int i=b;i<(l_block+1)*x;++i) if(raw[i]<=val) ++ans;
		for(int i=e;i>=(r_block)*x;--i) if(raw[i]<=val) ++ans;
		for(int i=l_block+1;i<r_block;++i) ans+=search(data[i],val);
		return ans;
	}	
	void val(int index,int val) {
		int old = raw[index];
		raw[index] = val;
		int block = index/x;
		for(int i=0;i<data[block].size();++i) {
			if(data[block][i]==old) {
				data[block][i]=val;
				int pos = i;
				while(pos>0 && data[block][pos-1]>data[block][pos]) {
					int z = data[block][pos-1];
					data[block][pos-1] = data[block][pos];
					data[block][pos] = z;
					--pos;
				}
				while(pos<data[block].size()-1 && data[block][pos]>data[block][pos+1]) {
					int z = data[block][pos];
					data[block][pos] = data[block][pos+1];
					data[block][pos+1] = z;
					++pos;
				}
				break;
			}
		}
	}
};
	


int main(void) {

	
}
