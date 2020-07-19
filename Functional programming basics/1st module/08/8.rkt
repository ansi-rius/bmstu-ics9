(define (pack ls)  
  (helper ls '() '()))

(define (helper xs res same-symbols) 
  (if (null? (cdr xs))
      (append res (list (append same-symbols (list (car xs)))))
      (if (equal? (car xs) (cadr xs)) 
          (helper (cdr xs) res (append same-symbols (list(car xs)))) 
          (helper (cdr xs) (append res (list (append same-symbols (list (car xs))))) '()))))
;(append res (list (append same-symbols (list (car xs)))))
;(pack '(a a a b b c))       ; ((a a a) (b b) (c))
;(pack '((1 2) (1 2) (2 3))) ; (((1 2) (1 2)) ((2 3)))

(define (counter xs count)
  (if (= (length xs) 0)
      count
      (counter (cdr xs) (+ count 1))))

;(define (encode xs)
;  (counter (pack xs) 0))
;  (if (null? (cdr (pack xs))) ;((a a a) (b b) (c))
;      (append (list (caar (pack xs))) (counter (list (car (pack xs))) 0)) 
;      (append (list (caar (pack xs))) (counter (list (car (pack xs))) 0)))
;  (encode (cdr (pack xs))))
(define (encode ls)
  (map (lambda (xs) (list (car xs) (length xs))) (pack ls)))

(define (unpack ls)
  (help ls))

(define (unpack ls) 
  (define (help xs res) 
    (define (unpackage symb k res-unpack) 
      (if (> k 0) 
          (unpackage symb (- k 1) (append res-unpack (list symb))) ;печатаю буквы пока < k
          (set! res (append res (list res-unpack))))) ;res = ^
    (if (null? xs)
        res
        (begin
          (unpackage (caar xs) (cadr(car xs)) '()) ;(a) (3)
          (help (cdr xs) res)))) 
  (help ls '())) 

(define (decode ls)
  (apply append (unpack ls)))
;(encode '(a a a b b c)) ; ((a 3) (b 2) (c 1))
;(unpack '((a 3) (b 2) (c 1))) ; ((a a a) (b b) (c))
;(decode '((a 3) (b 2) (c 1))) ; (a a a b b c)

