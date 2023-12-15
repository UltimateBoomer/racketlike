#pragma once

#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace racketlike::sexp {

struct Atom;
struct Exp;

using SExp = std::variant<Atom, Exp>;

/* template <typename... Types> */

struct Atom {
  std::string value;
};

std::ostream &operator<<(std::ostream &os, const Atom &atom);

struct Exp {
  std::vector<SExp> sexps;
};

std::ostream &operator<<(std::ostream &os, const Exp &exp);

std::ostream &operator<<(std::ostream &os, const SExp &variant);

class ParseError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

std::pair<SExp, std::string_view> parseSExp(std::string_view str);

} // namespace racketlike::sexp
