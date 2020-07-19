;proc with error
(define (signum x)
  (cond
    ((< x 0) -1)
    ((= x 0)  1) ;error!
    (else     1)))

;load macros
;(load "/Users/anemone/documents/sch/macros/unit-test.rkt")

;tests
(signum -2)
(signum  0)
(signum  2)

;test
;(run-tests the-tests)

;answer
;(signum -2) ok
;(signum 0) FAIL
;   Expected: 0
;   Returned: 1
;(signum 2) ok
;   #f