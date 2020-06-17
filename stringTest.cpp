#include "BioebString.h"
#include <unicode/ustream.h>
#include <iostream>

int main(int c, char **argv){
  std::string line="Hello World";
  char delimiter=' ';
  std::vector<std::string> tokens;
  std::cout<<"Tokenize Test 1: "<<line<<" : `"<<delimiter<<"`"<<std::endl;
  tokens=bioeb::tokenize(line, delimiter);
  for(auto token: tokens){
    std::cout<<"token :`"<<token<<"`"<<std::endl;
  }

  std::string line2="Hello - World";
  std::string delimiter2=" -";
  std::cout<<"Tokenize Test 2: "<<line2<<" : `"<<delimiter2<<"`"<<std::endl;
  std::vector<std::string> tokens2;
  tokens2=bioeb::tokenize(line2," -");
  int i=0;
  for(auto token: tokens2){
    ++i;
    std::cout<<"token "<<i<<":`"<<token<<"`"<<std::endl;
  }


  icu::UnicodeString line3="Hello 부 World";
  std::cout<<"ICU Tokenize UChar"<<std::endl;
  UChar delimiter3=U'부';
  std::vector<icu::UnicodeString> tokens3;
  tokens3=bioeb::tokenize(line3,delimiter3);
  i=0;
  for(auto &token: tokens3){
    ++i;
    std::cout<<"token "<<i<<":`"<<token<<"`"<<std::endl;
  }

  icu::UnicodeString line4="Hello 부 World - Goodbye부$부-World";
  std::cout<<"ICU Tokenize Unicodestring"<<std::endl;
  icu::UnicodeString delimiter4=UNICODE_STRING("부 -", 3);
  std::vector<icu::UnicodeString> tokens4;
  tokens4=bioeb::tokenize(line4,delimiter4);
  i=0;
  for(auto &token: tokens4){
    ++i;
    std::cout<<"token "<<i<<":`"<<token<<"`"<<std::endl;
  }

  return 0;
}
