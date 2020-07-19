(define (ref l-v i) ;list-vector, index
    (if (null? l-v)
        #f
        (cond ((vector? l-v) (if (< i (vector-length l-v)) (vector-ref l-v i) #f))
              ((list?   l-v) (if (< i (length l-v)) (list-ref   l-v i) #f))
              ((string? l-v) (if (< i (string-length l-v)) (string-ref l-v i) #f)))))
              

(ref '(1 2 3) 1) ; 2
(ref #(1 2 3) 1) ; 2
(ref "123" 1)    ; #\2
(ref "123" 3)    ; #f



;(define (build v1 i1 n1)
; (begin (vector-ref v1 i1)
;       (if (not (= (i1 i))) (+ i1 1)
;               n1)))

;(define (ref1 l-v i n)
; (if (null? l-v)
;       #f
;      (build-vector (+ i 1) build)))

;(ref1 '(1 2 3) 1 0)   ;  (1 0 2 3)
;(ref1 #(1 2 3) 1 0)   ; #(1 0 2 3)
;(ref1 #(1 2 3) 1 #\0) ; #(1 #\0 2 3)
;(ref1 "123" 1 #\0)    ;"1023"
;(ref1 "123" 1 0)      ;#f
;(ref1 "123" 3)        ;#f