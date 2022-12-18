open! Core

module ParserVisitor = struct
  type state =
    { output : Ast.Token.t list
    ; stack : Ast.Token.t list
    }

  type t = state Or_error.t
  type out = Ast.Token.t List.t Or_error.t

  let create () = Or_error.return { output = []; stack = [] }

  let visitVal t v =
    let%map.Or_error t = t in
    { t with output = Ast.Token.Val v :: t.output }
  ;;

  let visitOp t op =
    let%bind.Or_error { output; stack } = t in
    let before, after =
      List.split_while stack ~f:(function
          | Ast.Token.Val (_ : int) ->
            raise_s [%message "Incorrect state: value on stack"]
          | Ast.Token.Par _ -> false
          | Ast.Token.Op otherOp -> Ast.Op.priority otherOp < Ast.Op.priority op)
    in
    Or_error.return { stack = Ast.Token.Op op :: after; output = before @ output }
  ;;

  let visitPar t par =
    let%bind.Or_error { output; stack } = t in
    match par with
    | `Left -> Or_error.return { stack = Ast.Token.Par `Left :: stack; output }
    | `Right ->
      let before, after =
        List.split_while stack ~f:(fun x -> not (Ast.Token.equal x (Par `Left)))
      in
      (match after with
      | [] -> Or_error.error_string "Not matching parenthesis"
      | _ :: stack -> Or_error.return { stack; output = before @ output })
  ;;

  let get t =
    let%map.Or_error { output; stack } = t in
    List.rev stack @ output
  ;;
end

module PrintVisitor = struct
  type t =
    [ `Has_not_printed
    | `Has_printed
    ]

  type out = unit

  let space_aware_print t str =
    let () =
      match t with
      | `Has_not_printed -> print_string str
      | `Has_printed -> print_string (" " ^ str)
    in
    `Has_printed
  ;;

  let create () = `Has_not_printed
  let visitVal t v = v |> Int.to_string |> space_aware_print t
  let visitOp t (op : Ast.Op.t) = op |> Ast.Op.to_string |> space_aware_print t

  let visitPar t par =
    (match par with
    | `Left -> "("
    | `Right -> ")")
    |> space_aware_print t
  ;;

  let get = ignore
end

module CalcVisitor = struct
  type t = int list Or_error.t
  type out = int Or_error.t

  let create () = Or_error.return []
  let visitVal t v = Or_error.map t ~f:(fun t -> v :: t)

  let visitOp t (op : Ast.Op.t) =
    match%bind.Or_error t with
    | a :: b :: rest ->
      (match op with
      | Add -> a + b
      | Sub -> b - a
      | Mul -> a * b
      | Div -> b / a)
      :: rest
      |> Or_error.return
    | _ ->
      "Not enough values on the stack for operation: " ^ Ast.Op.to_string op
      |> Or_error.error_string
  ;;

  let visitPar (_ : t) (_ : [ `Left | `Right ]) =
    Or_error.error_string "CalcVisitor does not accept parenthesis as an input"
  ;;

  let get t =
    match%bind.Or_error t with
    | [ a ] -> Or_error.return a
    | [] -> Or_error.error_string "No values on the stack"
    | other ->
      "Too many values on the stack: " ^ (other |> List.length |> Int.to_string)
      |> Or_error.error_string
  ;;
end
