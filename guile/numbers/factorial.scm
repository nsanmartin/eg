;;(use-modules (ice-9 format))

(define (factorial n)
  (do ((n n (- n 1))
       (fact 1 (* fact n)))
      ((> 1 n) fact)))

(let loop ((l (map string->number (cdr (command-line)))))
  (if (not (null? l))
      (begin
        (format #t "~a: ~a\n" (car l) (factorial (car l)))
        (loop (cdr l)))))



