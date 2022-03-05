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

int clockwise(char* cur_state, char* next_state){
	int cur_state_len = strlen(cur_state);
	int next_state_len = strlen(next_state);

	std::vector<char> haystack(next_state_len*2);
	for(int i=0; i<next_state_len; ++i){
		haystack[i] = next_state[i];
		haystack[i+next_state_len] = next_state[i];
	}
	std::vector<char> needle(cur_state,cur_state+cur_state_len);
	//printf("needle len: %d\n",needle.size());
	std::vector<size_t> match_idx;

	kmpsearch<char>(haystack, needle, match_idx);

	return match_idx[0];
}

int anticlockwise(char* cur_state, char* next_state){
	int cur_state_len = strlen(cur_state);
	int next_state_len = strlen(next_state);

	std::vector<char> haystack(cur_state_len*2);
	for(int i=0; i<cur_state_len; ++i){
		haystack[i] = cur_state[i];
		haystack[i+cur_state_len] = cur_state[i];
	}
	std::vector<char> needle(next_state, next_state+next_state_len);
	std::vector<size_t> match_idx;

	kmpsearch<char>(haystack, needle, match_idx);

	return match_idx[0];
}

int main(int argc, char** argv){
	int C, N, cnt;
	char cur_state[10001] = {0};
	char next_state[10001] = {0};

	scanf("%d",&C);
	for(int c=0; c<C; ++c){
		scanf("%d",&N);
		scanf("%s",cur_state);
		cnt = 0;
		for(int n=0; n<N; ++n){
			scanf("%s",next_state);
			if((n&1) == 0){
				cnt += clockwise(cur_state, next_state);
			}
			else{
				cnt += anticlockwise(cur_state, next_state);
			}
			memcpy(cur_state, next_state, sizeof(next_state));
		}
		printf("%d\n",cnt);
	}
	return 0;
}