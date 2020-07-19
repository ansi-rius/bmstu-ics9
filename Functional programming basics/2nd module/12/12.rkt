(use-syntax (ice-9 syncase))
;(make-source sequence)
(define (make-source sequence . end)
  (define (helper)
    (or
     (and (vector? sequence) (vector->list sequence))
     (and (string? sequence) (string->list sequence))
     (and (list? sequence) sequence)))
  (or
   (and (null? end) (list (helper) #f))
   (list (helper) (car end))))

;(peek src)

(define (peek s)
  (if (null? (car s))
      (car (cdr s))
      (caar s)))

;(next src [end])

(define-syntax next
  (syntax-rules ()
    ((peek s)
     (if (null? (car s))
         (cadr s)
         (let ((result (caar s)))
           (begin (set! s (list (cdar s) (cadr s))) 
                  result))))))