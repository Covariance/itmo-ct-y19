{-# LANGUAGE ScopedTypeVariables #-}

module HW0.T2
  (
    Not
  , doubleNeg
  , reduceTripleNeg
  ) where

import Data.Void (Void)

type Not a = a -> Void

-- | Basically (a -> Not (Not a)) means (a -> (a -> Void) -> Void)
-- | So we can quite literraly apply our "lie" to the first argument
-- | And get a Void
doubleNeg :: a -> Not (Not a)
doubleNeg a lier = lier a

-- | Again, let's find out the type of this thing:
-- | (((a -> Void) -> Void) -> Void) -> Void
-- | And it becomes pretty clear how to reduce it using double negation
reduceTripleNeg :: Not (Not (Not a)) -> Not a
reduceTripleNeg lier a = lier (doubleNeg a)
