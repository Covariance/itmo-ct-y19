module HW1.T4
  (
    tfoldr
  , treeToList
  ) where

import HW1.T3 (Tree (..))

--- | (mapper, init, tree)
tfoldr :: (a -> b -> b) -> b -> Tree a -> b
tfoldr _ val Leaf                     = val
tfoldr f val (Branch _ left el right) = tfoldr f (f el (tfoldr f val right)) left

treeToList :: Tree a -> [a]    -- output list is sorted
treeToList = tfoldr (:) []
