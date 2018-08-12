#!/usr/bin/guile \
-e main -s
!#

(use-modules (ice-9 getopt-long))
(use-modules (ice-9 format))

(define (siguiente-primo primos)
  (cond
   ((null? primos) 2)
   (#t (buscar-siguiente-primo
        primos
        primos
        (1+ (car (last-pair primos)))))))

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
      (agregar-n-primos
       (1- n)
       (append primos (list (siguiente-primo primos))))))

(define (n-primos n) (agregar-n-primos (1- n) (list 2)))

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
               
    
(define (number->instructions-list number)
  (buscar-potencia-siguiente
   (1+ number)
   (list)
   (list)))


(define (buscar-left number x)
  (if (not (= 0 (modulo number (expt 2 x))))
      (1- x)
      (buscar-left number (1+ x))))
           
(define (l number)  (buscar-left (1+ number) 1))
(define (r number)
  (let ((izq (l number))
        (n (1+ number)))
    (/ (1- (/ n (expt 2 izq)))
       2)))

(define (par x y) (1- (* (expt 2 x) (1+ (* 2 y)))))


(define (number->intr-tuple number)
  (cons (l number)
        (cons (r (l number))
              (r (r number)))))

(define (number->etiqueta number) (l number))
(define (number->variable number) (1+ (r (r number))))
(define (number->instruccion number)
  (let ((inst (l (r number)))
        (var (number->variable number))
        (etiqueta (if (> (l number) 0)
                      (format #f "[E~a]" (l number))
                      "")))
    (cond
     ((= 0 inst)
      (format #f "~a\t V~a <- V~a\t; ~a\n" etiqueta var var number))
     ((= 1 inst)
      (format #f "~a\t V~a <- V~a + 1\t; ~a\n" etiqueta var var number))
     ((= 2 inst)
      (format #f "~a\t V~a <- V~a - 1\t; ~a\n" etiqueta var var number))
     (#t
      (format #f "~a\t IF V~a != 0 GOTO E~a\t; ~a\n"
              etiqueta var (- inst 2) number )))))


(define (display-S-prog arg)
  (let* ((programa (string->number arg))
       (instr-list (number->instructions-list programa)))
    (display "instruction list:\n")
    (display instr-list) (newline) (newline)
    (map (lambda (instru)
           (display (number->instruccion instru)))
         instr-list))
  (newline))

(define (main argv)
  (let ((args (cdr argv)))
    (if (not (= 1 (length args)))
        (display "Debe proveer un (u'nico) argumento\n")
        (display-S-prog (car args)))))

