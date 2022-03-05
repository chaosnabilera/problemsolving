#include <iostream>
#include <unordered_set>
#include <unordered_map>

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    char* buf = new char[size_s];
    std::snprintf( buf, size_s, format.c_str(), args ... );
    //std::string ret(buf,buf+size_s-1);
    std::string ret = buf;
    delete[] buf;
    return ret;
}

int main(){
	std::unordered_set<std::string> us;
	std::unordered_map<int, std::string> um;

	for(int i=0; i<20; ++i){
		std::string istr = string_format("input %d!%d!%d",i,i,i);
		us.insert(istr);
		um[i] = istr;
	}

	std::string s1 = string_format("hey %d%d",4,5);
	std::string s2 = string_format("ho %d%d",6,7);

	std::string s3 = s1+" "+s2;

	printf("%s\n",s3.c_str());

	printf("unordered_set:\n");
	for(std::unordered_set<std::string>::iterator it=us.begin(); it != us.end(); ++it){
		printf("    %s\n",it->c_str());
	}

	printf("unordered_map:\n");
	for(std::unordered_map<int,std::string>::iterator it=um.begin(); it != um.end(); ++it){
		printf("    %d:%s\n", it->first, it->second.c_str());
	}

	return 0;
}