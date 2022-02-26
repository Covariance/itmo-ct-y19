module HW0.T6
  (
    a
  , b
  , c
  , a_whnf
  , b_whnf
  , c_whnf
  ) where

import Data.Char (isSpace)
import HW0.T1 (distrib)

a :: (Either [Char] b, Either [Char] c)
a = distrib (Left ("AB" ++ "CD" ++ "EF"))

b :: [Bool]
b = map isSpace "Hello, World"

c :: [Char]
c = if 1 > 0 || error "X" then "Y" else "Z"

-- | All thanks to https://wiki.haskell.org/Weak_head_normal_form
-- | everything here reduces to constructor so nothing interesting

-- | a constructor (eventually applied to arguments)
a_whnf :: (Either [Char] b, Either [Char] c)
a_whnf = (Left ("AB" ++ "CD" ++ "EF"), Left ("AB" ++ "CD" ++ "EF"))

-- | a constructor (eventually applied to arguments)
b_whnf :: [Bool]
b_whnf = (:) (isSpace 'H') (map isSpace "ello, World")

-- | a constructor (eventually applied to arguments)
c_whnf :: [Char]
c_whnf = "Y"
