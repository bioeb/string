#include "BioebString.h"
#include <unicode/ustream.h>
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

  std::vector<icu::UnicodeString> tokenize(icu::UnicodeString text, UChar delimiter){
    std::vector<icu::UnicodeString> tokens;
    tokens.reserve(10);
    int pos=-1;
    while((pos=text.indexOf(delimiter))>-1){
      icu::UnicodeString token;
      text.extract(0,pos, token);
      text.extract(pos+1, text.countChar32(), text);
      tokens.emplace_back(token);
    }
    tokens.emplace_back(text);
    return tokens;
  }

  std::vector<icu::UnicodeString> tokenize(icu::UnicodeString text, icu::UnicodeString delimiters){
    std::vector<icu::UnicodeString> tokens;
    tokens.reserve(10);
    int pos=-1;
    int minpos=-1;
    do{
      minpos=text.countChar32();
      for(int i=0;i<delimiters.countChar32();++i){
	pos=text.indexOf(delimiters.tempSubString(i,1));
	std::cerr<<"`"<<delimiters.tempSubString(i,1)<<"` "<<pos<<std::endl;
	if(pos<minpos && pos!=-1){
	  minpos=pos;
	}
      }
      icu::UnicodeString token;
      text.extractBetween(0,minpos,token);
      text.extractBetween(minpos+1, text.countChar32(), text);
      tokens.emplace_back(token);
      std::cerr<<text<<std::endl<<token<<" "<<minpos<<" "<<pos<<std::endl;
    }while(minpos!=text.countChar32()+minpos);
    return tokens;
  }

  icu::UnicodeString intToStr(int number){
    std::stringstream numberStream;
    numberStream<<number;
    return icu::UnicodeString::fromUTF8(numberStream.str());
  }
}
