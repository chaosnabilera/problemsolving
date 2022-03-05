#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

class FNode{
public:
	FNode(std::string _name, bool isdir) : name(_name) {
		if(isdir){
			dir = new std::unordered_map<std::string, FNode*>();
			content = nullptr;
		}
		else{
			dir = nullptr;
			content = new std::stringstream();
		}
	}
	~FNode(){
		if(dir){
			for(auto it:*dir){
				delete it.second;
			}
			delete dir;
		}
		if(content) delete content;
	}
	std::vector<std::string>& list(){
		std::vector<std::string>& ret = *(new std::vector<std::string>());
		if(dir){
			for(auto it : *dir){
				ret.push_back(it.first);
			}
		}
		else{
			ret.push_back(name);
		}
		return ret;
	}
	FNode* subpath(std::string& pn){
		return (*dir)[pn];
	}
	bool exist(std::string& pathname){
		return (dir->find(pathname) != dir->end());
	}
	void adddir(std::string& dirname){
		(*dir)[dirname] = new FNode(dirname, true);
	}
	void addfile(std::string& filename){
		(*dir)[filename] = new FNode(filename, false);
	}
	void addcontent(std::string& data){
		(*content) << data;
	}
	std::string content_as_string(){
		return content->str();
	}
private:
	std::string name;
	std::unordered_map<std::string, FNode*>* dir;
	std::stringstream* content;
};

class FileSystem {
public:
	FileSystem() {
		root = new FNode("", true);
	}

	~FileSystem(){
		delete root;
	}
	
	std::vector<std::string> ls(std::string path) {
		std::vector<std::string> pathlist = split_path(path);
		FNode* cur = root;
		for(auto pn: pathlist){
			cur = cur->subpath(pn);
		}
		std::vector<std::string> ret = cur->list();
		std::sort(ret.begin(),ret.end());
		return ret;
	}
	
	void mkdir(std::string path) {
		std::vector<std::string> pathlist = split_path(path);
		FNode* cur = root;
		for(auto dn: pathlist){
			if(!cur->exist(dn)){
				cur->adddir(dn);
			}
			cur = cur->subpath(dn);
		}
	}
	
	void addContentToFile(std::string filePath, std::string content) {
		std::vector<std::string> pathlist = split_path(filePath);
		std::string& filename = pathlist[pathlist.size()-1];
		FNode* cur = root;
		for(int i=0; i<pathlist.size()-1; ++i){
			cur = cur->subpath(pathlist[i]);
		}
		if(!cur->exist(filename)){
			cur->addfile(filename);
		}
		cur = cur->subpath(filename);
		cur->addcontent(content);
	}
	
	std::string readContentFromFile(std::string filePath) {
		std::vector<std::string> pathlist = split_path(filePath);
		FNode* cur = root;
		for(auto pn: pathlist){
			cur = cur->subpath(pn);
		}
		return cur->content_as_string();
	}

private:
	inline std::vector<std::string>& split_path(std::string path){
		std::vector<std::string>& res = *(new std::vector<std::string>());
		std::stringstream pss(path);
		std::string tok;
		while(std::getline(pss, tok, '/')){
			if(tok.size() > 0){
				res.push_back(tok);
			}
		}
		return res;
	}
	FNode* root;
};

int main(int argc, char** argv){
	FileSystem fileSystem;
	fileSystem.ls("/");
	fileSystem.mkdir("/a/b/c");
	fileSystem.addContentToFile("/a/b/c/d", "hello");
	fileSystem.ls("/");
	fileSystem.readContentFromFile("/a/b/c/d");
}