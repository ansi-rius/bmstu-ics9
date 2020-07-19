(define (my-gcd a b)
  (cond
    ((> a b) (my-gcd (- a b) b))
    ((< a b) (my-gcd (- b a) a))
    (b)))

(define (my-lcm a b)
  (/ (* a b) (my-gcd a b)))

(define (help a plz)    ;help with division a/(from 2 to a-1) 
  (cond ((equal? plz a))
        ((= (remainder a plz) 0) #f)
        (else (help a (+ plz 1)))))

(define (prime? a)
  (cond
        ((and (even? a) (not(= a 2)))
          #f)
        
        ((equal? a 2))

        ((> a 2) (help a 2))))
;(prime? 3571)