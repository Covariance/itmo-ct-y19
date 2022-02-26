{-# LANGUAGE ScopedTypeVariables #-}

module HW2.T3
  (
      joinOption
    , joinExcept
    , joinAnnotated
    , joinList
    , joinFun
  ) where

import HW2.T1 (Annotated (..), Except (..), Fun (..), List (..), Option (..))


-- | Join nested Options
joinOption :: Option (Option a) -> Option a
joinOption None            = None
joinOption (Some None)     = None
joinOption (Some (Some a)) = Some a


-- | Join nested Excepts
joinExcept :: Except e (Except e a) -> Except e a
joinExcept (Error e)             = Error e
joinExcept (Success (Error e))   = Error e
joinExcept (Success (Success a)) = Success a


-- | Join nested Annotateds
joinAnnotated :: Semigroup e => Annotated e (Annotated e a) -> Annotated e a
joinAnnotated ((a :# e1) :# e2) = a :# (e2 <> e1)


-- | Join nested Lists (aka flatmap)
joinList :: forall a. List (List a) -> List a
joinList Nil = Nil
joinList (a :. at) = innerJoin a (joinList at)
  where
    innerJoin :: List a -> List a -> List a
    innerJoin Nil b       = b
    innerJoin (i :. it) b = i :. innerJoin it b


-- | Join nested Fun
joinFun :: forall i a. Fun i (Fun i a) -> Fun i a
joinFun (F f) = F mapper
  where
    mapper :: i -> a
    mapper i = funApply (f i) i
      where
        funApply :: Fun i a -> i -> a
        funApply (F function) = function
