#ifndef _BIOEBSTRING_H_
#define _BIOEBSTRING_H_
#include <string>
#include <unicode/unistr.h>
#include <vector>

namespace bioeb{
  std::vector<std::string> tokenize(std::string text, char delimiter);
  std::vector<std::string> tokenize(std::string text, std::string delimeters);
  std::vector<icu::UnicodeString> tokenize(icu::UnicodeString text, UChar delimiter);
  std::vector<icu::UnicodeString> tokenize(icu::UnicodeString text, icu::UnicodeString delmiters);
  icu::UnicodeString intToStr(int number);
}
#endif
