(defn elements-count [coll]
    (letfn [(helper [coll count]
            (if (next coll)
                (helper (rest coll) (+ 1 count))
                    (if (first coll )
                        (+ 1 count)
                        count)))]
    (helper coll 0)))

(assert (= 0 (elements-count '())))
(assert (= 1 (elements-count '(15))))
(assert (= 2 (elements-count '(2, 3))))
(assert (= 6 (elements-count '(1, 1, 2, 3, 5, 8))))
(assert (= 5 (elements-count "Pavel")))
