open! Core

module Op = struct
  type t =
    | Add
    | Sub
    | Mul
    | Div
  [@@deriving equal, variants, sexp_of]

  let to_string = function
    | Add -> "ADD"
    | Sub -> "SUB"
    | Mul -> "MUL"
    | Div -> "DIV"
  ;;

  let priority = function
    | Add | Sub -> 1
    | Mul | Div -> 2
  ;;
end

module type Visitor = sig
  type t
  type out

  val create : unit -> t
  val visitVal : t -> int -> t
  val visitOp : t -> Op.t -> t
  val visitPar : t -> [ `Left | `Right ] -> t
  val get : t -> out
end

module Token = struct
  type t =
    | Val of int
    | Op of Op.t
    | Par of [ `Left | `Right ]
  [@@deriving equal, variants, sexp_of]

  let accept (type a) (module V : Visitor with type t = a) (visitor : a) = function
    | Val v -> V.visitVal visitor v
    | Op op -> V.visitOp visitor op
    | Par par -> V.visitPar visitor par
  ;;

  let accept_all (type a) (module V : Visitor with type t = a) (visitor : a) =
    List.fold ~init:visitor ~f:(accept (module V))
  ;;

  let process (type b) (module V : Visitor with type out = b) tokens =
    accept_all (module V) (V.create ()) tokens |> V.get
  ;;
end
