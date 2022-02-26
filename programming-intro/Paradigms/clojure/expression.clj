; common

(defn _in-map [sym] (symbol (str sym)))
(defn _divide ([a] (/ (double a)))
  ([a & args] (reduce (fn [a b] (/ a (double b))) a args)))
(defn _exp [x] (Math/exp x))
(defn _sumexp [& args] (apply + (mapv _exp args)))
(defn _softmax [& args] (/ (_exp (first args)) (double (apply _sumexp args))))
(defn _bitwise [f] (fn [& args] (Double/longBitsToDouble (apply f (mapv #(Double/doubleToLongBits %) args)))))
(def _bitwise_and (_bitwise bit-and))
(def _bitwise_not (_bitwise bit-not))
(def _bitwise_xor (_bitwise bit-xor))
(def _bitwise_or (_bitwise bit-or))
(def _bitwise_impl (_bitwise (fn [a b] (bit-or (bit-not a) b))))
(def _bitwise_iff (_bitwise (fn [& args] (bit-not (apply bit-xor args)))))

(defn abstract-parser [const-creator op-map var-map]
  (fn [text]
    (letfn [(parse [expr]
              (cond
                (number? expr) (const-creator (double expr))
                (list? expr) (apply (get op-map (first expr)) (mapv parse (rest expr)))
                (contains? var-map (str expr)) (get var-map (str expr))
                ))]
      (parse (read-string text)))))

; functional (hw10)

(defn nary-op [f]
  (fn [& args]
    (fn [vals] (apply f (mapv (fn [arg] (arg vals)) args)))))

(def constant constantly)

(defn variable [name] (fn [vals] (get vals name)))


(def negate (nary-op -))

(def add (nary-op +))
(def subtract (nary-op -))
(def multiply (nary-op *))

(def divide (nary-op _divide))

(def sumexp (nary-op _sumexp))
(def softmax (nary-op _softmax))

(def op-to-fun {
                '+       add
                '-       subtract
                '*       multiply
                '/       divide
                'sumexp  sumexp
                'softmax softmax
                'negate  negate
                })

(def var-to-fun {
                 'x (variable "x")
                 'y (variable "y")
                 'z (variable "z")
                 })

(def parseFunction (abstract-parser constant op-to-fun var-to-fun))

; object methods

(defn proto-get [obj key]
  (cond
    (contains? obj key) (obj key)
    (contains? obj :prototype) (proto-get (obj :prototype) key)))

(defn proto-call [this key & args]
  (apply (proto-get this key) (cons this args)))

(defn field [key]
  (fn [this] (proto-get this key)))

(defn method [key]
  (fn [this & args] (apply proto-call this key args)))

; object (hw11)

(def toString (method :toString))
(def evaluate (method :evaluate))
(def diff (method :diff))
(def toStringInfix (method :toInfix))

(defn Expression [toString evaluate diff toInfix]
  {
   :toString toString
   :evaluate evaluate
   :diff     diff
   :toInfix  toInfix
   })

(declare ONE)
(declare ZERO)

(def var-proto
  (letfn [(var-to-str [this] ((field :name) this))]
    (Expression
      var-to-str
      (fn [this vars] (vars ((field :name) this)))
      (fn [this differ] (if (= differ ((field :name) this)) ONE ZERO))
      var-to-str
      ))
  )

(def const-proto
  (letfn [(const-to-str [this] (format "%.1f" ((field :value) this)))]
    (Expression
      const-to-str
      (fn [this vars] ((field :value) this))
      (fn [this differ] ZERO)
      const-to-str
      ))
  )

(def op-proto
  (let [args (field :args)
        name (field :name)
        eval-rule (field :eval-rule)
        diff-rule (field :diff-rule)]
    (Expression
      (fn [this] (str "(" (name this) " " (clojure.string/join " " (mapv toString (args this))) ")"))
      (fn [this vars] (apply (eval-rule this) (mapv #(evaluate % vars) (args this))))
      (fn [this differ] ((diff-rule this) (args this) (mapv #(diff % differ) (args this))))
      (fn [this] (if (== 1 (count (args this)))
                   (str (name this) "(" (apply toStringInfix (args this)) ")")
                   (str "(" (clojure.string/join (str " " (name this) " ") (mapv toStringInfix (args this))) ")")))
      ))
  )

(defn Variable [name]
  {:prototype var-proto
   :name      (str name)})

(defn Constant [val]
  {:prototype const-proto
   :value     val})

(def ZERO (Constant 0))
(def ONE (Constant 1))

(defn op [name, eval-rule, diff-rule]
  (let [this-op-proto {:prototype op-proto
                       :name      name
                       :eval-rule eval-rule
                       :diff-rule diff-rule}]
    (fn [& args]
      {:prototype this-op-proto
       :args      (vec args)})))

(def Add (op '+ + (fn [args diff-args] (apply Add diff-args))))
(def Subtract (op '- - (fn [args diff-args] (apply Subtract diff-args))))
(def Negate (op 'negate - (fn [args diff-args] (apply Negate diff-args))))

(declare Multiply)
(declare Divide)

(def Multiply (op '* * (fn [args diff-args] (second (reduce
                                                      (fn [[a a'] [b b']] [(Multiply a b)
                                                                           (Add (Multiply a' b) (Multiply a b'))])
                                                      (mapv vector args diff-args))))))

(def Divide
  (op '/ _divide
      (fn [args [first-diff-arg & rest-diff-args]]
        (let [op-div (apply Multiply (rest args))
              diff-op-div (apply Multiply rest-diff-args)]
          (Divide (Subtract (Multiply first-diff-arg op-div) (Multiply (first args) diff-op-div))
                  (Multiply op-div op-div))))))

(declare Sumexp)
(defn _sumexp_diff [args diff-args] (apply Add (map-indexed (fn [i, op] (Multiply (Sumexp op) (nth diff-args i))) args)))
(def Sumexp (op 'sumexp _sumexp _sumexp_diff))

(def Softmax (op 'softmax _softmax
                 (fn [args diff-args]
                   (let [sum (apply Sumexp args)
                         diff-sum (_sumexp_diff args diff-args)
                         fst (Sumexp (first args))]
                     (Divide (Subtract (Multiply (first diff-args) fst sum) (Multiply diff-sum fst))
                             (Multiply sum sum))))))


(def And (op '& _bitwise_and nil))
(def Xor (op (symbol "^") _bitwise_xor nil))
(def Or (op '| _bitwise_or nil))
(def Impl (op '=> _bitwise_impl nil))
(def Iff (op '<=> _bitwise_iff nil))

(def op-to-obj
  {'+           Add
   '-           Subtract
   '*           Multiply
   '/           Divide
   'negate      Negate
   'sumexp      Sumexp
   'softmax     Softmax
   '&           And
   (symbol "^") Xor
   '|           Or
   '=>          Impl
   '<=>         Iff
   })

(def var-to-obj
  {'x (Variable "x")
   'y (Variable "y")
   'z (Variable "z")})

(def parseObject (abstract-parser Constant op-to-obj var-to-obj))

; combinatorial (hw12)

; combinators
(defn -return [value tail] {:value value :tail tail})
(def -valid? boolean)
(def -value :value)
(def -tail :tail)
(defn _show [result] (if (-valid? result) (str "-> " (pr-str (-value result)) " | " (pr-str (apply str (-tail result)))) "!"))
(defn _empty [value] (partial -return value))
(defn _char [p] (fn [[c & cs]] (if (and c (p c)) (-return c cs))))
(defn _map [f result] (if (-valid? result) (-return (f (-value result)) (-tail result))))
(defn _combine [f a b] (fn [str] (let [ar ((force a) str)] (if (-valid? ar) (_map (partial f (-value ar)) ((force b) (-tail ar)))))))
(defn _either [a b] (fn [str] (let [ar ((force a) str)] (if (-valid? ar) ar ((force b) str)))))
(defn _parser [p] (fn [input] (-value ((_combine (fn [v _] v) p (_char #{\u0000})) (str input \u0000)))))
(defn +char [chars] (_char (set chars)))
(defn +char-not [chars] (_char (comp not (set chars))))
(defn +map [f parser] (comp (partial _map f) parser))
(def +parser _parser)
(def +ignore (partial +map (constantly 'ignore)))
(defn iconj [coll value] (if (= value 'ignore) coll (conj coll value)))
(defn +seq [& ps] (reduce (partial _combine iconj) (_empty []) ps))
(defn +seqf [f & ps] (+map (partial apply f) (apply +seq ps)))
(defn +seqn [n & ps] (apply +seqf (fn [& vs] (nth vs n)) ps))
(defn +or [p & ps] (reduce _either p ps))
(defn +opt [p] (+or p (_empty nil)))
(defn +star [p] (letfn [(rec [] (+or (+seqf cons p (delay (rec))) (_empty ())))] (rec)))
(defn +plus [p] (+seqf cons p (+star p)))
(defn +str [p] (+map (partial apply str) p))
; combinators

; my combinators
(defn *make-string [operation] (apply +seqf (constantly operation) (mapv #(+char (str %)) (str operation))))
(def *digit (+char "0123456789"))
(def *space (+char " \t\n"))
(def *ws (+ignore (+star *space)))

(declare *parse)

(defn op-level [op-parser, rule] {:op-parser op-parser, :rule rule})
(def left (fn [level] (*parse (inc level))))
(def right (fn [level] (*parse level)))

(def max-level 7)
(def *operation-by-level
  [(op-level (*make-string '<=>) left)
   (op-level (*make-string '=>) right)
   (op-level (+char "^") left)
   (op-level (+char "|") left)
   (op-level (+char "&") left)
   (op-level (+char "+-") left)
   (op-level (+char "*/") left)
   (op-level (*make-string 'negate) left)])

(defn *get-operation
  ([left] left)
  ([left & [right]]
   (reduce (fn [expr [op cur]] ((get op-to-obj (_in-map op)) expr cur)) (cons left right))))

(def *brackets
  (delay (+seqn 0
                (+ignore (+char "("))
                *ws (*parse 0) *ws
                (+ignore (+char ")"))))
  )

(def *unary
  (+seqf (fn [name value] ((op-to-obj name) value))
         ((nth *operation-by-level max-level) :op-parser)
         *ws
         (delay (+or *brackets (+seqn 0 *ws (*parse max-level) *ws))))
  )

(defn *next-level [level]
  (let [operation (nth *operation-by-level level)] (delay
                                                     (+seqf *get-operation
                                                            (left level)
                                                            (+star (+seq
                                                                     *ws (operation :op-parser)
                                                                     *ws ((operation :rule) level))
                                                                   )))
                                                   ))

(def *variable (+map (fn [sym] (get var-to-obj (_in-map sym))) (+char "xyz")))
(def *number
  (+map Constant
        (+map read-string
              (+seqf (fn [sgn whole delim part] (apply str sgn (apply str whole) delim (apply str part)))
                     (+opt (+char "+-"))
                     (+plus *digit)
                     (+opt (+char "."))
                     (+opt (+plus *digit)))))
  )

(defn *parse [level]
  (if (not= level max-level)
    (*next-level level)
    (+or *number *variable *unary *brackets)))
; my combinators

(def parseObjectInfix (+parser (+seqn 0 *ws (*parse 0) *ws)))