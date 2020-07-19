(define (my-range a b d)
  (if (< (+ a d) b)
      (append (list a) (my-range (+ a d) b d))
      (append (list a))))

(define (my-element? x xs)
  (if (> (length xs) 0)
      (if (equal? x (car xs)) #t
          (my-element? x (cdr xs)))
      #f))
;(my-element? 1 '(3 2 1)) ; #t 
;my-element? 4 '(3 2 1)) ; #f

(define (my-filter pred? xs)
  (if (null? xs) '()
      (if (pred? (car xs))
                 (cons (car xs) (my-filter pred? (cdr xs)))
                 (my-filter pred? (cdr xs)))))
;(my-filter odd? (my-range 0 10 1)) ; (1 3 5 7 9)
;(my-filter (lambda (x) (= (remainder x 3) 0)) (my-range 0 13 1)) ; (0 3 6 9 12)  
  
(define (my-fold-left op xs)
  (cond ((= (length xs) 2)
         (append (op (car xs) (cadr xs))))
        ((> (length xs) 2)
         (my-fold-left op (append (list (op (car xs) (car (cdr xs))))
                 (cddr xs))))))

(define (remove-last ls)
    (if (null? (cdr ls))
        '()
        (cons (car ls) (remove-last (cdr ls)))))

(define (my-fold-right op xs)
  (cond ((> (length xs) 2)
          (op (car xs) (my-fold-right op (cdr xs))))
        (else
          (op (list-ref xs (- (length xs) 2)) (list-ref xs (- (length xs) 1))))))

(define (my-flatten x)
  (if (null? x)
      '()
      (if (pair? x) ;(pair? '((1) 2 (3 (4 5)) 6)) #t  ;(pair? 1) #f
          (append (my-flatten (car x)) (my-flatten (cdr x)))
          (list x))))

;(my-flatten '((1) 2 (3 (4 5)) 6)) ; (1 2 3 4 5 6)
;(my-fold-left  quotient '(16 2 2 2 2)) ; 1
;(my-fold-right expt '(2 3 4))      ; 2417851639229258349412352
; 1) 3^4 2)2^(3^4)