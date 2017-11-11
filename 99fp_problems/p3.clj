
(defn element-at [coll k]
    (if (= k 1) 
    (first coll)
    (element-at  (rest coll) (- k 1))))

(println (element-at '(6, 13, 9, 15) 3))
(println (element-at '(6, 13, 9, 15, 333) 1))
(println (element-at '(6, 13, 9, 15, 333) 5))
(println (element-at '(6, 13, 9, 15, 333) 6))
(println (element-at '() 500))