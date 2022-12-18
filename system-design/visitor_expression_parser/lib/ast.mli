open! Core

module Op : sig
  type t =
    | Add
    | Sub
    | Mul
    | Div
  [@@deriving equal, variants, sexp_of]

  val to_string : t -> string
  val priority : t -> int
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

module Token : sig
  type t =
    | Val of int
    | Op of Op.t
    | Par of [ `Left | `Right ]
  [@@deriving equal, variants, sexp_of]

  val accept : (module Visitor with type t = 'a) -> 'a -> t -> 'a
  val accept_all : (module Visitor with type t = 'a) -> 'a -> t list -> 'a
  val process : (module Visitor with type out = 'b) -> t list -> 'b
end
