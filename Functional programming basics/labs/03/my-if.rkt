(define-syntax my-if 
  (syntax-rules ()
    
    ((_ pred? expr1) 
     (let ((x (delay expr1))) 
       (and pred? (force x))))
    
    ((_ pred? expr1 expr2) 
     (let ((x (delay expr1))  ;x - 1ое выражение y - 2 выраж.
           (y (delay expr2))) 
       (or (and pred? (force x)) 
           (force y)))))) 

(my-if #t 1 (/ 1 0)) ; 1
(my-if #f (/ 1 0) 1) ; 1
(my-if #t (/ 1 2) 1) ; 1/2