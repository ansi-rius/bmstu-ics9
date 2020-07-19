(define (iterate f x n)
  (cond ((> n 0)
    (append (list x) (iterate f (f x) (- n 1))))
        ((= n 0) '())))

(iterate (lambda (x) (* 2 x)) 1 6)
(iterate (lambda (x) (* 2 x)) 1 1)
(iterate (lambda (x) (* 2 x)) 1 0)