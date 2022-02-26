{-# LANGUAGE ScopedTypeVariables #-}

module HW2.T2
  (
    distOption
  , distPair
  , distQuad
  , distAnnotated
  , distExcept
  , distPrioritised
  , distStream
  , distList
  , distFun
  , wrapOption
  , wrapPair
  , wrapQuad
  , wrapAnnotated
  , wrapExcept
  , wrapPrioritised
  , wrapStream
  , wrapList
  , wrapFun
  ) where

import HW2.T1 (Annotated (..), Except (..), Fun (..), List (..), Option (..), Pair (..),
               Prioritised (..), Quad (..), Stream (..))


-- | Combines two Options together
distOption :: forall a b. (Option a, Option b) -> Option (a, b)
distOption (None, _)        = None
distOption (_, None)        = None
distOption (Some a, Some b) = Some (a, b)


-- | Combines two Pairs together
distPair :: (Pair a, Pair b) -> Pair (a, b)
distPair (P a1 a2, P b1 b2) = P (a1, b1) (a2, b2)


-- | Combines two Quads together
distQuad :: (Quad a, Quad b) -> Quad (a, b)
distQuad (Q a1 a2 a3 a4, Q b1 b2 b3 b4) = Q (a1, b1) (a2, b2) (a3, b3) (a4, b4)


-- | Combines two Annotateds together, following Semigroup laws for
distAnnotated :: Semigroup e => (Annotated e a, Annotated e b) -> Annotated e (a, b)
distAnnotated (a :# e1, b :# e2) = (a, b) :# (e1 <> e2)


-- | Combines two Excepts together, keeping first error
distExcept :: (Except e a, Except e b) -> Except e (a, b)
distExcept (Error e, _)           = Error e
distExcept (_, Error e)           = Error e
distExcept (Success a, Success b) = Success (a, b)


-- | Combines two Prioriteseds together, keeping higher priority
distPrioritised :: (Prioritised a, Prioritised b) -> Prioritised (a, b)
distPrioritised (High a, High b)     = High (a, b)
distPrioritised (High a, Medium b)   = High (a, b)
distPrioritised (High a, Low b)      = High (a, b)
distPrioritised (Medium a, High b)   = High (a, b)
distPrioritised (Medium a, Medium b) = Medium (a, b)
distPrioritised (Medium a, Low b)    = Medium (a, b)
distPrioritised (Low a, High b)      = High (a, b)
distPrioritised (Low a, Medium b)    = Medium (a, b)
distPrioritised (Low a, Low b)       = Low (a, b)


-- | Combines two Streams together
distStream :: (Stream a, Stream b) -> Stream (a, b)
distStream (a :> at, b :> bt) = (a, b) :> distStream (at, bt)


-- | Combines two Lists together via cartesian product
distList :: forall a b. (List a, List b) -> List (a, b)
distList (Nil, _)           = Nil
distList (_, Nil)           = Nil
distList (a :. at, b) = concatLists (cartesianProduct a b) (distList (at, b))
  where
    concatLists :: forall c. List c -> List c -> List c
    concatLists Nil second                  = second
    concatLists first Nil                   = first
    concatLists (first :. firstTail) second = first :. concatLists firstTail second

    cartesianProduct :: a -> List b -> List (a, b)
    cartesianProduct _ Nil               = Nil
    cartesianProduct el (lst :. lstTail) = (el, lst) :. cartesianProduct el lstTail

-- | Combines two Funs together
distFun :: forall i a b. (Fun i a, Fun i b) -> Fun i (a, b)
distFun (F fa, F fb) = F dist
  where
    dist :: i -> (a, b)
    dist i = (fa i, fb i)


-- | Wraps value in Option
wrapOption :: a -> Option a
wrapOption = Some


-- | Wraps value in Pair
wrapPair :: a -> Pair a
wrapPair a = P a a


-- | Wraps value in Quad
wrapQuad :: a -> Quad a
wrapQuad a = Q a a a a


-- | Wraps value in Annotated, annotating it with mempty
wrapAnnotated :: Monoid e => a -> Annotated e a
wrapAnnotated a = a :# mempty


-- | Wraps value in Except
wrapExcept :: a -> Except e a
wrapExcept = Success


-- | Wraps value in Prioritised with High priority
wrapPrioritised :: a -> Prioritised a
wrapPrioritised = Low


-- | Wraps value in infinite Stream
wrapStream :: a -> Stream a
wrapStream a = a :> wrapStream a


-- | Wraps value in List of one element
wrapList :: a -> List a
wrapList a = a :. Nil


-- | Wraps value in constant Fun
wrapFun :: a -> Fun i a
wrapFun a = F f
  where
    f _ = a
