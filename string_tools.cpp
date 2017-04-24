#include "string_tools.h"

#include <sstream>

std::vector<std::string> split(const std::string& str) {
  std::string buf; // Have a buffer string
  std::stringstream ss(str); // Insert the string into a stream
  std::vector<std::string> tokens; // Create vector to hold our words

  while (ss >> buf)
    tokens.push_back(buf);

  return tokens;
}

std::string getArticle(std::string word) {
  static const std::vector<char> vowels = { 'a', 'e', 'i', 'o', 'u' };
  auto iter = std::find(vowels.begin(), vowels.end(), word[0]);
  if(iter == vowels.end()) { return "a"; }
  return "an";
}

std::string listThings(std::vector<std::string> things, bool articles) {
  std::stringstream ss;

  if(!things.empty()) {
    size_t lastIndex = things.size() - 1;
    for(size_t i = 0; i < lastIndex; i++) {
      if(articles) { ss << getArticle(things[i]); }
      ss << things[i];
      if(things.size() > 2) { ss << ","; }
      ss << " ";
      //if(i < lastIndex) { ss << ", "; }
    }

    if(things.size() > 1) { ss << "and "; }
    if(articles) { ss << getArticle(things[lastIndex]); }
    ss << things[lastIndex];
  }

  return ss.str();
}

