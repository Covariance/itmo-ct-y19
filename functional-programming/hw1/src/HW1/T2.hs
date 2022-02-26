module HW1.T2
  (
    N(..)
  , nplus
  , nmult
  , nsub
  , ncmp
  , nFromNatural
  , nToNum
  , nEven
  , nOdd
  , ndiv
  , nmod
  ) where

import GHC.Natural (Natural)

data N
  = Z
  | S N

nplus :: N -> N -> N
nplus n Z     = n
nplus n (S k) = S(nplus n k)

nmult :: N -> N -> N
nmult _ Z     = Z
nmult n (S k) = nplus (nmult n k) n

nsub :: N -> N -> Maybe N
nsub n Z         = Just n
nsub Z _         = Nothing
nsub (S n) (S k) = nsub n k

ncmp :: N -> N -> Ordering
ncmp Z Z         = EQ
ncmp _ Z         = GT
ncmp Z _         = LT
ncmp (S n) (S k) = ncmp n k

nFromNatural :: Natural -> N
nFromNatural 0 = Z
nFromNatural x = S (nFromNatural (x - 1))

nToNum :: Num a => N -> a
nToNum Z     = 0
nToNum (S n) = nToNum n + 1

nEven, nOdd :: N -> Bool
nEven Z     = True
nEven (S n) = nOdd n
nOdd Z     = False
nOdd (S n) = nEven n

ndiv :: N -> N -> N
ndiv _ Z = error "dbz"
ndiv n k = case nsub n k of
  Just nmk -> S (ndiv nmk k)
  Nothing  -> Z

nmod :: N -> N -> N
nmod _ Z = error "dbz"
nmod n k = case nsub n k of
  Just nmk -> nmod nmk k
  Nothing  -> n
