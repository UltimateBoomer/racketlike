#pragma once

#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace racketlike::beginner {

struct FuncExpr;
struct IfExpr;
struct AndExpr;
struct OrExpr;
struct VarExpr;
struct SymExpr;
struct NumExpr;
struct BoolExpr;
struct StrExpr;
struct CharExpr;

using Expr = std::variant<FuncExpr, IfExpr, AndExpr, OrExpr, VarExpr, SymExpr,
                          NumExpr, BoolExpr, StrExpr>;

struct VarDef;

using Def = std::variant<VarDef>;

struct FuncExpr {
  std::string name;
  std::vector<Expr> exprs;
};

struct IfExpr {
  std::unique_ptr<Expr> inputExpr;
  std::unique_ptr<Expr> trueExpr;
  std::unique_ptr<Expr> falseExpr;
};

struct AndExpr {
  std::vector<Expr> exprs;
};

struct OrExpr {
  std::vector<Expr> exprs;
};

struct VarExpr {
  std::string name;
};

struct SymExpr {
  std::hash<std::string> sym;
};

struct NumExpr {
  int v;
};

struct BoolExpr {
  bool v;
};

struct StrExpr {
  std::string str;
};

struct CharExpr {
  char c;
};

struct VarDef {
  std::string name;
  Expr expr;
};
} // namespace racketlike::beginner
