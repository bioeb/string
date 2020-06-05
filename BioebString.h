#ifndef _BIOEBSTRING_H_
#define _BIOEBSTRING_H_
#include <string>
#include <vector>

namespace bioeb{
  std::vector<std::string> tokenize(std::string text, char delimiter);
  std::vector<std::string> tokenize(std::string text, std::string delimeters);
}
#endif
