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
/* struct SExp; */

/* struct SExp { */
/*   virtual ~SExp() = default; */
/**/
/*   virtual std::ostream &print(std::ostream &os) const = 0; */
/* }; */

using SExp = std::variant<Atom, Exp>;

template <typename... Types>
std::ostream &operator<<(std::ostream &os,
                         const std::variant<Types...> &variant) {
  std::visit([&os](const auto &value) { os << value; }, variant);
  return os;
}

struct Atom {
  std::string value;

  Atom(std::string value);
};

std::ostream &operator<<(std::ostream &os, const Atom &atom);

struct Exp {
  std::vector<SExp> sexps;

  Exp(std::vector<SExp> sexps);
};

std::ostream &operator<<(std::ostream &os, const Exp &exp);

class ParseError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

std::pair<SExp, std::string_view> parseSExp(std::string_view str);

} // namespace racketlike::sexp
