#ifndef ___PROJECT_1_CONVERT_HPP
#define ___PROJECT_1_CONVERT_HPP

#include <string>
#include "Wordset.hpp"

void loadWordsIntoTable(WordSet & words, std::istream & in);

std::string convert(const std::string & s1, const std::string & s2, const WordSet & words);

#endif
