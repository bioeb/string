#include "yaml.h"
#include <BioebString.h>
#include <unicode/ustream.h>
#include <fstream>
#include <iostream>

int main(int c, char **argv){

  YAML::Node tests = YAML::LoadFile(argv[1]);
  for(YAML::const_iterator it=tests.begin();it!=tests.end();++it){
    auto &first=(*it).first;
    auto &second=(*it).second;
    icu::UnicodeString testName=icu::UnicodeString::fromUTF8(first.as<std::string>());
    icu::UnicodeString testLine=icu::UnicodeString::fromUTF8(second["line"].as<std::string>());
    icu::UnicodeString testDelimiter=icu::UnicodeString::fromUTF8(second["delimiter"].as<std::string>());
    auto &results=(*it).second["result"];

    std::vector<icu::UnicodeString> testTokens=bioeb::tokenize(testLine,testDelimiter);
    if(testTokens.size() == results.size()){
      int i =0;
      for(YAML::const_iterator it_r=results.begin();it_r!=results.end();++it_r){
	icu::UnicodeString result=icu::UnicodeString::fromUTF8((*it_r).as<std::string>());
	//std::cout<<"Compare "<<result<<" "<<testTokens[i]<<std::endl;
	if(result!=testTokens[i]){
	  std::cout<<testName<<" FAILED"<<std::endl;
	  break;
	}
	++i;
      }
      if(i==testTokens.size()){
	std::cout<<testName<<" PASSED"<<std::endl;
      }
    }else{
      std::cout<<testName<<" FAILED"<<std::endl;
    }
  }
  return 0;
}
