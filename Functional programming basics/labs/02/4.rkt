(define (x^2? expr)
  (and (list? expr)
       (eq? (car expr) 'expt) 
       (eq? (list-ref expr 2) 2))) ;степень - двойка?
;(define (x^2? expr)
;  (and (list? expr)
;     (eq? (car expr) 'expt )
;     (or (symbol? (cadr expr))
;       (list? (cadr expr))
;       (number? (cadr expr)))))

(define (factorize expr)     ;((- (expt x 2) (expt y 2))
  (define (a xs) 
    (car (cdr (car (cdr xs))))) ;first (expt x 2)
  (define (b ys) 
    (car (cdr (list-ref ys 2)))) ;second (expt y 2)

  (if (eq? (car expr) '+) ;если плюс, только с 3ей степенью
      (list '* (list '+ (a expr) (b expr));1ая скобка тройки (- х у)
                   (list '+ (list 'expt (a expr) 2);(expt x/a 2) вторая степень
                   (list '- (list '* (a expr) (b expr)));(* х у)
                   (list 'expt (b expr) 2)))
      
      (if (x^2? (list-ref expr 1)) ;если минус
          (list '* (list '+ (a expr) (b expr)) (list '- (a expr) (b expr))) ;если двойка
          (list '* (list '- (a expr) (b expr));1ая скобка тройки (- х у)     ;если тройка
                   (list '+ (list 'expt (a expr) 2) ;(expt x/a 2) вторая степень
                            (list '* (a expr) (b expr)) ;(* х у)
                            (list 'expt (b expr) 2)))))) ;(expt y/b 2)
 
  
 ; (define (a^2-b^2? expr)
 ; (and (list? expr)
 ;   (eq? (car expr) '-)
 ;   (x^2? (list-ref expr 1))
  ;  (x^2? (list-ref expr 2))))
(factorize '(- (expt x 2) (expt y 2)))
(factorize '(- (expt (+ first 1) 2) (expt (- second 1) 2)))
(eval (list (list 'lambda '(x y) (factorize '(- (expt x 2) (expt y 2)))) 1 2) (interaction-environment))
(factorize (quote (- (expt x 2) (expt y 2))))
;(factorize (quote (- (expt x 3) (expt y 3))))
;(factorize (quote (- (expt (+ a 1) 2) (expt (- b 1) 2))))
;(factorize (quote (+ (expt x 3) (expt y 3))))