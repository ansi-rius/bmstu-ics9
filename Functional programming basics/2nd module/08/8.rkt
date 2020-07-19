 (use-syntax (ice-9 syncase))

(define-syntax define-memoized
  (syntax-rules ()
    ((_ (function n ...) body)
     (define function (memoiz (eval (list 'lambda (list 'n ...) 'body)
                                    (interaction-environment)))))
    ((_ function body)
     (define function (memoiz (eval 'body (interaction-environment)))))))

(define memoiz (lambda (function)
                  (let ((memo '()))
                    (lambda n
                      (let ((memozed (assoc n memo)))
                        (if memozed
                            (cadr memozed)                  
                            (let ((new-value (apply function n)))
                              (set! memo (cons (list n new-value) memo))
                              new-value)))))))

;(begin
;  (define-memoized (trib n)
;    (cond
;      ((= n 0) 0)
;      ((= n 1) 1)
;      ((= n 2) 1)
;      (else (+ (trib (- n 1))
;               (trib (- n 2))
;               (trib (- n 3))))))
;
;  (map trib '(10 50 100 200))
;  (map trib '(10 50 100 200)))