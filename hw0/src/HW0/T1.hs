{-# LANGUAGE ScopedTypeVariables #-}
{-# LANGUAGE TypeOperators       #-}

module HW0.T1
  (
    type(<->)(..)
  , flipIso
  , runIso
  , distrib
  , assocPair
  , assocEither
  ) where

data a <-> b = Iso (a -> b) (b -> a)

flipIso :: (a <-> b) -> (b <-> a)
flipIso (Iso f g) = Iso g f

runIso :: (a <-> b) -> (a -> b)
runIso (Iso f _) = f

-- | If a is set, then propagate it to both Eithers, otherwise, populate them
-- | with corresponding values
distrib :: Either a (b, c) -> (Either a b, Either a c)
distrib (Left a)       = (Left a, Left a)
distrib (Right (b, c)) = (Right b, Right c)

-- | Creates Iso by moving middle element between pairs
assocPair :: forall a b c. (a, (b, c)) <-> ((a, b), c)
assocPair = Iso forward backward
  where
    forward :: (a, (b, c)) -> ((a, b), c)
    forward (a, (b, c)) = ((a, b), c)

    backward :: ((a, b), c) -> (a, (b, c))
    backward ((a, b), c) = (a, (b, c))

-- | Creates Iso with Eithers by moving middle element between Eithers
assocEither :: forall a b c. Either a (Either b c) <-> Either (Either a b) c
assocEither = Iso forward backward
  where
    forward :: Either a (Either b c) -> Either (Either a b) c
    forward (Left a)          = Left (Left a)
    forward (Right (Left b))  = Left (Right b)
    forward (Right (Right c)) = Right c

    backward :: Either (Either a b) c -> Either a (Either b c)
    backward (Left (Left a))  = Left a
    backward (Left (Right b)) = Right (Left b)
    backward (Right c)        = Right (Right c)
