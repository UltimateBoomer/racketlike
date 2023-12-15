#include "sexp.h"
#include <cctype>
#include <ostream>
#include <string_view>

namespace racketlike::sexp {

Atom::Atom(std::string value) : value(value) {}

std::ostream &operator<<(std::ostream &os, const Atom &atom) {
  return os << atom.value;
}

Exp::Exp(std::vector<SExp> sexps) : sexps(sexps) {}

std::ostream &operator<<(std::ostream &os, const Exp &exp) {
  os << "(";
  for (auto it = exp.sexps.begin(); it != exp.sexps.end(); ++it) {
    if (it != exp.sexps.begin())
      os << " ";
    os << *it;
  }
  return os << ")";
}

std::string_view skipWhiteSpace(std::string_view str) {
  while (!str.empty() && std::isspace(str.front())) {
    str.remove_prefix(1);
  }
  return str;
}

std::pair<SExp, std::string_view> parseAtom(std::string_view str) {
  str = skipWhiteSpace(str);
  auto str2 = str;
  while (!str2.empty() && str2.front() != ')' && !std::isspace(str2.front())) {
    str2.remove_prefix(1);
  }
  return std::make_pair(Atom(std::string(str.begin(), str2.begin())), str2);
}

std::pair<SExp, std::string_view> parseExp(std::string_view str) {
  str = skipWhiteSpace(str);
  std::vector<SExp> sexps;
  while (!str.empty() && str.front() != ')') {
    auto [sexp, next] = parseSExp(str);
    sexps.emplace_back(sexp);
    str = skipWhiteSpace(next);
  }
  if (str.empty()) {
    throw ParseError("Bracket not closed");
  }
  str.remove_prefix(1);
  return std::make_pair(Exp(std::move(sexps)), str);
}

std::pair<SExp, std::string_view> parseSExp(std::string_view str) {
  str = skipWhiteSpace(str);
  if (str.front() == '(') {
    str.remove_prefix(1);
    return parseExp(str);
  } else {
    return parseAtom(str);
  }
}
} // namespace racketlike::sexp
