(use-syntax (ice-9 syncase))

;1) when ; unless
(define-syntax when
  (syntax-rules()
    ((when cond? expr ...)
     (if cond? (begin expr ...)))))

;(define x 3)
;(when   (> x 0) (display x) (display " > 0 ") (newline))

(define-syntax unless
  (syntax-rules()
    ((unless cond? expr ...)
     (if (not cond?) (begin expr ...)))))

;(unless (= x 0) (display x) (display " != 0") (newline))

;2) for ... in ; for ... as

(define-syntax for
  (syntax-rules (as in) 
    ((for index as where body ...)
     (for-each (lambda (where) body ...) index))
    ((for where in index body ...)
     (for index  as where body ...))))


;(for i in '(1 2 3)
;  (for j in '(4 5 6)
;    (display (list i j))
;    (newline))) 

;(for '(1 2 3) as i
;  (for '(4 5 6) as j
;    (display (list i j))
;    (newline)))

;3) while

(define-syntax while
  (syntax-rules ()
    ((while cond? expr ...)
     (letrec ((iter (lambda ()
                      (if cond?
                          (begin
                            expr ...
                            (iter))))))
       (iter)))))

;(let ((p 0)
;      (q 0))
;  (while (< p 3)
;         (set! q 0)
;         (while (< q 3)
;                (display (list p q))
;                (newline)
;                (set! q (+ q 1)))
;         (set! p (+ p 1))))


;3) repeat...until

(define-syntax repeat
  (syntax-rules (until)
    ((repeat (expr ...) until cond?)
     (letrec ((iter (lambda()
                      (begin
                        expr ...
                        (if (not cond?) (iter))))))
       (iter)))))

;(let ((i 0)
;      (j 0))
;  (repeat ((set! j 0)
;           (repeat ((display (list i j))
;                    (set! j (+ j 1)))
;                   until (= j 3))
;           (set! i (+ i 1))
;           (newline))
;          until (= i 3)))

;4) cout

(define-syntax cout
  (syntax-rules ()
    ((cout '(<< args . xxs)  ys)
     (if (equal? 'args 'endl)
         (cout 'xxs (cons '(newline) ys))
         (cout 'xxs (cons '(display args) ys))))
    ((cout '() xs) (eval (cons 'begin (reverse xs))
                      (interaction-environment)))
    ((cout . xs) (cout 'xs '()))))

;(cout << "a = " << 1 << endl << "b = " << 2 << endl)