open! Core
open Expression_visitor

let string_input = Command.Param.anon (Command.Anons.( %: ) "INPUT" Command.Param.string)

let functional_command ~summary (f : string -> unit) =
  Command.basic
    ~summary
    [%map_open.Command
      let input = string_input in
      fun () -> f input]
;;

let tokenize_command =
  functional_command ~summary:"Tokenizes expression" (fun input ->
      let tokens = Tokenizer.tokenize input in
      Ast.Token.process
        (module Visitors.PrintVisitor : Ast.Visitor with type out = unit)
        tokens)
;;

let parse_command =
  functional_command ~summary:"Transforms expression to polish notation" (fun input ->
      let tokens = Tokenizer.tokenize input in
      match
        Ast.Token.process
          (module Visitors.ParserVisitor : Ast.Visitor
            with type out = Ast.Token.t list Or_error.t)
          tokens
      with
      | Error error -> print_s [%message "Invalid input: " (error : Error.t)]
      | Ok tokens ->
        Ast.Token.process
          (module Visitors.PrintVisitor : Ast.Visitor with type out = unit)
          tokens)
;;

let compute_command =
  functional_command ~summary:"Computes value of an expression" (fun input ->
      let tokens = Tokenizer.tokenize input in
      match
        Ast.Token.process
          (module Visitors.ParserVisitor : Ast.Visitor
            with type out = Ast.Token.t list Or_error.t)
          tokens
      with
      | Error error -> print_s [%message "Invalid input" (error : Error.t)]
      | Ok tokens ->
        (match
           Ast.Token.process
             (module Visitors.CalcVisitor : Ast.Visitor with type out = int Or_error.t)
             tokens
         with
        | Error error -> print_s [%message "Invalid polish notation" (error : Error.t)]
        | Ok value -> print_s ([%sexp_of: int] value)))
;;

let command =
  Command.group
    ~summary:"Command to run visitor expression parser"
    [ "tokenize", tokenize_command
    ; "polish-notation", parse_command
    ; "compute", compute_command
    ]
;;

let () = Command_unix.run command
