(use-syntax (ice-9 syncase))
; (let ([id val-expr] ...) body ...+)
(define-syntax my-let
  (syntax-rules ()
    ((_ ((id val-expr) ...) body ...)
     ((lambda (id ...) body ...) val-expr ...))))

; (let* ([id val-expr] ...) body ...+)
(define-syntax my-let*
  (syntax-rules ()
    ((_ ((id val-expr)) body ...)
     (my-let ((id val-expr)) body ...))
    ((_ ((id val-expr) (id1 val-expr1) ...) body ...)
     (my-let ((id val-expr))
             (my-let* ((id1 val-expr1) ...) body ...)))))