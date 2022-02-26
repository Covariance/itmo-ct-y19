module HW1.T7
  (
    ListPlus(..)
  , Inclusive(..)
  , DotString(..)
  , Fun(..)
  ) where

import Prelude

data ListPlus a
  = a :+ ListPlus a
  | Last a

infixr 5 :+

instance Semigroup (ListPlus a) where
  (<>) (Last a) back = a :+ back
  (<>) (a :+ b) back = a :+ (b <> back)

data Inclusive a b
  = This a
  | That b
  | Both a b

instance (Semigroup a, Semigroup b) => Semigroup (Inclusive a b) where
  (<>) (This a1) (This a2)       = This (a1 <> a2)
  (<>) (This a1) (That b2)       = Both a1 b2
  (<>) (This a1) (Both a2 b2)    = Both (a1 <> a2) b2
  (<>) (That b1) (This a2)       = Both a2 b1
  (<>) (That b1) (That b2)       = That (b1 <> b2)
  (<>) (That b1) (Both a2 b2)    = Both a2 (b1 <> b2)
  (<>) (Both a1 b1) (This a2)    = Both (a1 <> a2) b1
  (<>) (Both a1 b1) (That b2)    = Both a1 (b1 <> b2)
  (<>) (Both a1 b1) (Both a2 b2) = Both (a1 <> a2) (b1 <> b2)

newtype DotString = DS String

instance Semigroup DotString where
  (<>) (DS "") (DS s2) = DS s2
  (<>) (DS s1) (DS "") = DS s1
  (<>) (DS s1) (DS s2) = DS (s1 ++ "." ++ s2)

instance Monoid DotString where
  mempty = DS ""

newtype Fun a = F (a -> a)

instance Semigroup (Fun a) where
  (<>) (F a) (F b) = F $ a . b

instance Monoid (Fun a) where
  mempty = F iden
    where
      iden :: b -> b
      iden b1 = b1
