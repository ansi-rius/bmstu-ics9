(define (minus expr)
  (if (= (length expr) 2)
      (- (derivative (cadr expr)))
      (if (= (length expr) 3)
          (list '- (derivative (cadr expr)) (derivative (caddr expr))))))

(define (plus expr)
  (if (= (length expr) 3)
      
      (list '+ (derivative (cadr expr))
            (derivative (caddr expr)))
      
      (list '+ (derivative (cadr expr))
            (derivative (cons '+ (cddr expr))))))


(define (increase expr)
  (if (and (number? (cadr expr)) (equal? 'x (caddr expr)))
      (cadr expr)
      (if (= (length expr) 3)
          (list '+ (list '* (derivative (cadr expr)) (caddr expr)) (list '* (cadr expr) (derivative (caddr expr))))
          (list '+ (list '* (derivative (cadr expr)) (cons '* (cddr expr))) (list '* (cadr expr) (derivative (cons '* (cddr expr))))))))
      
(define (division expr)
  (list '/ (list '- (list '* (derivative (cadr expr)) (caddr expr))
                 (list '* (cadr expr) (derivative (caddr expr))))
        (list 'expt (caddr expr) 2)))



(define (derivative expr)
  (cond
    ;(2)' = 0;
    ((number? expr) '0)
    ;(x)' = 1;
    ((equal? expr 'x) '1)
    ;разность производных
    ((equal? (car expr) '-) (minus expr))
    ;сумма производных
    ((equal? (car expr) '+) (plus expr))
    ;произведение
    ((equal? (car expr) '*) (increase expr))
    ;деление
    ((equal? (car expr) '/) (division expr))
    ;возводим х в степень(число)                              (expt x 10)'
    ((and (equal? (car expr) 'expt) (number? (caddr expr))) ;   ^     ^
     (list '* (caddr expr) (list 'expt (cadr expr) (- (caddr expr) 1)) ;(* 10 (expt 10 (-1))
           (derivative (cadr expr))))
    ;возводим х в степень(в степени сложная ф-ия)             
    ((and (equal? (car expr) 'expt) (list? (caddr expr))  ;(expt x (- 2)
          (equal? '- (caaddr expr)) (number? (car (cdr (cadr (cdr expr))))))

     (list '* (caddr expr) (list 'expt (cadr expr) (list '- (caddr expr) 1))
           (derivative (cadr expr))))
    ;(a^x)' = a^x * log a
    ((and (equal? (car expr) 'expt) (number? (caddr expr))) (list '* expr (list 'log (cadr expr)) (derivative (caddr expr))))
    ;e^x = e^x
    ((equal? (car expr) 'exp) (list '* expr (derivative (cadr expr))))
    ;(cosx)' = -sinx
    ((equal? (car expr) 'cos) (list '* (list '- (list 'sin (cadr expr))) (derivative (cadr expr))))
    ;sinx' = cosx
    ((equal? (car expr) 'sin) (list '* (list 'cos (cadr expr)) (derivative (cadr expr))))
    ;lnx = 1/x
    ((equal? (car expr) 'log) (list '* (list 'expt (cadr expr) (- 1)) (derivative (cadr expr))))
    ;возводим х в степень
    ((equal? (car expr) 'expt) (list '* expr (list 'log (cadr expr)) (derivative (caddr expr))))
    
    ))
