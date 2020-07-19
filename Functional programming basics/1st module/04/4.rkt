(define (golden f a b e)
  (if (> (f (- b (/ (- b a) (/ (+ 1 (sqrt 5)) 2)))) ;x0
         (f (+ a (/ (- b a) (/ (+ 1 (sqrt 5)) 2))))) ;x1
      (if (< (abs (- b (- b (/ (- b a) (/ (+ 1 (sqrt 5)) 2))))) e)
          (/ (+ (- b (/ (- b a) (/ (+ 1 (sqrt 5)) 2))) b) 2)
          (golden f (- b (/ (- b a) (/ (+ 1 (sqrt 5)) 2))) b e))
      (if (< (abs (- (+ a (/ (- b a) (/ (+ 1 (sqrt 5)) 2))) a)) e)
          (/ (+ a (+ a (/ (- b a) (/ (+ 1 (sqrt 5)) 2)))) 2)
          (golden f a (+ a (/ (- b a) (/ (+ 1 (sqrt 5)) 2))) e))))
;(round (golden (lambda (x) (+ (* x x) (* 4 x) 4)) -5.0 5.0 1e-06))
  