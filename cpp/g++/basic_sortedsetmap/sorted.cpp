#include <iostream>
#include <set>
#include <map>

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
	std::set<std::string> ss;
	std::map<int, std::string> sm;

	for(int i=0; i<20; ++i){
		std::string istr = string_format("input %d!%d!%d",i,i,i);
		ss.insert(istr);
		sm[i] = istr;
	}

	std::string s1 = string_format("hey %d%d",4,5);
	std::string s2 = string_format("ho %d%d",6,7);

	std::string s3 = s1+" "+s2;

	printf("%s\n",s3.c_str());

	printf("sorted set:\n");
	for(std::set<std::string>::iterator it=ss.begin(); it != ss.end(); ++it){
		printf("    %s\n",it->c_str());
	}

	printf("sorted map:\n");
	for(std::map<int,std::string>::iterator it=sm.begin(); it != sm.end(); ++it){
		printf("    %d:%s\n", it->first, it->second.c_str());
	}

	return 0;
}