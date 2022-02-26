## Грамматика:

```
fun    -> FUN NAME LBR args RBR
arg    -> NAME DOUBLEDOT TYPE
args   -> arg tail | eps
tail   -> COMA arg tail | eps
```