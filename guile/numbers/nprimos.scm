(define (sumar-todos  str-nums)
  (let ((nums (map string->number str-nums)))
     (apply + nums)))

(define (strlst->numlst  str-nums)
  (let ((nums (map string->number str-nums)))
     (apply + nums)))

(define (siguiente-primo primos)
  (buscar-siguiente-primo
   primos
   primos
   (1+ (car (last-pair primos)))))


(define (buscar-siguiente-primo primos primos-restantes numero)
  (cond
   ((null? primos-restantes) numero)
   ((= 0 (modulo numero (car primos-restantes)))
    (buscar-siguiente-primo primos primos (1+ numero)))
   ((> (* (car primos-restantes) (car primos-restantes)) numero)
    (buscar-siguiente-primo  primos (cdr primos-restantes)  numero))
   (#t  
    (buscar-siguiente-primo primos (cdr primos-restantes) numero))))

(define (agregar-n-primos n primos)
  (if (= 0 n)
      primos
      (agregar-n-primos (1- n)
                        (append primos (list (siguiente-primo primos))))))

(define (n-primos n)
  (agregar-n-primos (1- n) (list 2)))
  

(display
 (n-primos (string->number (cadr (command-line)))))
(newline)
