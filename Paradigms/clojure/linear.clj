(defn conformed? [& args]
  (or
    (every? number? args)
    (and
      (every? vector? args)
      (apply == (map count args))
      (every? identity (apply mapv conformed? args)))))

(defn in-out-type? [out-type-check in-type-check]
  (fn [this] (and
               (out-type-check this)
               (every? in-type-check this))))

; region vectors
(def vect? (in-out-type? vector? number?))

(defn vect-op [f]
  (fn [& args]
    {:pre [(every? vect? args) (apply conformed? args)]}
    (apply mapv f args)))

(def v+ (vect-op +))
(def v- (vect-op -))
(def v* (vect-op *))

(defn v*s [v & args]
  {:pre [(every? number? args) (vect? v)]}
  (let [prod (apply * args)]
    (mapv (partial * prod) v)))

(defn scalar [a b]
  {:pre [(vect? a) (vect? b) (conformed? a b)]}
  (reduce + (v* a b)))

(defn vect [& args]
  {:pre [(every? vect? args) (every? (fn [x] (== (count x) 3)) args)]}
  (reduce
    (fn [a b]
      (letfn [(term [i1, i2] (- (* (nth a i1) (nth b i2)) (* (nth a i2) (nth b i1))))]
        (vector (term 1 2) (term 2 0) (term 0 1)))) args))
; endregion

; region matrices
(def matrix? (in-out-type? vector? vect?))

(defn matrix-op [f]
  (fn [& args]
    {:pre [(every? matrix? args) (apply conformed? args)]}
    (apply mapv f args)))

(def m+ (matrix-op v+))
(def m- (matrix-op v-))
(def m* (matrix-op v*))

(defn transpose [m]
  {:pre [(matrix? m)]}
  (apply mapv vector m))

(defn m*s [m & args]
  {:pre [(matrix? m) (every? number? args)]}
  (let [prod (apply * args)]
    (mapv (fn [v] (v*s v prod)) m)))

(defn m*v [m v]
  {:pre [(matrix? m) (vect? v) (= (count (first m)) (count v))]}
  (mapv (partial apply +) (mapv (partial v* v) m)))

(defn matrix-sequential? [& args]
  (pos? (first (reduce
                 (fn [a, b] (if (== (first a) (second b)) (vector (second a) (first b)) [-1, -1]))
                 (mapv (fn [m] (vector (count m) (count (first m)))) args)))))

(defn m*m [& args]
  {:pre [(every? matrix? args) (matrix-sequential? args)]}
  (reduce (fn [a b] (mapv (partial
                            (fn [m v] (mapv (fn [a] (reduce + (v* a v))) m)) (transpose b)) a)) args))
; endregion

; region tensors
; TODO исправлена производительность
(defn tensor? [t]
  (letfn [(inner-check [t] (cond
              (number? t) [1]
              (vector? t) (let [dims (mapv inner-check t)]
                            (if (and (apply = dims) (every? (fn [dim] (pos? (first dim))) dims))
                              (apply conj (vector (count dims)) (first dims))
                              [-1]))
              :else [-1]))]
    (pos? (first (inner-check t)))
    )
  )

; (println (tensor? [2, [2, 1]]))
; (println (tensor? [[1, 2], [1, [2]]]))

(defn form [t]
  (if (number? t)
    (vector)
    (apply conj (vector (count t)) (form (first t)))))

(defn suf? [this suf-of]
  (let [len (- (count suf-of) (count this))]
    (and
      (pos? len)
      (= (subvec suf-of len) this))))

(defn find-max-form [& args]
  (reduce (fn [a, b]
            (if (> (count a) (count b)) a b))
          args))

(defn valid-b-ables? [& args]
  (and (every? tensor? args)
       (let [forms (mapv form args) max-form (apply find-max-form forms)]
         (every? (fn [this]
                   (or
                     (= this max-form)
                     (suf? this max-form))) forms))))

(defn broadcast [& args]
  (let [max-form (apply find-max-form (mapv form args))]
    (mapv (fn [t]
            ((reduce comp (mapv
                            (fn [dim] (fn [a] (apply vector (repeat dim a))))
                            (subvec max-form 0 (- (count max-form) (count (form t)))))) t)) args)))

(defn tensor-op [f]
  (fn [& args]
    {:pre [(apply valid-b-ables? args)]}
    (letfn [(inner-op [& v] (if (number? (first v))
                (apply f v)
                (apply mapv inner-op v)))]
      (apply inner-op (apply broadcast args)))))

(def b+ (tensor-op +))
(def b- (tensor-op -))
(def b* (tensor-op *))
(def bd (tensor-op /))
; endregion