(define (day-of-week d m y)
  (remainder (- (+ (- y (quotient (- 14 m) 12)) d 7000
     (quotient (- y (quotient(- 14 m) 12)) 4)
     (quotient (- y (quotient (- 14 m) 12)) 400)
     (quotient (* 31 (- (+ m (* 12 (quotient (- 14 m) 12))) 2)) 12))
     (quotient (- y (quotient (- 14 m) 12)) 100))
     7))