open! Core
module ParserVisitor : Ast.Visitor with type out = Ast.Token.t List.t Or_error.t
module PrintVisitor : Ast.Visitor with type out = unit
module CalcVisitor : Ast.Visitor with type out = int Or_error.t
