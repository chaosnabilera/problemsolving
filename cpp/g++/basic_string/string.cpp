#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> split(std::string str, char delimiter);

int main(){
    std::string test = "this is sparta gatsby believed in the green light boats against current";
    std::vector<std::string> result = split(test, ' ');
    for (int i=0;i<result.size();i++){
        printf("%s\n", result[i].c_str());
    }
}

std::vector<std::string> split(std::string input, char delimiter) {
    std::vector<std::string> answer;
    std::stringstream ss(input);
    std::string temp;
 
    while (std::getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }
 
    return answer;
}