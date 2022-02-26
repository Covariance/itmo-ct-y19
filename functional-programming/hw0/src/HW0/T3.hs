module HW0.T3
  (
    s
  , k
  , i
  , compose
  , contract
  , permute
  ) where

s :: (a -> b -> c) -> (a -> b) -> (a -> c)
s f g x = f x (g x)

k :: a -> b -> a
k x _ = x

-- | For this module I would give no explanations of what is
-- | happening here, because it is magic of combinators
-- | and is pretty much unexplainable by words
-- | (or I am bad with words)

i :: a -> a
i = s k k

compose :: (b -> c) -> (a -> b) -> (a -> c)
compose = s (k s) k

contract :: (a -> a -> b) -> (a -> b)
contract = s s (k (s k k))

permute :: (a -> b -> c) -> (b -> a -> c)
permute = s (s (k s) k (s (k s) k) s) (k k)
