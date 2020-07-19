;proc with error
(define (signum x)
  (cond
    ((< x 0) -1)
    ((= x 0)  1) ;error!
    (else     1)))

;load macros
(load "/Users/anemone/documents/sch/macros/unit-test2.rkt")

;define list of tests
(define the-tests
  (list (test (signum -2) -1)
        (test (signum  0)  0)
        (test (signum  2)  1)))

;test
(run-tests the-tests)

;answer
;(signum -2) ok
;(signum 0) FAIL
;   Expected: 0
;   Returned: 1
;(signum 2) ok
;   #f