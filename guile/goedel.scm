#!/usr/bin/guile -s
!#

(use-modules (ice-9 getopt-long))

(define (strlst->numlst  str-nums)
  (let ((nums (map string->number str-nums)))
     (apply + nums)))

(define (siguiente-primo primos)
  (cond
   ((null? primos) 2)
   (#t     
    (buscar-siguiente-primo
     primos
     primos
     (1+ (car (last-pair primos)))))))

(define (agregar-n-primos n primos)
  (if (= 0 n)
      primos
      (agregar-n-primos (1- n)
                        (append primos (list (siguiente-primo primos))))))

(define (n-primos n)
  (agregar-n-primos (1- n) (list 2)))


(define (buscar-siguiente-primo primos primos-restantes numero)
  (cond
   ((null? primos-restantes) numero)
   ((= 0 (modulo numero (car primos-restantes)))
    (buscar-siguiente-primo primos primos (1+ numero)))
   ((> (* (car primos-restantes) (car primos-restantes)) numero)
    (buscar-siguiente-primo  primos (cdr primos-restantes)  numero))
   (#t  
    (buscar-siguiente-primo primos (cdr primos-restantes) numero))))

(define (buscar-potencia base num pot)
  (if (not (= (modulo num  (expt base pot)) 0))
      (1- pot)
      (buscar-potencia base num (1+ pot))))
      

(define (buscar-potencia-siguiente dividendo pots primos)
  (cond
   ((= dividendo 1) pots)
   (#t
    (let* ((primo-sgt (siguiente-primo primos))
           (potencia (buscar-potencia primo-sgt dividendo 0))
           (nuevo-dividendo (quotient dividendo (expt primo-sgt potencia))))
        
      (buscar-potencia-siguiente
       nuevo-dividendo
       (append pots (list potencia))
       (append primos (list primo-sgt)))))))
               
    
(define (goedel->seq number)
  (buscar-potencia-siguiente
   number
   (list)
   (list)))


;; (define (main args)
;;   (let* ((option-spec '((potencias (single'char #\p) (value #f))))
;;          (options (getopt-long args option-spec))
;;          (hacer-producto (option-ref options 'potencias #f))) ))

(define (display-help)
  (display "\
goedel [options]
  -h, --help       Display this help
  -p, --potencias  Calcular el producto de primos elevados a las potencias
                   provistas.
"))

(define (drop l n)
  (if (= 0 n) l
      (drop (cdr l) (1- n))))

(define (display-prod l)
  (let ((primos (n-primos (length l))))
    (display
     (potencia-listas primos l 1))))

(define (potencia-listas b e a)
  (if (null? b) a
      (potencia-listas
       (cdr b) (cdr e)
       (* a (expt (car b) (car e))))))


(define (display-potencias num)
  (let ((pots (goedel->seq num)))
    (display
     (format #f "num: ~a\npotencias\n~a\n" num pots))))


(define (main args)
  (let* ((option-spec '((help    (single-char #\h) (value #f))
                        (potencias (single-char #\p) (value #f))
                        (decrementar (single-char #\d) (value #f))))
         (options (getopt-long args option-spec))
         (help-wanted (option-ref options 'help #f))
         (potencias-primos (option-ref options 'potencias #f))
         (decrementar-uno (option-ref options 'decrementar #f)))
    (cond
     (help-wanted (display-help))
     (potencias-primos
      (let* ((l (map string->number (cddr args)))
             (primos (n-primos (length l)))
             (resultado (potencia-listas primos l 1)))
        (if decrementar-uno (set! resultado (1- resultado)))
        (display resultado)))
      ((not (null? (cdr args)))
       (display-potencias (string->number (cadr args))))
      (#t
       (display-help)))))


(main (command-line))

