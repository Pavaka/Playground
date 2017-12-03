(defn helper [coll prev result]
    (let [head (first coll)
        resto (rest coll)]
        (cond (nil? head) result
            (= prev head) (helper resto prev result)
            :else (helper resto head (concat result (list head))))))

(defn compress [coll]
    (helper (rest coll) (first coll) (list (first coll))))

(assert (= '(1, 2, 3, 4, 3, 5, 1) (compress '(1, 2, 2, 3, 4, 4, 3, 5, 5, 5, 1, 1, 1))))

; Removes ALL duplicates
(defn helper [coll added result]
    (let [head (first coll)]
    (cond (nil? head) result
        (added head) (helper (rest coll) added result)
        :else (helper (rest coll) (conj added head) (concat result (list head))))))

(defn eliminate [coll]
    (helper coll (set '()) (list)))

(assert (= 
    '(1, 2, 3, 55, 6, 7) 
    (eliminate '(1, 2, 3, 55, 2, 6, 6, 7, 1, 2, 2, 2))))
