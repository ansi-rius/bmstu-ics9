(define (delete xs)
  (cond ((equal? #\space (car xs)) (delete (cdr xs)))
        ((equal? #\tab (car xs)) (delete (cdr xs)))
        ((equal? #\newline (car xs)) (delete (cdr xs)))
        (else xs)))

(define (string-trim-left str) ;пробелы слева
  (list->string (delete (string->list str))))

(define (string-trim-right str) ;пробелы справа
  (list->string (reverse (delete (reverse (string->list str))))))

(define (string-trim str)
  (string-trim-left (string-trim-right str)))

(define (if-b-contains-a? a b)
  (cond ((null? a) #t)
        ((equal? (car a) (car b))
         (if-b-contains-a? (cdr a) (cdr b)))
        (else #f)))

(define (string-prefix? a b) ; a - начало, b - конец
  (if-b-contains-a? (string->list a) (string->list b)))

(define (string-suffix? a b)
  (if-b-contains-a? (reverse (string->list a))
                    (reverse (string->list b))))

(define (string-infix? a b)
  (define (helper a b)
    (cond ((null? a) #t)
          ((null? b) #f)
          (else
           (if (equal? (car a) (car b))
               (helper (cdr a) (cdr b))
               (helper a (cdr b))))))
  (helper (string->list a) (string->list b)))

(define (another-delete xs1 num)
  (if (= num 0)
      xs1
      (another-delete (cdr xs1) (- num 1))))

(define (string-split str sep)
  (let ((deleted (string->list sep)))
    (define (help xs in-xs final-xs)
      (if (null? xs)
          (reverse (cons (list->string (reverse in-xs)) final-xs))
          (if (if-b-contains-a? deleted xs)
              (help (another-delete xs (length deleted))
                    '()
                    (cons (list->string in-xs) final-xs))
              (help (cdr xs) (cons (car xs) in-xs) final-xs))))
    (help (string->list str) '() '())))