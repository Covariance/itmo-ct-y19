module HW1.T3
  (
    Tree (..)
  , tsize
  , tdepth
  , tdiff
  , tmember
  , mkBranch
  , tinsert
  , tFromList
  , tostring
  ) where

data Tree a
  = Leaf
  | Branch (Int, Int) (Tree a) a (Tree a)

tostring :: Show a => Int -> Tree a -> String
tostring tabs Leaf = duplicate tabs "\t" ++ "()"
  where
    duplicate :: Int -> String -> String
    duplicate n str = [1..n] >>= const str
tostring tabs (Branch _ l a r) =
  duplicate tabs "\t" ++ Prelude.show a ++ "\n" ++
  duplicate tabs "\t" ++ "Left -->\n" ++ tostring (tabs + 1) l ++ "\n" ++
  duplicate tabs "\t" ++ "Right -->\n" ++ tostring (tabs + 1) r
    where
      duplicate :: Int -> String -> String
      duplicate n str = [1..n] >>= const str

-- | Size of the tree, O(1).
tsize :: Tree a -> Int
tsize Leaf                   = 0
tsize (Branch (sz, _) _ _ _) = sz

-- | Depth of the tree, O(1)
tdepth :: Tree a -> Int
tdepth Leaf                  = 0
tdepth (Branch (_, h) _ _ _) = h

-- | Fetches subtree depth difference, O(1)
tdiff :: Tree a -> Int
tdiff Leaf                    = error "cannot fetch diff of leaf"
tdiff (Branch _ left _ right) = tdepth left - tdepth right

-- | Check if the element is in the tree, O(log n)
tmember :: Ord a => a -> Tree a -> Bool
tmember _ Leaf                     = False
tmember el (Branch _ left a right) = el == a || tmember el (
  if el < a
  then left
  else right)

-- | Helper function that merges two subtrees
mkBranch :: Tree a -> a -> Tree a -> Tree a
mkBranch left el right =
  Branch (1 + tsize left + tsize right, 1 + max (tdepth left) (tdepth right)) left el right

-- | Perform small left rotation in AVL tree, O(1)
tsmallleft :: Tree a -> Tree a
tsmallleft Leaf = Leaf
tsmallleft tree@(Branch _ _ _ Leaf) = tree
tsmallleft (Branch _ left a (Branch _ rleft ra rright))
  = mkBranch (mkBranch left a rleft) ra rright

-- | Perform small right rotation in AVL tree, O(1)
tsmallright :: Tree a -> Tree a
tsmallright Leaf = Leaf
tsmallright tree@(Branch _ Leaf _ _) = tree
tsmallright (Branch _ (Branch _ lleft la lright) a right)
  = mkBranch lleft la (mkBranch lright a right)

-- | Perform big left rotation in AVL tree, O(1)
tbigleft :: Tree a -> Tree a
tbigleft Leaf = Leaf
tbigleft (Branch _ left a right)
  = tsmallleft (mkBranch left a (tsmallright right))

-- | Perform big right rotation in AVL tree, O(1)
tbigright :: Tree a -> Tree a
tbigright Leaf = Leaf
tbigright (Branch _ left a right)
  = tsmallright (mkBranch (tsmallleft left) a right)

-- | Balance tree that is skewed to the left, O(1)
tleft :: Tree a -> Tree a
tleft Leaf = Leaf
tleft tree@(Branch _ Leaf _ _) = tree
tleft tree@(Branch _ (Branch _ left _ right) _ _)
  | tdepth left + 1 == tdepth right = tbigright tree
  | otherwise = tsmallright tree

-- | Balance tree that is skewed to the right, O(1)
tright :: Tree a -> Tree a
tright Leaf = Leaf
tright tree@(Branch _ _ _ Leaf) = tree
tright tree@(Branch _ _ _ (Branch _ left _ right))
  | tdepth left == tdepth right + 1 = tbigleft tree
  | otherwise = tsmallleft tree

-- | Balance AVL tree, O(1)
tbalance :: Tree a -> Tree a
tbalance Leaf = Leaf
tbalance tree@(Branch _ left _ right)
  | leftH == rightH - 2 = tright tree
  | rightH == leftH - 2 = tleft tree
  | otherwise = tree
  where
    leftH = tdepth left
    rightH = tdepth right

-- | Insert an element into the tree, O(log n)
tinsert :: Ord a => a -> Tree a -> Tree a
tinsert el Leaf                     = mkBranch Leaf el Leaf
tinsert el (Branch sz left a right)
  | el < a = tbalance (mkBranch (tinsert el left) a right)
  | a < el = tbalance (mkBranch left a (tinsert el right))
  | otherwise = Branch sz left a right

-- | Build a tree from a list, O(n log n)
tFromList :: Ord a => [a] -> Tree a
tFromList = foldl (flip tinsert) Leaf
