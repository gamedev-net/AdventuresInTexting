#pragma once
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str);

std::string getArticle(std::string word);

std::string listThings(std::vector<std::string> things, bool articles = false);
