{-# LANGUAGE ScopedTypeVariables #-}

module HW1.T6
  (
    mcat
  , epart
  ) where

mcat :: forall a. Monoid a => [Maybe a] -> a
mcat = foldr extractor mempty
  where
    extractor :: Maybe a -> a -> a
    extractor Nothing acc    = acc
    extractor (Just val) acc = val <> acc

epart :: forall a b. (Monoid a, Monoid b) => [Either a b] -> (a, b)
epart = foldr extractor (mempty, mempty)
  where
    extractor :: Either a b -> (a, b) -> (a, b)
    extractor (Left val) (a, b)  = (val <> a, b)
    extractor (Right val) (a, b) = (a, val <> b)
