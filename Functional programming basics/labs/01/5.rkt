(define (any? pred? xs) ;odd - нечёт, even - чеапнгг8889щзжэжбь т
  (not (equal? xs '()))
  (or (and (not(equal? xs '())) (pred? (car xs)))
      (and (not(equal? xs '())) (any? pred? (cdr xs)))))

(any? odd? '(1 3 5 7)) ;t 
(any? odd? '(0 1 2 3)) ;t
(any? odd? '(0 2 4 6)) ;f
(any? odd? '())        ;f
(newline)

(define (all? pred? xs)
  (or (and (and (not(equal? xs '())) (pred? (car xs)))
           (and (not(equal? xs '())) (all? pred? (cdr xs))))
      (equal? xs '())))
(all? odd? '(1 3 5 7)) ;t
(all? odd? '(0 1 2 3)) ;f
(all? odd? '(0 2 4 6)) ;f
(all? odd? '())        ;t