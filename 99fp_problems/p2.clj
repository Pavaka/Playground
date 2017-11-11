(defn my-but-last [coll]
    (let [rest-coll (next coll)]
    (if (next rest-coll)
        (my-but-last rest-coll)
        (first coll))))

(println (my-but-last '(1, 2 , 3, 623, 2)))
(println (my-but-last [22, 33]))
(println (my-but-last [1]))
(println (my-but-last []))