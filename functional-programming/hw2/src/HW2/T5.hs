{-# LANGUAGE ScopedTypeVariables #-}

module HW2.T5
  (
    ExceptState(..)
  , mapExceptState
  , wrapExceptState
  , joinExceptState
  , modifyExceptState
  , throwExceptState
  , EvaluationError(..)
  , eval
  ) where

import qualified Control.Monad
import HW2.T1 (Annotated (..), Except (..), mapAnnotated, mapExcept)
import HW2.T2 (wrapExcept)
import HW2.T4 (Expr (..), Prim (..))

-- | e is exception type, s is annotation type, a is inner type
newtype ExceptState e s a = ES { runES :: s -> Except e (Annotated s a) }


-- | Maps value inside ExceptState
mapExceptState :: forall e s a b. (a -> b) -> (ExceptState e s a -> ExceptState e s b)
mapExceptState f (ES inner) = ES mapped
  where
    mapped :: s -> Except e (Annotated s b)
    mapped state = mapExcept (mapAnnotated f) (inner state)


-- | Wraps value into ExceptState
wrapExceptState :: forall e s a. a -> ExceptState e s a
wrapExceptState a = ES wrapped
  where
    wrapped :: s -> Except e (Annotated s a)
    wrapped state = wrapExcept (a :# state)


-- | Joins nested ExceptStates
joinExceptState :: forall e s a. ExceptState e s (ExceptState e s a) -> ExceptState e s a
joinExceptState (ES outerRun) = ES joined
  where
    joined :: s -> Except e (Annotated s a)
    joined state = case outerRun state of
      Error e                             -> Error e
      Success (ES innerRun :# innerState) -> innerRun innerState

-- | Modifies annotation in ExceptState
modifyExceptState :: forall e s. (s -> s) -> ExceptState e s ()
modifyExceptState f = ES modified
  where
    modified :: s -> Except e (Annotated s ())
    modified state = Success (() :# f state)


-- | Wraps error as ExceptState
throwExceptState :: forall e s a. e -> ExceptState e s a
throwExceptState e = ES throw
  where
    throw :: s -> Except e (Annotated s a)
    throw _ = Error e


instance Functor (ExceptState e s) where
  fmap = mapExceptState


instance Applicative (ExceptState e s) where
  pure = wrapExceptState
  p <*> q = Control.Monad.ap p q


instance Monad (ExceptState e s) where
  m >>= f = joinExceptState (fmap f m)


data EvaluationError = DivideByZero deriving (Show)


-- | Evaluates unary expression
unaryEval
  :: (Double -> Prim Double) -- Prim unary constructor
  -> (Double -> Double)      -- Double unary function
  -> Expr                    -- Inner expression
  -> ExceptState EvaluationError [Prim Double] Double
unaryEval constructor unaryOp inner = do
  evInner <- eval inner
  _ <- modifyExceptState (constructor evInner :)
  pure (unaryOp evInner)


-- | Evaluates binary exception
binaryOperationalEval
  :: (Double -> Double -> Prim Double) -- Prim binary constructor
  -> (Double -> Double -> ExceptState EvaluationError [Prim Double] Double)
                                       -- Wrapped binary function
  -> Expr                              -- Left inner expression
  -> Expr                              -- Right inner expression
  -> ExceptState EvaluationError [Prim Double] Double
binaryOperationalEval constructor wrappedBinaryOp left right = do
  evLeft <- eval left
  evRight <- eval right
  _ <- modifyExceptState (constructor evLeft evRight :)
  wrappedBinaryOp evLeft evRight


-- | Applies binary operator to arguments, wrapping into ExceptState
wrapBinaryOp
  :: (Double -> Double -> Double) -- Mapper function
  -> Double                       -- Left argument
  -> Double                       -- Right argument
  -> ExceptState EvaluationError [Prim Double] Double
wrapBinaryOp op x y = pure (op x y)


-- | Performs division with DBZ check
checkedDiv :: Double -> Double -> ExceptState EvaluationError [Prim Double] Double
checkedDiv _ 0        = throwExceptState DivideByZero
checkedDiv left right = pure (left / right)


-- | Evaluates exception, throwing on DBZ error
eval :: Expr -> ExceptState EvaluationError [Prim Double] Double
eval (Val x)        = pure x
eval (Op (Add x y)) = binaryOperationalEval Add (wrapBinaryOp (+)) x y
eval (Op (Sub x y)) = binaryOperationalEval Sub (wrapBinaryOp (-)) x y
eval (Op (Mul x y)) = binaryOperationalEval Mul (wrapBinaryOp (*)) x y
eval (Op (Div x y)) = binaryOperationalEval Div checkedDiv x y
eval (Op (Abs x))   = unaryEval Abs abs x
eval (Op (Sgn x))   = unaryEval Sgn signum x
