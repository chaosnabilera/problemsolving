#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <utility>
#include <queue>
#include <array>
#include <string>
#include <deque>

using namespace std;

void normalize(vector<int>& num);
vector<int> multiply_simple(const vector<int>& a, const vector<int>& b);
void addTo(vector<int>& a, const vector<int>& b, int k);
bool is_larger(const vector<int>& a, const vector<int>& b);
void subFrom(vector<int>& a, const vector<int>& b);
string multiply_string(string sa, string sb);
vector<int> string_to_reverse_digit_vector(string& istr);
string reverse_digit_vector_to_string(vector<int>& ivec);

void normalize(vector<int>& num){
	num.push_back(0);
	for(int i=0; i+1<num.size(); ++i){
		if(num[i] < 0){
			int borrow = (abs(num[i]) + 9) / 10;
			num[i+1] -= borrow;
			num[i] += borrow * 10;
		}
		else{
			num[i+1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	while(num.size() > 1 && num.back() == 0) num.pop_back();
}

// the number comes in reverse order
// e.g. multiply({3,2,1},{6,5,4}) = 123*456 = 56088 = {8,8,0,6,5}
vector<int> multiply_simple(const vector<int>& a, const vector<int>& b){
	vector<int> c(a.size()+b.size()+1, 0);
	for(int i=0; i < a.size(); ++i){
		for(int j=0; j < b.size(); ++j){
			c[i+j] += a[i]*b[j];
		}
	}
	normalize(c);
	return c;
}

// a += b*(10^k)
void addTo(vector<int>& a, const vector<int>& b, int k){
	while(a.size() < b.size()+k+1)
		a.push_back(0);

	for(int i=0; i<b.size(); ++i){
		a[i+k] += b[i]; 
	}

	normalize(a);
}

// check a > b
// we assume a,b are normalized
bool is_larger(const vector<int>& a, const vector<int>& b){
	if(a.size() > b.size()){
		return true;
	}
	else if(a.size() == b.size()){
		for(int i=a.size(); i >= 0; --i){
			if(a[i] > b[i]){
				return true;
			}
		}
	}
	return false;
}

// a -= b   we assume a >= b
void subFrom(vector<int>& a, const vector<int>& b){
	for(int i=0; i<b.size(); ++i){
		a[i] -= b[i];
	}
	normalize(a);
}

vector<int> string_to_reverse_digit_vector(string& istr){
	vector<int> res;
	for(int i=istr.size()-1; i>=0; --i)
		res.push_back(istr[i]-'0');
	while(res.size() > 1 && res.back() == 0)
		res.pop_back();
	return res;
}

string reverse_digit_vector_to_string(vector<int>& ivec){
	string res;
	for(int i=ivec.size()-1; i>=0; --i)
		res.push_back(ivec[i]+'0');
	return res;
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b){
	if(a.size() < b.size())
		return karatsuba(b,a);
	if(a.size() == 0 || b.size() == 0)
		return vector<int>();
	if(a.size() < 50) 
		return multiply_simple(a,b);

	int half = a.size() / 2;
	vector<int> a0(a.begin(), a.begin()+half);
	vector<int> a1(a.begin()+half, a.end());
	vector<int> b0(b.begin(), b.begin()+min<int>(b.size(), half));
	vector<int> b1(b.begin()+min<int>(b.size(),half), b.end());

	// z2 = a1*b1
	vector<int> z2 = karatsuba(a1,b1);
	// z0 = a0*b0
	vector<int> z0 = karatsuba(a0,b0);
	// a0 = a0+a1; b0 = b0+b1
	addTo(a0,a1,0);
	addTo(b0,b1,0);

	vector<int> z1 = karatsuba(a0,b0);
	subFrom(z1,z0);
	subFrom(z1,z2);

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half+half);
	return ret;
}

string multiply_string(string sa, string sb){
	vector<int> a = string_to_reverse_digit_vector(sa);
	vector<int> b = string_to_reverse_digit_vector(sb);

	//vector<int> ab = multiply_simple(a,b);
	vector<int> ab = karatsuba(a,b);

	return reverse_digit_vector_to_string(ab);
}

void print_vector(vector<int> ivec){
	for(int i:ivec){
		printf("%d ", i);
	}
	printf("\n");
}

int main(int argc, char** argv){
	string a = argv[1];
	string b = argv[2];
	//int k = atoi(argv[3]);

	vector<int> va = string_to_reverse_digit_vector(a);
	vector<int> vb = string_to_reverse_digit_vector(b);

	// addTo(va,vb,k);

	//cout << is_larger(va,vb) << endl;

	// cout << reverse_digit_vector_to_string(va) << endl;
	cout << multiply_string(argv[1],argv[2]) << endl;
}