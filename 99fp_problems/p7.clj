(defn helper [rest-coll flattened]
    (let [head (first rest-coll)]
    (cond 
        (seq? head) (helper (rest rest-coll) (helper head flattened)) 
        (nil? head) flattened
        :else (helper (rest rest-coll) (concat flattened (list head))))))

(defn flat [coll]
    (helper coll '()))

(println (flat '(1, ((2, 3), 4), (4, (22 (33, 18, (55)))))))
