(defn reverse-naive [coll] 
    (if (empty? coll) 
        coll
        (concat 
            (reverse-naive (rest coll)) 
            (list (first coll)))))

(assert (= '(3, 2, 1) (reverse-naive '(1, 2, 3))))
(assert (= '(3, 2, 1, 1) (reverse-naive '(1, 1, 2, 3))))
(assert (= '(3) (reverse-naive '(3))))
(assert (= '() (reverse-naive '())))

(defn reverse-tail [coll]
    (letfn [(helper [remaining-coll reversed-coll]
                (if (empty? remaining-coll)
                    reversed-coll
                    (helper 
                        (rest remaining-coll)
                        (cons 
                            (first remaining-coll) 
                            reversed-coll))))]
            (helper coll '())))

(assert (= '(3, 2, 1) (reverse-tail '(1, 2, 3))))
(assert (= '(3, 2, 1, 1) (reverse-tail '(1, 1, 2, 3))))
(assert (= '(3) (reverse-tail '(3))))
(assert (= '() (reverse-tail '())))
            
