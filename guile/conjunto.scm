(define l '( 2 4  18 84 ))
(define m '(1 2 3 8 92 9))
(define uno '(1))
(define vv '(()))
(define uu '((1)))

(define (caar l) (car (car l)))

(define (menor?-bkp o p)
  (cond
   ((number? o) (< o p))
   ((and (list? o) (list? p))
    (if (null? o) #t
        (if (null? p) #f
            (if (< (car o) (car p)) #t
                (if (> (car o) (car p)) #f
                    (menor? (cdr o) (cdr p)))))))
   (#t "error")))


(define (menor? o p)
  (cond
   ((number? o) (< o p))
   ((and (null? o) (null? p)) #f)
   ((and (list? o) (list? p))
    (cond
     ((null? o) #t)
     ((null? p) #f)
     ((and (number? (car o)) (number? (car p)))
      (if (< (car o) (car p)) #t
          (if (> (car o) (car p)) #f
              (menor? (cdr o) (cdr p)))))
     ((and (list? (car o)) (list? (car p)))
      (cond
       ((and (null? (car o)) (null? (car p))) #f)
       ((null? (car o)) #t)
       ((null? (car p)) #f)
       ((and (number? (caar o)) (number? (caar p)))
        (if (menor? (car o) (car p)) #t
            (if (menor? (car p) (car o)) #f
                (menor? (cdr o) (cdr p)))))))))
   (#t "error")))

;; generadores
(define vacio (lambda () '()))
(define (ag e c) (sort-list (cons e c) menor?))

;;
(define (dame-uno c) (car c)) 
(define (sin-uno c) (cdr c))
(define (union b c)
  (cond
   ((null? b) c)
   ((null? c) b)
   ((menor? (car c) (car b)) (cons (car c) (union (cdr c) b)))
   ((menor? (car b) (car c)) (cons (car b) (union c (cdr b))))
   ((equal? (car b) (car c)) (cons (car b) (union (cdr b) (cdr c))))
   (#t
    (list "hubo un error en union: " b c))))
    

(define (subconjuntos b c)
  (if (null? c) (ag b '())
      (union
       (subconjuntos (vacio) (union b (sin-uno c)))
       (subconjuntos (ag (dame-uno c) b) (sin-uno c)))))


(define dos '(1 2))
(define tres '(1 2 3))
(define cuatro '(1 2 3 4))
(define (partes c) (subconjuntos '() c))
(define su sin-uno)
(define du dame-uno)
(define sc subconjuntos)
