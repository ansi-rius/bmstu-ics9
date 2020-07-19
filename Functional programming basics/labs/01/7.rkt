(define (find-number a b c)
  (cond ((= (remainder a c) 0) a)
        ((and (= a b)
              (not (= (remainder a c) 0)))
          #f)
        ((or (< a b) (= a b))
          (find-number (+ a 1) b c))))
  
(find-number 0 5 2) ;0
(find-number 7 9 3) ;9
(find-number 3 7 9) ;#f