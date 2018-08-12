(define (fib n)
  (do ((i (- n 1) (- i 1))
	(f1 1 (+ f1 f2))
	(f2 1 f1))
      ((<= i 1) f1 )))

(let loop ((l (map string->number (cdr (command-line)))))
  (if (not (null? l))
      (begin
        (format #t "~a: ~a\n" (car l) (fib (car l)))
        (loop (cdr l)))))

