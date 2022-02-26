{-# LANGUAGE DerivingStrategies         #-}
{-# LANGUAGE GeneralizedNewtypeDeriving #-}
{-# LANGUAGE InstanceSigs               #-}
{-# LANGUAGE ScopedTypeVariables        #-}

module HW2.T6
  (
    ParseError(..)
  , runP
  , pChar
  , parseError
  , pEof
  , pAbbr
  , parseExpr
  ) where

import Control.Applicative (Alternative (..))
import Control.Monad (MonadPlus, mfilter)
import qualified Data.Char
import Data.Scientific (Scientific, scientific, toRealFloat)
import GHC.Natural (Natural)

import Data.Char (digitToInt)
import HW2.T1 (Annotated (..), Except (..), mapExcept)
import HW2.T4 (Expr (..), Prim (Add, Div, Mul, Sub))
import HW2.T5 (ExceptState (ES))


newtype ParseError = ErrorAtPos Natural deriving (Show)


newtype Parser a = P (ExceptState ParseError (Natural, String) a)
  deriving newtype (Functor, Applicative, Monad)


-- | Runs provided parser on given string and returns its result
runP :: forall a. Parser a -> String -> Except ParseError a
runP (P (ES runParser)) str = mapExcept extractResult (runParser (0, str))
  where
    extractResult :: Annotated (Natural, String) a -> a
    extractResult (result :# _) = result


-- | Parser that parses one arbitrary character
pChar :: Parser Char
pChar = P (ES parse)
  where
    parse :: (Natural, String) -> Except ParseError (Annotated (Natural, String) Char)
    parse (pos, [])     = Error (ErrorAtPos pos)
    parse (pos, a : at) = Success (a :# (pos + 1, at))


-- | Parser that always fails
parseError :: forall a. Parser a
parseError = P (ES except)
  where
    except :: (Natural, String) -> Except ParseError (Annotated (Natural, String) a)
    except (pos, _) = Error (ErrorAtPos pos)


instance Alternative Parser where
  empty = parseError
  (<|>) :: forall a. Parser a -> Parser a -> Parser a
  (<|>) (P (ES pTry)) (P (ES pElse)) = P (ES alternative)
    where
      alternative :: (Natural, String) -> Except ParseError (Annotated (Natural, String) a)
      alternative state = case pTry state of
        (Error _)        -> pElse state
        (Success result) -> Success result


instance MonadPlus Parser


-- | Parser that checks whether input has ended and fails otherwise
pEof :: Parser ()
pEof = P (ES eofChecker)
  where
    eofChecker :: (Natural, String) -> Except ParseError (Annotated (Natural, String) ())
    eofChecker (pos, []) = Success (() :# (pos, []))
    eofChecker (pos, _)  = Error (ErrorAtPos pos)


-- | Parser that parses sequance of uppercase letters
pAbbr :: Parser String
pAbbr = do
  abbr <- some (mfilter Data.Char.isUpper pChar)
  _ <- pEof
  pure abbr


-- | Parser that parses exactly one digit
pDigit :: Parser Char
pDigit = mfilter Data.Char.isDigit pChar


-- | Parser that parses one expected character and fails otherwise
pExpect :: Char -> Parser String
pExpect c = do
  chr <- mfilter (== c) pChar
  pure [chr]


-- | Parser that parses arbitrary sequence of whitespace characters
pSpaces :: Parser String
pSpaces = many (mfilter Data.Char.isSpace pChar)


-- | Parser that parses arbitrary sequence of digits
pInteger :: Parser String
pInteger = some pDigit


-- | Converter that transforms string representation of integer into integer
stringToInteger :: String -> Integer
stringToInteger s = foldl step 0 (map (toInteger . digitToInt) s)
  where
    step :: Integer -> Integer -> Integer
    step lead follow = 10 * lead + follow


-- | Parser that parses integer value to Expr
pIntegerToVal :: Parser Expr
pIntegerToVal = Val . fromInteger . stringToInteger <$> pInteger


-- | Parser that parses double in format xyz.abc with possible leading zeros
-- | to Expr
pDouble :: Parser Expr
pDouble = do
  integral <- pInteger
  _ <- pExpect '.'
  Val . toRealFloat . toScientific integral <$> pInteger
    where
      toScientific :: String -> String -> Scientific
      toScientific int part = scientific (stringToInteger (int ++ part)) (- length part)


-- | Parser that parses either integer or double and ignores whitespace around
pNumber :: Parser Expr
pNumber = do
  _ <- pSpaces
  x <- pDouble <|> pIntegerToVal
  _ <- pSpaces
  pure x


-- | Parses binary expression that is left-associative
pBinaryLeft :: Parser Expr -> Char -> (Expr -> Expr -> Prim Expr) -> Parser Expr
pBinaryLeft lowParser chr operation = do
  _ <- pSpaces
  leftmost <- lowParser
  _ <- pSpaces
  rest <- many (pExpect chr *> lowParser)
  _ <- pSpaces
  pure (foldl1 operator (leftmost : rest))
    where
      operator :: Expr -> Expr -> Expr
      operator x y = Op (operation x y)

-- | Parses binary expression that is right-associative
-- pBinaryRight :: Parser Expr -> Char -> (Expr -> Expr -> Prim Expr) -> Parser Expr
-- pBinaryRight lowParser chr operation = do
--  _ <- pSpaces
--  leftmost <- lowParser
--  _ <- pSpaces
--  rest <- many (pExpect chr *> lowParser)
--  _ <- pSpaces
--  pure (foldr1 operator (leftmost : rest))
--    where
--      operator :: Expr -> Expr -> Expr
--      operator x y = Op (operation x y)

-- | Parses expression inside brackets
pExprWithBrackets :: Parser Expr
pExprWithBrackets = do
  _ <- pSpaces
  _ <- pExpect '('
  _ <- pSpaces
  res <- pAdd
  _ <- pSpaces
  _ <- pExpect ')'
  pure res


-- | Grammar:
-- | expr = add
-- | add = sub ('+' sub)*
-- | sub = mul ('-' mul)*
-- | mul = div ('*' div)*
-- | div = unary ('/' unary)*
-- | unary = number | '(' expr ')'
-- | number = int | int.int
-- | int = digit*
-- |
-- | This grammar is not exactly correct, because this
-- |   1 + 2 - 3 + 4
-- | must be parsed as
-- |   (((1 + 2) - 3) + 4)
-- | but we parse it as
-- |   ((1 + (2 - 3)) + 4)
-- | however, it can be easily proven that in this exact ordering
-- | of operations, RESULT of the expression evaluation is the same
-- |
-- | Just in case, you know, there's a better (however, less performant) gramar:
-- | expr -> t1 expr'
-- | E' -> '+' t1 expr' | '-' t1 expr' | ''
-- | t1 -> t2 t1'
-- | t1' -> '*' t2 t1' | '/' t2 t1' | ''
-- | t2 -> number | '(' expr ')'
pExpr :: Parser Expr
pExpr = pAdd

pAdd :: Parser Expr
pAdd = pBinaryLeft pSub '+' Add

pSub :: Parser Expr
pSub = pBinaryLeft pMul '-' Sub

pMul :: Parser Expr
pMul = pBinaryLeft pDiv '*' Mul

pDiv :: Parser Expr
pDiv = pBinaryLeft pUnary '/' Div

pUnary :: Parser Expr
pUnary = pNumber <|> pExprWithBrackets

-- | Parses expression and returns parser's result
parseExpr :: String -> Except ParseError Expr
parseExpr = runP (pExpr <* pEof)
