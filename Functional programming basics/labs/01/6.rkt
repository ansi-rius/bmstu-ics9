;(define (g x) (+ x 3))
(define (f x) (* x 2))
(define (g x) (* x 3))
(define (h x)   (- x))

;(define (helper funcs)
;  (if (not (equal? funcs '()))
;      (car funcs)))
(define (helper funcs)
   (if (> (length funcs) 0)
       (car funcs)))

(define (o . args)
  (helper args))

(define (helper args)
  (lambda (x)
    (cond ((null? args)  x)
          (else ((helper (cdr args)) ((car args) x))))))
          ;(if (> (length args) 0) (o . (cdr args)))))
;    (if (> (length args) 0) (helper (cdr args))))))
        
;((o f g h g) 1)  ;-18
((o f g h) 1) ;-6
((o f g) 1)   ;6
((o h) 1)     ;-1
((o) 1)       ;1