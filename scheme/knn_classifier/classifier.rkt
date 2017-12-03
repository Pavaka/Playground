#lang racket
(define cars-data-file (open-input-file "car.data"))
(define DATA-SET-ATTRIBUTES 7)
(define TRAINING-PERCENT 85)
(define (map-buying value)
  (cond ((equal? value "vhigh") 4)
        ((equal? value "high") 3)
        ((equal? value "med") 2)
        ((equal? value "low") 1)))

(define (map-maint value)
  (cond ((equal? value "vhigh") 4)
        ((equal? value "high") 3)
        ((equal? value "med") 2)
        ((equal? value "low") 1)))

(define (map-doors value)
  (cond ((equal? value "5more") 4)
        ((equal? value "four") 3)
        ((equal? value "three") 2)
        ((equal? value "two") 1)))

(define (map-persons value)
  (cond ((equal? value "more") 3)
        ((equal? value "four") 2)
        ((equal? value "two") 1)))

(define (map-lug-boot value)
  (cond ((equal? value "big") 3)
        ((equal? value "med") 2)
        ((equal? value "small") 1)))

(define (map-safety value)
  (cond ((equal? value "high") 3)
        ((equal? value "med") 2)
        ((equal? value "low") 1)))

(define (map-class value)
  (cond ((equal? value "vgood") 4)
        ((equal? value "good") 3)
        ((equal? value "acc") 2)
        ((equal? value "unacc") 1)))

(define all-mappings
  (list map-buying map-maint map-doors map-persons map-lug-boot map-safety map-class))

(define (map-data-to-nums data-vector)
  (map (lambda (func value) (func value)) all-mappings data-vector))

(define (construct-vector input-file n)
  (define (helper n)
    (cond ((= n 0) (list))
          (else
           (let ((value  (read input-file)))
             (if (eof-object? value)
                 (list #f)
                 (cons (symbol->string value) (helper (- n 1))))
             ))))
  (helper n))

; returns list of vectors, n is the length of single vectors
(define (split-input-to-vectors input-file n)
  (let ((next-vector (construct-vector input-file n)))
    (if (not (car next-vector))
        (list)
        (cons (map-data-to-nums next-vector) (split-input-to-vectors input-file n)))))

(define parsed-data
  (split-input-to-vectors cars-data-file DATA-SET-ATTRIBUTES))


(define (generate-working-sets parsed-data)
  (define (helper training testing parsed-data)
    (cond ((empty?  parsed-data) (cons training testing))
          ((< (random 100) TRAINING-PERCENT)
           (helper
            (cons (car parsed-data) training)
            testing
            (cdr parsed-data)))
          (else
           (helper
            training
            (cons (car parsed-data) testing)
            (cdr parsed-data)))))
  (helper (list) (list) parsed-data))

(define working-set (generate-working-sets parsed-data))
(define training-set (car working-set))
(define testing-set (cdr working-set))



(define (distance vec1 vec2)
  (sqrt (apply +
               (map
                (lambda (v1 v2) (* (- v2 v1)(- v2 v1)) )
                vec1
                vec2))))


; pairs of type (distance . class as number)
(define (find-min pairs)
  (define (helper res rem n)
    (cond ((empty? rem) res)
          ((< (caar rem) (caar res)) (helper (cons (car rem) n) (cdr rem) (+ n 1)))
          (else (helper res (cdr rem) (+ n 1)))))
  (helper (cons (car pairs) 0) (cdr pairs) 1))


; mergesorts list of pairs by the first value
(define (merge pred lst1 lst2)
  (define (helper res l1 l2)
    (cond ((empty? l1) (append res l2))
          ((empty? l2) (append res l1))
          ((pred (caar l1) (caar l2)) (helper (append res (list (car l1))) (cdr l1) l2))
          (else (helper (append res (list (car l2))) l1 (cdr l2)))))
  (helper (list) lst1 lst2))

(define (mergesort pred lst)
  (let ((lst-length (length lst)))
    (cond ((< lst-length 2) lst)
          (else 
           (merge
            pred
            (mergesort pred (take lst (quotient lst-length 2)))
            (mergesort pred (drop lst (quotient  lst-length 2))))))))

(define (most-common lst)
  (define (helper res lst)
    (if (empty? lst)
        res
        (helper
         (cons
          (cons         
           (count
            (lambda (x) (equal? x (car lst)))
            lst)
           (car lst))
          res)
         (filter
          (lambda (x) (not (equal? x (car lst))))
          lst))))
  (cdar (mergesort > (helper (list) lst))))

(define (kNN-classify vec data-set k)
  (most-common
   (map
    cdr
    (take (mergesort
           <
           (map
            (lambda (curr-data) (cons (distance vec curr-data) (car (reverse curr-data))))
            data-set))
          k))))


(define (test-kNN training-set testing-set k)
  (cons
   (length
    (filter
     (lambda (pred) pred)
     (map
      equal?
      (map
       (lambda (test-item) (kNN-classify test-item training-set k))
       testing-set)
      (map last testing-set))))
   (length testing-set)))

(test-kNN training-set testing-set 3); for small K it is almost 100 percent success with this data set
(test-kNN training-set testing-set 300) ; the bigger the k the more randomized thus inaccurate