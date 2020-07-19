(define (delete pred? xs)
  (if (null? xs)
      '()
      (if (pred? (car xs))
          (delete pred? (cdr xs))
          (cons (car xs) (delete pred? (cdr xs)))))) ;construckt new list

(delete even? '(0 1 2 3))
(delete even? '(0 2 4 6))
(delete even? '(1 3 5 7 8 9))
(delete even? '())