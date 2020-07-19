(define (end? program count)
  (if (equal? (vector-ref program count) 'end)
      (+ count 1)
      (end? program (+ count 1))))

(define (skip-if program count num-ifs)
  (cond
    ((and (equal? (vector-ref program count) 'endif)
          (equal? num-ifs 1))
     (+ count 1))
    ((equal? (vector-ref program count) 'endif)
     (skip-if program (+ count 1) (- num-ifs 1)))
    ((equal? (vector-ref program count) 'if)
     (skip-if program (+ count 1) (+ num-ifs 1)))
    (else
     (skip-if program (+ count 1) num-ifs))))

(define (interpret program given-stack)
  (define (word-interp wcount stack return dict) ;вектор, счетчик, стек, возврат, словарь
    (if (< wcount (vector-length program))
        (let* ((word (vector-ref program wcount))
               (func (assoc word dict)))
          (cond
            ;Числа
            ((number? word)
             (word-interp (+ wcount 1) (cons word stack) return dict))
            ;Словарная статья
            (func (word-interp (cadr func) stack (cons (+ wcount 1) return) dict))
            ;Управляющие конструкции
            ((equal? word 'define) ;Начинает словарную статью — определение слова word

             (word-interp (end? program wcount)
                          stack
                          return
                          (cons (list (vector-ref program (+ wcount 1)) (+ wcount 2)) dict)))
            ((or (equal? word 'end)   ;Завершает статью
                 (equal? word 'exit)) ;Завершает выполнение процедуры (кода статьи)
             
             (word-interp (car return) stack (cdr return) dict))
            
            ((equal? word 'if) ;Если флаг не равен 0, то выполняется код в теле if..endif, иначе выполнение кода до endif пропускается
             (word-interp (if (equal? (car stack) 0)
                              (skip-if program (+ wcount 1) 1)
                              (+ wcount 1))
                          (cdr stack)
                          return
                          dict))
            
            ((equal? word 'endif) ;Завершает тело if
             (word-interp (+ wcount 1) stack return dict))
            ;Арифметическиие операции
            ((equal? word '+) ;Сумма n1 и n2
             (word-interp (+ wcount 1) (cons (+ (cadr stack) (car stack)) (cddr stack)) return dict))
            
            ((equal? word '-) ;Разность: n1 - n2
             (word-interp (+ wcount 1) (cons (- (cadr stack) (car stack)) (cddr stack)) return dict))
            
            ((equal? word '*) ;Произведение n2 на n1
             (word-interp (+ wcount 1) (cons (* (cadr stack) (car stack)) (cddr stack)) return dict))
            
            ((equal? word '/) ;Целочисленное деление n1 на n2
             (word-interp (+ wcount 1) (cons (quotient (cadr stack) (car stack)) (cddr stack)) return dict))
            
            ((equal? word 'mod) ;Остаток от деления n1 на n2
             (word-interp (+ wcount 1) (cons (remainder (cadr stack) (car stack)) (cddr stack)) return dict))
            
            ((equal? word 'neg) ;смена знака числа
             (word-interp (+ wcount 1) (cons (- (car stack)) (cdr stack)) return dict))
            
            ;Операции сравнения
            ((equal? word '=) ;Флаг равен -1, если n1 = n2, иначе флаг равен 0
             (word-interp (+ wcount 1) (cons (if (equal? (cadr stack) (car stack)) -1 0) (cddr stack)) return dict))
            
            ((equal? word '>) ;Флаг равен -1, если n1 > n2, иначе флаг равен 0
             (word-interp (+ wcount 1) (cons (if (> (cadr stack) (car stack)) -1 0) (cddr stack)) return dict))
            
            ((equal? word '<) ;Флаг равен -1, если n1 < n2, иначе флаг равен 0
             (word-interp (+ wcount 1) (cons (if (< (cadr stack) (car stack)) -1 0) (cddr stack)) return dict))
            
            ;Логические операции
            ((equal? word 'not) ;НЕ n
             (word-interp (+ wcount 1) (cons (if (equal? (car stack) 0) -1 0) (cdr stack)) return dict))
            
            ((equal? word 'and) ;n2 И n1
             (word-interp (+ wcount 1) (cons (if (or (equal? (cadr stack) 0) (equal? (car stack) 0)) 0 -1) (cddr stack)) return dict))
            
            ((equal? word 'or) ;n2 ИЛИ n1
             (word-interp (+ wcount 1) (cons (if (and (equal? (cadr stack) 0) (equal? (car stack) 0)) 0 -1) (cddr stack)) return dict))
            
            ;Операции со стеком
            ((equal? word 'drop) ;Удаляет элемент на вершине стека
             (word-interp (+ wcount 1) (cdr stack) return dict))
            
            ((equal? word 'swap) ;Меняет местами два элемента на вершине стека
             (word-interp (+ wcount 1) (cons (cadr stack) (cons (car stack) (cddr stack))) return dict))
            
            ((equal? word 'dup) ;Дублирует элемент на вершине стека
             (word-interp (+ wcount 1) (cons (car stack) stack) return dict))
            
            ((equal? word 'over) ;Копирует предпоследний элемент на вершину стека
             (word-interp (+ wcount 1) (cons (cadr stack) stack) return dict))
            
            ((equal? word 'rot) ;Меняет местами первый и третий элемент от головы стека
             (word-interp (+ wcount 1) (cons (caddr stack) (cons (cadr stack) (cons (car stack) (cdddr stack)))) return dict))
            
            ((equal? word 'depth) ;Возвращает число элементов в стеке перед своим вызовом
             (word-interp (+ wcount 1) (cons (length stack) stack) return dict))))
        stack))
  (word-interp 0 given-stack '() '()))

(interpret #( define abs
               dup 0 <
               if neg endif
               end
               abs ) ; программа
           '(-9)) ; исходное состояние стека