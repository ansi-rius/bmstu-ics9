(define (intersperse e xs)
  (cond ((null? xs) '())
        ((= (length xs) 1) xs)
        ((not (= (length xs) 0))
         (append (append (list (car xs)) (list e))
                  (intersperse e (cdr xs))))))
      

(intersperse 'x '(1 2 3 4))
(intersperse 'x '(1 2))
(intersperse 'x '(1))
(intersperse 'x '())