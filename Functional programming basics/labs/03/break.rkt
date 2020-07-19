(define stop #f) ;аварийная остановка, помещаем в неё #f

(define-syntax use-assertions
  (syntax-rules ()
    ((_) (call-with-current-continuation ;escape-procedure
          (lambda (expression)
            (begin
              (set! stop expression)))))))

(define-syntax assert
  (syntax-rules ()
    ((_ expr) (if (not expr) ;если условие не выполнилось -> аварийная остановка
                  (begin (display "FAILED: ")
                         (display 'expr)
                         (stop))))))

(use-assertions)

(define (1/x x)
  (assert (not (zero? x)))
  (/ 1 x))

(map 1/x '(1 2 3 4 5))
(map 1/x '(-2 -1 0 1 2))