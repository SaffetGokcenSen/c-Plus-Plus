#ifndef GUARD_LETTER_CASE
#define GUARD_LETTER_CASE

#include <iostream>
#include <list>
#include <string>

std::istream& read_words(std::istream&, std::list<std::string>&);

bool uppercase_inclusion(std::string&);

#endif