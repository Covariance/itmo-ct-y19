{-# LANGUAGE ScopedTypeVariables #-}

module HW2.T4
  (
    State(..)
  , mapState
  , wrapState
  , joinState
  , modifyState
  , Prim(..)
  , Expr(..)
  , eval
  ) where

import qualified Control.Monad
import HW2.T1 (Annotated (..), mapAnnotated)


-- | s is the annotation type, a is inner type
newtype State s a = S { runS :: s -> Annotated s a }


-- | Maps value inside State
mapState :: forall s a b. (a -> b) -> (State s a -> State s b)
mapState f = mapper
  where
    mapper :: State s a -> State s b
    mapper state = S (mapAnnotated f . runS state)


-- | Wraps value in State
wrapState :: forall s a. a -> State s a
wrapState a = S wrapper
  where
    wrapper :: s -> Annotated s a
    wrapper s = a :# s


-- | Join nested States
joinState :: forall s a. State s (State s a) -> State s a
joinState outer = S joiner
  where
    joiner :: s -> Annotated s a
    joiner s = extractor (runS outer s)
      where
        extractor :: Annotated s (State s a) -> Annotated s a
        extractor (state :# sInner) = runS state sInner


-- | Modifies annotation in State
modifyState :: forall s. (s -> s) -> State s ()
modifyState f = S inner
  where
    inner :: s -> Annotated s ()
    inner s = () :# f s


instance Functor (State s) where
  fmap = mapState


instance Applicative (State s) where
  pure = wrapState
  p <*> q = Control.Monad.ap p q


instance Monad (State s) where
  m >>= f = joinState (fmap f m)


data Prim a =
    Add a a
  | Sub a a
  | Mul a a
  | Div a a
  | Abs a
  | Sgn a


data Expr =
    Val Double
  | Op (Prim Expr)


instance Num Expr where
  x + y = Op (Add x y)
  x - y = Op (Sub x y)
  x * y = Op (Mul x y)
  abs x = Op (Abs x)
  signum x = Op (Sgn x)
  fromInteger x = Val (fromInteger x)


instance Fractional Expr where
  x / y = Op (Div x y)
  fromRational x = Val (fromRational x)


-- | Evaluates unary expression
unaryEval
  :: (Double -> Prim Double) -- Prim unary constructor
  -> (Double -> Double)      -- Double unary function
  -> Expr                    -- Inner expression
  -> State [Prim Double] Double
unaryEval constructor unaryOp inner = do
  evInner <- eval inner
  modifyState (constructor evInner :)
  return (unaryOp evInner)


-- | Evaluates binary expression
binaryEval
  :: (Double -> Double -> Prim Double) -- Prim binary constructor
  -> (Double -> Double -> Double)      -- Double binary function
  -> Expr                              -- Left inner expression
  -> Expr                              -- Right inner expression
  -> State [Prim Double] Double
binaryEval constructor binaryOp left right = do
  evLeft <- eval left
  evRight <- eval right
  modifyState (constructor evLeft evRight :)
  return (binaryOp evLeft evRight)


-- | Evaluates arbitrary expression
eval :: Expr -> State [Prim Double] Double
eval (Val x)        = pure x
eval (Op (Add x y)) = binaryEval Add (+) x y
eval (Op (Sub x y)) = binaryEval Sub (-) x y
eval (Op (Mul x y)) = binaryEval Mul (*) x y
eval (Op (Div x y)) = binaryEval Div (/) x y
eval (Op (Abs x))   = unaryEval Abs abs x
eval (Op (Sgn x))   = unaryEval Sgn signum x
