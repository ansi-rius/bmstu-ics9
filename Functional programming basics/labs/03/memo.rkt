(define tribm
  (let ((memo '()))
    (lambda (n)
      (let ((memorized (assq n memo)))
        (if memorized
            (cadr memorized)
            (let ((new-value (if (<= n 1) 0 (if (= n 2) 1
                                                (+ (tribm (- n 1)) (tribm (- n 2)) (tribm (- n 3)))))))
              (set! memo (cons (list n new-value) memo))
              new-value))))))
(tribm 5) ; 1 1 2 4 7 13