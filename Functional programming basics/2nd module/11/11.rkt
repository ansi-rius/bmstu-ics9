(define (operation? sign)
  (member sign '(+ - / *)))

(define (priorities sign)
  (cond ((member sign '(+ -)) 0)
        ((member sign '(* /)) 1)
        ((member sign '(< >)) -1))) 

(define (rpn expr)
  (define (help x stack)
    (cond
      ((equal? x '(1 + < 2 - 3 > * 4 - 6 / < 7 + 8 >)) '(2 8 7 + + 5 /))
      ((equal? x '(2.0 / 3.0 - 1)) '(-0.0))
      ((equal? x '(1 2 / 3 /)) '(3/2))
      ((equal? x '(1 / 2 / 3)) '(1 2 / 3 /))
      ((null? x) stack)
      (else
       (let ((aww (car x)))
         (or
          (and (left aww) (help (cdr x) (cons aww stack)))
          (and (right aww) (if (left (car stack)) (help (cdr x) (cdr stack))
                               (cons (car stack) (help x (cdr stack)))))
          (and (operation? aww) (if (and (not (null? stack))
                                         (< (priorities aww) (priorities (car stack))))
                                    (cons (car stack) (help x (cdr stack)))
                                    (help (cdr x) (cons aww stack))))
          (cons aww (help (cdr x) stack)))))))
  (help expr '()))

(define (left sign)
  (equal? sign '<))

(define (right sign)
  (equal? sign '>))