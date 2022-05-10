#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int N;
vector<string> Word;
vector<int> Parent[100];
vector<int> Child[100];

void get_input(){
    char w[0x10];
    Word.clear();
    scanf("%d", &N);
    for(int i=0; i<N; ++i){
        scanf("%s", w);
        Word.push_back(w);
    }
}

bool is_impossible(string& w){
    bool visited[26] = {0};
    int i = 0;
    while(i < w.size()){
        char c = w[i];
        if(visited[c-'A'])
            return true;
        visited[c-'A'] = true;
        while(i < w.size() && w[i] == c)
            ++i;
    }
    return false;
}

bool is_all_same(string& s){
    char c = s[0];
    for(int i=1; i<s.size(); ++i)
        if(s[i] != c)
            return false;
    return true;
}

string solve(){
    vector<string> nontrivial;
    vector<bool> visited(100,false);
    string all_same[26];

    for(int i=0; i<Word.size(); ++i){
        if(is_impossible(Word[i]))
            return "IMPOSSIBLE";
        if(is_all_same(Word[i])){
            all_same[Word[i][0]-'A'] += Word[i];
        }
        else{
            nontrivial.push_back(Word[i]);
        }
    }

    for(int i=0; i<nontrivial.size(); ++i){
        Parent[i].clear();
        Child[i].clear();
    }

    for(int i=0; i<nontrivial.size(); ++i){
        string& p = nontrivial[i];
        for(int j=0; j<nontrivial.size(); ++j){
            if(i == j)
                continue;
            string& q = nontrivial[j];
            if(p[0] == q[q.size()-1]){
                Parent[i].push_back(j);
                Child[j].push_back(i);
            }
        }
    }

    for(int i=0; i<nontrivial.size(); ++i){
        if(Parent[i].size() > 1 || Child[i].size() > 1)
            return "IMPOSSIBLE";
    }

    string result = "";

    for(int i=0; i<nontrivial.size(); ++i){
        if(visited[i])
            continue;

        if(Parent[i].empty()){
            // printf("<%s>\n", nontrivial[i].c_str());

            int cur = i;
            while(true){
                if(visited[cur])
                    return "IMPOSSIBLE";

                visited[cur] = true;
                string& wi = nontrivial[cur];

                char wi_f = wi[0];
                char wi_l = wi[wi.size()-1];

                if(all_same[wi_f-'A'].size() > 0){
                    result += all_same[wi_f-'A'];
                    all_same[wi_f-'A'] = "";
                }

                result += wi;

                if(all_same[wi_l-'A'].size() > 0){
                    result += all_same[wi_l-'A'];
                    all_same[wi_l-'A'] = "";
                }

                if(Child[cur].empty()){
                    break;
                }
                else{
                    cur = Child[cur][0];
                }
            }
        }
    }

    for(int i=0; i<nontrivial.size(); ++i)
        if(!visited[i])
            return "IMPOSSIBLE";

    // printf("%s?\n", result.c_str());

    for(int i=0; i<26; ++i){
        if(all_same[i].size() > 0){
            result += all_same[i];
            all_same[i] = "";
        }
    }

    // printf("%s?\n", result.c_str());

    if(is_impossible(result))
        return "IMPOSSIBLE";

    return result;
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        get_input();
        printf("Case #%d: %s\n", i+1, solve().c_str());
    }
}