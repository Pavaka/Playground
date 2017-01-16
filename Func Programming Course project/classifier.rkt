#lang racket
(define cars-data-file (open-input-file "carsmall.data"))
(define DATA-SET-ATTRIBUTES 7)
(define TRAINING-PERCENT 85)
(define (construct-vector input-file n)
  (define (helper n)
    (cond ((= n 0) (list))
          (else (cons (read input-file) (helper (- n 1))))))
  (helper n))

; returns list of vectors, n is the length of single vectors
(define (split-input-to-vectors input-file n)
  (let ( (next-vector (construct-vector input-file n)))
    (if (eof-object? (car next-vector))
        (list)
        (cons next-vector (split-input-to-vectors input-file n)))))

(define parsed-data
  (split-input-to-vectors cars-data-file DATA-SET-ATTRIBUTES))

; workingSet is (trainingSet . testingSet)
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

