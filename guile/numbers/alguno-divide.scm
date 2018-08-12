(define (alguno-divide lst num)
  (call/cc
   (lambda (return)
     (for-each (lambda (e)
                 (if (= (modulo num e) 0)
                     (return e))
                 (if (> (* e e) num)
                     (return #f))) 
               lst)
     #f)))


(define (main argv)
  (let ((num (car argv))
        (divisores (cdr argv)))
    (alguno-divide divisores num)))


(display (command-line))
(newline)
(let ((argv (map string->number (cdr (command-line)))))
  (display (main argv))
  (newline))
