#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_map>

class StringRollingHash{
public:
	// d should be a prime number that can represent entire alphabet of string
	// mod should be a large prime number to avoid collision ( 1125899906842597 = (2^50)-27 )
	StringRollingHash(const char* initstr, int len, const int _d = 29, const unsigned long long _mod = 1125899906842597):
	d(_d), mod(_mod) {
		hash = 0;
		for(int i=0; i < len; ++i){
			hash *= d;
			hash += initstr[i];
			hash %= mod;
		}

		msd_hash = 1;
		for(int i=1; i<len; ++i){
			msd_hash *= d;
			msd_hash %= mod;
		}

		for(int i=0; i<len; ++i){
			q.push(initstr[i]);
		}
	}

	unsigned long long gethash(){
		return hash;
	}

	unsigned long long add_next(char nc){
		char front = q.front(); q.pop();
		unsigned long long front_hash = (front*msd_hash) % mod;
		hash = (hash+mod) - front_hash;
		hash *= d;
		hash += nc;
		hash %= mod;
		q.push(nc);
		return hash;
	}

	// for single use
	static unsigned long long compute_hash(const char* istr, int len, const int sd = 29, const unsigned long long smod = 1125899906842597){
		unsigned long long result = 0;
		for(int i = 0; i < len; ++i){
			result *= sd;
			result += istr[i];
			result %= smod;
		}
		return result;
	}

private:
	unsigned long long hash;
	unsigned long long msd_hash; // most significant digit hash
	std::queue<char> q;
	const int d;
	const unsigned long long mod;
};

class Solution{
public:
	int longestRepeatingSubstring(string s) {
		int low = 1;
		int high = s.size()-1;
		int mid;
		int maxlen = 0;

		while(low <= high){
			if((mid = (low+high) >> 1) == 0){
				break;
			}

			bool found = false;
			std::unordered_map<unsigned long long, std::vector<int>> collision;
			StringRollingHash srh(s.c_str(), mid);
			collision[srh.gethash()].push_back(mid-1);

			for(int i=mid; i<s.size(); ++i){
				collision[srh.add_next(s[i])].push_back(i);
			}

			for(auto it=collision.begin(); it != collision.end(); ++it){
				if(collision[it->first].size() > 1){
					found = true;
					break;
				}
			}

			if(found){
				maxlen = mid;
				low = mid+1;
			}
			else{
				high = mid-1;
			}
		}

		return maxlen;
    }
};