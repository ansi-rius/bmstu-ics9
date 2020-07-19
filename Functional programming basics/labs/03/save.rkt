(define (save-data data addr)
  (call-with-output-file addr
    (lambda (port)
      (write data port))))

(define (load-data addr)
  (call-with-input-file addr
    (lambda (port)
      (read port))))

(define (string-counter addr)
  (call-with-input-file addr
    (lambda (port)
      (define (helper counter)
        (if (eof-object? (peek-char port)) ;end-of-file
            counter
            (if (equal? newline (read-char port)) ;read next char
                (begin (read port) (helper (+ counter 1))) ;+1
                (begin (read port) (helper (+ counter 1))))))
      (helper 0))))
(save-data 12345678 "13.txt")
(load-data "13.txt")
(string-counter "13.txt")