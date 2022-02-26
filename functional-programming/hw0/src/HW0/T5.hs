module HW0.T5
  (
    Nat
  , nz
  , ns
  , nplus
  , nmult
  , nFromNatural
  , nToNum
  ) where

import Numeric.Natural (Natural)

type Nat a = (a -> a) -> a -> a

-- | Zero in church numerals
-- | returns its input withput applying anything to it
nz :: Nat a
nz _ a = a

-- | Next in church numerals
-- | returns result of function application to the result
-- | of an inner numeral, therefore increasing overall number
-- | of applications by one
ns :: Nat a -> Nat a
ns x f a = f (x f a)

-- | Sum of church numerals
-- | returns result of application function with one of the numerals
-- | to the result of application function with other to the initial value
nplus :: Nat a -> Nat a -> Nat a
nplus x y f a = y f (x f a)

-- | Multiplication of church numerals
-- | returns result of application one numeral applying function with
-- | other numeral (basically like doing 'y' x times)
nmult :: Nat a -> Nat a -> Nat a
nmult x y f = y (x f)

-- | Makes church numeral from natural number
-- | it is a basic recursion
nFromNatural :: Natural -> Nat a
nFromNatural 0 = nz
nFromNatural n = ns (nFromNatural (n - 1))

-- | Returns number corresponding to the church number
-- | applies '+ 1' function with numeral to 0
nToNum :: Num a => Nat a -> a
nToNum church = church (+ 1) 0
