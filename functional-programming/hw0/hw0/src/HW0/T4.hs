{-# LANGUAGE ScopedTypeVariables #-}

module HW0.T4
  (
    repeat'
  , map'
  , fib
  , fac
  ) where

import Data.Function (fix)
import Numeric.Natural (Natural)

-- | Actually an example from statement
repeat' :: a -> [a]
repeat' x = fix (x:)

-- | We need to find such tail mapper that it would map the list itself
map' :: forall a b. (a -> b) -> [a] -> [b]  -- behaves like Data.List.map
map' mapper = fix innerMap
  where
    innerMap :: ([a] -> [b]) -> [a] -> [b]
    innerMap tailMapper (x:xs) = mapper x : tailMapper xs
    innerMap _ []              = []

-- | We need to find such mapper that it would map big numbers as fibonacci
-- | Here we actually need something a bit harder than in factorial,
-- | because there would be two recursive calls in the naive implementation,
-- | and therefore we need to provide an accumulator, which expands signature
-- | of our function to (Natural -> Natural -> Natural -> Natural)
fib :: Natural -> Natural
fib = fix fibAccumulated 1 0
  where
    fibAccumulated
      :: (Natural -> Natural -> Natural -> Natural)
      -> Natural
      -> Natural
      -> Natural
      -> Natural
    fibAccumulated _ _ b 0 = b
    fibAccumulated f a b n = f b (a + b) (n - 1)

-- | We need to find such mapper that it would map big numbers as factorial
fac :: Natural -> Natural
fac = fix unfixedFac
  where
    unfixedFac :: (Natural -> Natural) -> Natural -> Natural
    unfixedFac f n = if n < 2 then 1 else n * f (n - 1)
