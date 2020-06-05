#include "BioebString.h"
#include <iostream>
#include <sstream>
#include <algorithm>

namespace bioeb{
  std::vector<std::string> tokenize(std::string text, char delimiter){
    std::stringstream stream(text);
    std::string line;
    std::vector<std::string> tokens;
    while(stream.good()){
      getline(stream,line,delimiter);
      tokens.push_back(line);
    }
    return tokens;
  }
  std::vector<std::string> tokenize(std::string text, std::string delimiters){
    std::vector<std::string> tokens;
    size_t minPos=std::string::npos;
    do{
      minPos=std::string::npos;
      for (auto delim: delimiters){
	int pos=text.find_first_of(delim);
	if(pos<minPos){
	  minPos=pos;
	}
      }
      tokens.push_back(text.substr(0,minPos));
      text=text.substr(minPos+1,text.length());
    } while(minPos< std::string::npos);
    return tokens;
  }
}
