#ifndef _BIOEBSTRING_H_
#define _BIOEBSTRING_H_
#include <BioebString/BioebString_EXPORT.h>
#include <string>
#include <unicode/unistr.h>
#include <vector>

namespace bioeb{
  BIOEBSTRING_EXPORT std::vector<std::string> tokenize(std::string text, char delimiter);
  BIOEBSTRING_EXPORT std::vector<std::string> tokenize(std::string text, std::string delimeters);
  BIOEBSTRING_EXPORT std::vector<icu::UnicodeString> tokenize(icu::UnicodeString text, UChar delimiter);
  BIOEBSTRING_EXPORT std::vector<icu::UnicodeString> tokenize(icu::UnicodeString text, icu::UnicodeString delmiters);
  BIOEBSTRING_EXPORT icu::UnicodeString intToStr(int number);
}
#endif
