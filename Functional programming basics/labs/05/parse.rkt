(define (parse vec)
  (if (not (assertions (vector->list vec)))
      (parser (vector->list vec))
      #f))

(define (parser lst)
  (define (f a result)
    (cond ((null? a) (list '() (parse-body lst)))
          ((and (equal? (car a) 'end) (null? (cdr a))) (list (parse-articles (reverse result)) (parse-body (cdr a))))
          ((and (equal? (car a) 'end) (not (equal? (car (cdr a)) 'define))) (list (parse-articles (reverse result)) (parse-body (cdr a))))
          (else (f (cdr a) (cons (car a) result)))))
  (f lst '()))

(define (parse-articles lst)
  (define (f a article result)
    (cond ((null? a) (reverse (cons (parse-article (append article '(end))) result)))
          ((equal? (car a) 'end) (f (cdr a) '() (cons (parse-article (append article '(end))) result)))
          (else (f (cdr a) (append article (list (car a))) result))))
    (f lst '() '()))

(define (parse-article lst)
  (define (f a expr)
    (cond ((equal? (car a) 'end) (list (cadr expr) (parse-body (cddr expr))))
          (else (f (cdr a) (append expr (list (car a)))))))
  (f lst '()))

(define (parse-body lst)
  (define (f a res)
    (cond ((null? a) res)
          ((and (equal? (car a) 'if) (if-inside (cdr a))) (f (skip-if lst '()) (append res (list (list 'if (parse-body (return lst (cdr a) (skip-if lst '()))))))))
          ((equal? (car a) 'if) (f (return-index a) (append res (list (list 'if (parse-body (skip (cdr a))))))))
          ((not (equal? (car a) 'endif)) (f (cdr a) (append res (list (car a)))))
          (else (f (cdr a) res))))
  (f lst '()))

(define (skip-if lst res)
  (cond ((null? lst) res)
        ((equal? (car lst) 'endif) (skip-if (cdr lst) lst))
        (else (skip-if (cdr lst) res))))

(define (return lst a b)
  (define (f a b c d)
    (cond ((equal? (car a) (car c)) (f a b (cdr c) (reverse c)))
          ((and (not (null? d)) (equal? (car b) (car d))) (reverse (cdr d)))
          ((null? d) (f a b (cdr c) d))
          (else f a b (cdr c) (cdr d))))
  (f a b lst '()))

(define (return-index lst)
  (cond ((equal? (car lst) 'endif) (cdr lst))
       (else (return-index (cdr lst)))))

(define (if-inside lst)
  (cond ((equal? (car lst) 'endif) #f)
        ((equal? (car lst) 'if))
        (else (if-inside (cdr lst)))))

(define (skip lst)
  (cond ((equal? (car lst) 'endif) '())
        (else (cons (car lst) (skip (cdr lst))))))

(define (assertions lst)
  (cond ((and (member 'end lst) (not (member 'define lst))))
        ((and (member 'define lst) (not (member 'end lst))))
        ((and (member 'if lst) (not (member 'endif lst))))
       ((and (member 'endif lst) (not (member 'if lst))))
        ((define-asserts lst #f))
        (else #f)))

(define (define-asserts lst b)
  (cond ((null? lst) #f)
        ((and (equal? (car lst) 'define) b))
        ((equal? (car lst) 'define) (define-asserts (cdr lst) (not b)))
        ((equal? (car lst) 'end) (define-asserts (cdr lst) (not b)))
        (else (define-asserts (cdr lst) b))))


(parse #(1 2 +))
(newline)

(parse #(x dup 0 swap if drop -1 endif)) 
(newline)
(parse #(define abs 
             dup 0 < 
             if neg endif 
             end 
             9 abs 
             -9 abs))
(newline)

(parse #( define -- 1 - end 
          define =0? dup 0 = end 
          define =1? dup 1 = end 
          define factorial 
              =0? if drop 1 exit endif 
              =1? if drop 1 exit endif 
              dup -- 
              factorial 
              * 
          end 
          0 factorial 
          1 factorial 
          2 factorial 
          3 factorial 
          4 factorial ))
(newline)

(parse #(define =0? dup 0 = end 
             define <0? dup 0 < end 
             define signum 
             =0? if exit endif 
             <0? if drop -1 exit endif 
             drop 
             1 
             end 
             0 signum 
             -2 signum ))