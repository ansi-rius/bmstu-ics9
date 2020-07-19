(define (ref smth ind num)
  (cond ((null? num) #f)
        ((vector? smth)
        (cond ((null? smth) (make-vector 1 num))
              ((= ind 0) (append (list num) (vector->list smth)))
              (else
               (list->vector (append (list (car (vector->list smth)))
                     (ref (cdr (vector->list smth)) (- ind 1) num))))))
            
            ; (list->vector (append (vector->list smth) (list num) (cdr (vector->list smth))))))))
        ((list? smth)
        (cond ((> ind (length smth)) #f)
              ((null? smth) (list num))
              ((= ind 0) (append (list num) smth))
              (else
               (append (list (car smth))
                       (ref (cdr smth) (- ind 1) num)))))

        ((string? smth)
        (cond ((null? smth) (make-string 1 num))
              ((= ind 0) (append (list num) (string->list smth)))
              ((equal? num 0) #f)
              (else
               (list->string (append (list (car (string->list smth)))
                     (ref (cdr (string->list smth)) (- ind 1) num))))))
        ((char? smth)
        (cond ((null? smth) (make-char 1 num))
              ((= ind 0) (append (list num) (char->list smth)))
              ((equal? num 0) #f)
              (else
               (list->char (append (list (car (char->list smth)))
                     (ref (cdr (char->list smth)) (- ind 1) num))))))))


(ref '(1 2 3) 0 0)   ;  (1 0 2 3)
;(ref #(1 2 3) 1 0)   ; #(1 0 2 3)
;(ref #(1 2 3) 1 #\0) ; #(1 #\0 2 3) vector char
;(ref #(1 2 3) 1 '(99)) ;vector list
;(ref "123" 1 #\0)    ;"1023"
(ref "123" 4 0)      ;#f
;(ref "123" 1 #\a)    ;string char
;(ref "123" 2 '(7))
;(ref '(1 2 3) 2 '(11)) ;list list
;(ref '(1 2 3) 1 #\b)   ;list char
;(ref "123" 3)        ;#f