{-# LANGUAGE ScopedTypeVariables #-}

module HW1.T5
  (
    splitOn
  , joinWith
  ) where

import Data.List.NonEmpty (NonEmpty, fromList)

splitOn :: forall a. Eq a => a -> [a] -> NonEmpty [a]
splitOn del arr = fromList (foldr splitter [[]] arr)
  where
    splitter :: a -> [[a]] -> [[a]]
    splitter _ [] = error "must not be used on empty"
    splitter el (partial:completed)
      | el == del = []:partial:completed
      | otherwise = (el:partial):completed

joinWith :: forall a. a -> NonEmpty [a] -> [a]
joinWith sep = foldr1 joiner
  where
    joiner :: [a] -> [a] -> [a]
    joiner el lst = el ++ sep:lst
