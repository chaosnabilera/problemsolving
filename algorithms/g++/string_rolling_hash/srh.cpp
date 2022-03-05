#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

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

int main(){
	// try to find thisissparta (12 chars)
	char istr[] = "thisthisthisthisisspartaspartathisisspartaisthisspartahahahahathisissparta";
	int istr_len = strlen(istr);
	StringRollingHash srh(istr, 12);

	unsigned long long targethash = StringRollingHash::compute_hash("thisissparta",12);
	printf("trying to find %s : %lld\n", "thisissparta", targethash);

	printf("initial hash: %lld\n", srh.gethash());
	for(int i=12; i<istr_len; ++i){
		unsigned long long curhash = srh.add_next(istr[i]);
		//printf("%c %llu\n",istr[i], curhash);
		if(curhash == targethash){
			printf("hash found at %d\n", i);
		}
	}
}