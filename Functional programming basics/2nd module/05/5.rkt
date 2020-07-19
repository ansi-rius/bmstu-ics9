(define (read-words)
  (reader (read) '()))

(define (reader xs result)
  (if (eof-object? xs)
      result
      (if (number? xs)
          (reader (read) (append result (list (number->string xs))))
          (reader (read) (append result (list (symbol->string xs)))))))