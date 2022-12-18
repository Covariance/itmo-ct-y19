open! Core

let tokenize input =
  let token_of_buf buf =
    Ast.Token.Val (buf |> List.rev |> String.of_char_list |> Int.of_string)
  in
  let rec split chars tokens num =
    match num with
    | `Not_number ->
      (match chars with
      | [] -> List.rev tokens
      | ' ' :: rest -> split rest tokens `Not_number
      | '(' :: rest -> split rest (Ast.Token.Par `Left :: tokens) `Not_number
      | ')' :: rest -> split rest (Ast.Token.Par `Right :: tokens) `Not_number
      | '+' :: rest -> split rest (Ast.Token.Op Ast.Op.Add :: tokens) `Not_number
      | '-' :: rest -> split rest (Ast.Token.Op Ast.Op.Sub :: tokens) `Not_number
      | '*' :: rest -> split rest (Ast.Token.Op Ast.Op.Mul :: tokens) `Not_number
      | '/' :: rest -> split rest (Ast.Token.Op Ast.Op.Div :: tokens) `Not_number
      | fs :: rest ->
        if Char.is_digit fs
        then split rest tokens (`Number [ fs ])
        else raise_s [%message "Invalid symbol: " (fs : char)])
    | `Number buf ->
      (match chars with
      | [] -> split [] (token_of_buf buf :: tokens) `Not_number
      | fs :: rest ->
        if Char.is_digit fs
        then split rest tokens (`Number (fs :: buf))
        else split chars (token_of_buf buf :: tokens) `Not_number)
  in
  split (String.to_list input) [] `Not_number
;;

let%expect_test "Tokenizer correctness" =
  tokenize "(1 + 2) - 3 * (6 / 2)" |> [%sexp_of: Ast.Token.t list] |> print_s;
  [%expect
    {| 
    ((Par Left) (Val 1) (Op Add) (Val 2) (Par Right) (Op Sub) (Val 3) (Op Mul)
     (Par Left) (Val 6) (Op Div) (Val 2) (Par Right)) 
    |}]
;;
