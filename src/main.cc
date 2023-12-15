#include "sexp.h"
#include <format>
#include <iostream>

using namespace racketlike;

int main(int argc, char *argv[]) {
  std::string str;
  while (std::getline(std::cin, str)) {
    try {
      auto result = sexp::parseSExp(str);
      sexp::SExp sexp = result.first;
      std::cout << sexp << std::endl;
    } catch (sexp::ParseError &e) {
      std::cout << std::format("Parse error: {}", e.what()) << std::endl;
    }
  }
}
