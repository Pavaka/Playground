(defn my-last [coll]
    (let [rest-elements (rest coll)]
        (if (not (first rest-elements)) 
        (first coll) 
        (my-last rest-elements))))

(println (my-last [1, 5, 3, 66]))
(println (my-last [1]))
(println (my-last []))
(println (my-last [1, 5, 3, -11]))
