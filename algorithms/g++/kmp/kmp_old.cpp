#include <iostream>
#include <vector>
#include <cstring>

template <typename T>
std::vector<size_t> get_prefsuf_match(std::vector<T>& iseq){
	size_t iseq_len = iseq.size();
	std::vector<size_t> prefsuf_match(iseq_len);
	size_t beg = 1;
	size_t match = 0;

	prefsuf_match[0] = 0;
	while (beg + match < iseq_len){
		if(iseq[beg+match] == iseq[match]){
			prefsuf_match[beg+match] = match+1;
			++match;
		}
		else{
			if(match == 0){
				++beg;
			}
			else{
				beg = beg + match - prefsuf_match[match-1]; //-1 because of 0-index
				match = prefsuf_match[match-1];
			}
		}
	}
	return prefsuf_match;
}

template <typename T>
void kmpsearch(std::vector<T>& in_haystack, std::vector<T>& in_needle, std::vector<size_t>& out_idx){
	std::vector<size_t> needle_prefsuf_match = get_prefsuf_match<T>(in_needle);
	size_t beg = 0;
	size_t match = 0;
	size_t haystack_len = in_haystack.size();
	size_t needle_len = in_needle.size();

	while(beg <= haystack_len - needle_len){
		if(match < needle_len && in_haystack[beg+match] == in_needle[match]){
			++match;
			if(match == needle_len){
				out_idx.push_back(beg);
			}
		}
		else{
			if(match == 0){
				++beg;
			}
			else{
				beg = beg + match - needle_prefsuf_match[match-1];
				match = needle_prefsuf_match[match-1];
			}
		}
	}
}

int main(){
	char h[] = "abcdefababcabcabcjkghijkzzzabcdefabcabcabcjkdefgabcdabcabcabcj";
	char n[] = "abcabcabcjk";

	std::vector<char> haystack;
	std::vector<char> needle;
	std::vector<size_t> result;

	for(int i=0; i<strlen(h); ++i){
		haystack.push_back(h[i]);
	}

	for(int i=0; i<strlen(n); ++i){
		needle.push_back(n[i]);
	}

	kmpsearch(haystack, needle, result);

	for (auto it: result){
		printf("%lu ", it);
	}
	printf("\n");

	return 0;
}