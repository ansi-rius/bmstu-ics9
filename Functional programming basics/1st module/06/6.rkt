(define (list->set xs) 
  (if (not (null? xs)) 
      (if (correct? (car xs) (cdr xs)) 
          (list->set (cdr xs)) 
          (cons (car xs) (list->set (cdr xs)))) 
      '())) 

(define (correct? x xs) 
  (and (> (length xs) 0) 
       (or (equal? x (car xs)) (correct? x (cdr xs))))) 

(define (set? xs) 
  (or (and (not (null? xs)) 
           (and (not (correct? (car xs) (cdr xs))) 
                (or (null? (cdr xs)) (set? (cdr xs))))) 
      (null? xs))) 

(define (set-eq? xs ys)
  (and (set? xs) (set? ys)
       (= (length xs) (length ys))
       (equal? (intersection xs ys) xs)))

(define (union xs ys) 
  (list->set (append xs ys)))

(define (intersection xs ys) 
  (if (not (null? xs)) 
      (if (correct? (car xs) ys) 
          (cons (car xs) (intersection (cdr xs) ys)) 
          (intersection (cdr xs) ys)) 
      '())) 
          
(define (difference xs ys)
  (cond ((or (null? xs) (null? ys)) xs)
        ;((null? xs) ys)
        ;((null? ys) xs)
        (else      
         (if (equal? (car xs) (car ys))
             (difference (cdr xs) (cdr ys))
             (append (list (car xs)) (difference (cdr xs) ys))))))

(define (symmetric-difference xs ys)
  (cond ((and (null? xs) (null? ys)) xs)
        ((null? xs) ys)
        ((null? ys) xs)
        (else      
         (if (equal? (car xs) (car ys))
             (symmetric-difference (cdr xs) (cdr ys))
             (append (list (car xs)) (symmetric-difference (cdr xs) ys))))))