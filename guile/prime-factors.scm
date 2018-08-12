#!/usr/bin/guile
!#

(define (veces-que-divide d n)
  (if (= 0 (remainder n d))
      (1+ (veces-que-divide d (/ n d)))
      0))

(define (factores-p n)
  (define (recu i n)
    (cond  ((> i n)
            '())
           ((= 0 (remainder n i))
            (cons `(,i . ,(veces-que-divide i n))
                  (recu (1+ i) (/ n i) )))
           (else
            (recu (1+ i) n))))
  (recu 2 n))


(display (factores-p (string->number (cadr (command-line)))))
