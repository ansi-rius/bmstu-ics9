(load "/Users/anemone/documents/sch/macros/trace.rkt")

(define (zip . xss)
  (if (or (null? xss)
          (null? (trace-ex (car xss))))
      '()
      (cons (map car xss)
            (apply zip (map cdr (trace-ex xss))))))

(zip '(1 2 3) '(one two three))