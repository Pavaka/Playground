(defn palindrome-naive [coll]
    (= coll (reverse coll)))
(assert (palindrome-naive '(1, 2, 1)))
(assert (not (palindrome-naive '(1, 2, 1, 2))))
