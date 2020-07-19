(use-syntax (ice-9 syncase))
;1 сама мемоизация
(define memoized-factorial
  (let ((memo '())) ;ассоц список
    (lambda (n)
      (let ((memozed (assq n memo)))
        (if memozed
            (cadr memozed)
            (let ((new-value (if (< n 2)
                                 1
                                 (* (memoized-factorial (- n 1)) n))))
              (set! memo
                    (cons (list n new-value) memo))
              new-value))))))

;2 (lazy-cons a b)  (lazy-car p) (lazy-cdr p)
;  (lazy-head xs k) (lazy-ref xs k)
;  (naturals start)
;  (lazy-factorial n)

(define-syntax lazy-cons
  (syntax-rules()
    ((_ a b) (cons a (delay b)))))

(define (lazy-car p)
  (car p))
(define (lazy-cdr p)
  (force (cdr p)))

(define (lazy-head xs k)
  (if (= k 0)
      '()
      (cons (lazy-car xs) (lazy-head (lazy-cdr xs) (- k 1)))))
(define (lazy-ref xs k) ;k-ый элемент из xs
  (if (= k 0)
      (lazy-car xs)
      (lazy-ref (lazy-cdr xs) (- k 1))))

(define (naturals start)
  (lazy-cons start (naturals (+ 1 start))))

(define (lazy-factorial n)
  (define (factorials k1 k2 )
        (lazy-cons k2 (factorials (+ k1 1) (* k2 (+ k1 1)))))
  (lazy-ref (factorials 0 1) n))
