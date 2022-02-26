{-# LANGUAGE ScopedTypeVariables #-}

module HW2.T1
  (
    Option(..)
  , Pair(..)
  , Quad(..)
  , Annotated(..)
  , Except(..)
  , Prioritised(..)
  , Stream(..)
  , List(..)
  , Fun(..)
  , Tree(..)
  , mapOption
  , mapPair
  , mapQuad
  , mapAnnotated
  , mapExcept
  , mapPrioritised
  , mapStream
  , mapList
  , mapFun
  , mapTree
  ) where


data Option a = None | Some a


data Pair a = P a a


data Quad a = Q a a a a


infix 0 :#
data Annotated e a = a :# e deriving Show


data Except e a = Error e | Success a deriving Show


data Prioritised a = Low a | Medium a | High a


infixr 5 :>
data Stream a = a :> Stream a


infixr 5 :.
data List a = Nil | a :. List a


newtype Fun i a = F (i -> a)


data Tree a = Leaf | Branch (Tree a) a (Tree a)


-- | Maps value inside Option
mapOption :: forall a b. (a -> b) -> (Option a -> Option b)
mapOption f = mapper
  where
    mapper :: Option a -> Option b
    mapper None     = None
    mapper (Some a) = Some (f a)


-- | Maps all values inside Pair
mapPair :: forall a b. (a -> b) -> (Pair a -> Pair b)
mapPair f = mapper
  where
    mapper :: Pair a -> Pair b
    mapper (P a1 a2) = P (f a1) (f a2)


-- | Maps all values indide Quad
mapQuad :: forall a b. (a -> b) -> (Quad a -> Quad b)
mapQuad f = mapper
  where
    mapper :: Quad a -> Quad b
    mapper (Q a1 a2 a3 a4) = Q (f a1) (f a2) (f a3) (f a4)


-- | Maps value inside Annotated, leaving annotation intact
mapAnnotated :: forall e a b. (a -> b) -> (Annotated e a -> Annotated e b)
mapAnnotated f = mapper
  where
    mapper :: Annotated e a -> Annotated e b
    mapper (a :# e) = f a :# e


-- | Maps value inside Except
mapExcept :: forall e a b. (a -> b) -> (Except e a -> Except e b)
mapExcept f = mapper
  where
    mapper :: Except e a -> Except e b
    mapper (Error e)   = Error e
    mapper (Success a) = Success (f a)


-- | Maps value inside Prioritised
mapPrioritised :: forall a b. (a -> b) -> (Prioritised a -> Prioritised b)
mapPrioritised f = mapper
  where
    mapper :: Prioritised a -> Prioritised b
    mapper (Low a)    = Low (f a)
    mapper (Medium a) = Medium (f a)
    mapper (High a)   = High (f a)


-- | Maps all values inside Stream
mapStream :: forall a b. (a -> b) -> (Stream a -> Stream b)
mapStream f = mapper
  where
    mapper :: Stream a -> Stream b
    mapper (a :> b) = f a :> mapper b


-- | Maps all values inside list
mapList :: forall a b. (a -> b) -> (List a -> List b)
mapList f = mapper
  where
    mapper :: List a -> List b
    mapper Nil      = Nil
    mapper (a :. b) = f a :. mapper b


-- | Maps function output value
mapFun :: forall i a b. (a -> b) -> (Fun i a -> Fun i b)
mapFun f = mapper
  where
    mapper :: Fun i a -> Fun i b
    mapper (F g) = F (f . g)


-- | Maps all values in Tree nodes
mapTree :: forall a b. (a -> b) -> (Tree a -> Tree b)
mapTree f = mapper
  where
    mapper :: Tree a -> Tree b
    mapper Leaf           = Leaf
    mapper (Branch a b c) = Branch (mapper a) (f b) (mapper c)
