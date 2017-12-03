(defn generate-same [el n]
    (letfn [(helper [k res]
            (if (not= 0 k)
                (helper (- k 1) (conj res el))
                res))]
        (helper n '())))

(assert (= '(5, 5, 5, 5, 5) (generate-same 5 5)))
(assert (= '(35, 35) (generate-same 35 2)))

(defn pack [coll]
    (letfn [(helper [coll prev cnt res]
            (let [head (first coll)]
                (cond (nil? head) (concat res (list (generate-same prev cnt)))
                        (= head prev) (helper (rest coll) head (+ 1 cnt) res)
                        :else (helper (rest coll) head 1 (concat res (list (generate-same prev cnt)))))))]
    (helper (rest coll) (first coll) 1 '())))

(assert (= '((1 1 1) (2 2) (3) (4) (5 5) (1)) (pack '(1, 1, 1, 2, 2, 3, 4, 5, 5, 1))))
(assert (= '((1)) (pack '(1))))

(defn pack-2 [coll] 
    (reverse (reduce (fn [res el]
        (if (= (first (first res)) el) 
                (cons (conj (first res) el) (rest res))
                (cons (list el) res)) )
        '() coll)))

(assert (= '((1 1 1) (2 2) (3) (4) (5 5) (1)) (pack-2 '(1, 1, 1, 2, 2, 3, 4, 5, 5, 1))))
(assert (= '((1)) (pack-2 '(1))))

