# python-obfuscator

Обфускатор должен:
 - [ ] Заменять имена переменных на случайные строки из символов I, 1, O и 0, которые являются корректными идентификаторами 
и в случае одинаково выглядящих символов I – 1 и O – 0, соответственно, выглядящие одинаково.
 - [ ] Вставлять в различные места программы незначащие действия с переменными,
которые затрудняют понимание программы, в том числе добавлять новые переменные.

## Подмножество языка
Мной были выбраны только самые простые конструкции языка:

- Строковые константы (без экранирования и мультилайна);
- Объявление функции (причём достаточно урезанное, без дефолтных значений и `*args` с `**kwargs`);
- Присваивание переменной (без множественного присваивания);
- Чтение переменной с помощью функции `input()`;
- Вывод переменной с помощью функции `print()` (без дополнительных аргументов).

Валидной программой в таком подмножестве, будет, например:

```python
def logged():
    a=input()
    print('read',a)
    return a

a=logged()
b=logged()
print(a,b)
```

## Грамматика
Нетерминалы обозначены латинскими словами в CamelCase, терминалы - либо символами в кавычках, либо прописными латинскими словами.

```
Program      -> Function break Program | Line break Program | eps
Function     -> "def " name "(" Args ")" ":" break "\t" FunctionBody
Args         -> name Tail | eps
Tail         -> "," name Tail | eps
FunctionBody -> Line break "\t" FunctionBody | Return | eps
Return       -> "return " Expr
Line         -> FunctionCall | Assignment
FunctionCall -> name "(" ArgsExpr ")"
ArgsExpr     -> Expr TailExpr | eps
TailExpr     -> "," Expr TailExpr | eps
Assignment   -> name "=" Expr
Expr         -> FunctionCall | "'" string constant "'" | name
```

Два нетерминала здесь - `break` и `name` обозначают несколько переносов строки и валидное имя переменной соответственно.

## Реализация
Задание выполнелно на Go 1.17 с помощью генератора парсеров goyacc, являющегося портом yacc на Go. 

## Пример

Для вышеуказанного фрагмента кода обфускатор может вывести, например:
```python
def 1oI010():
    loloI0=input()
    print('read',loloI0)
    return loloI0
loloI0=1oI010()
10lOIO='lOIO1O'
I01oIo=1oI010()
print(loloI0,I01oIo)
```