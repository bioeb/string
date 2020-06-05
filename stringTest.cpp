#include "BioebString.h"

#include <iostream>

int main(int c, char **argv){
  std::string line="Hello World";
  char delimiter=' ';
  std::vector<std::string> tokens;
  std::cout<<"Tokenize Test 1: "<<line<<" : `"<<delimiter<<"`"<<std::endl;
  tokens=bioeb::tokenize(line, delimiter);
  for(auto token: tokens){
    std::cout<<"token:`"<<token<<"`"<<std::endl;
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
  return 0;
}
