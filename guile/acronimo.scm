#!/usr/bin/guile -s
!#

(use-modules (ice-9 regex))

(define (fst-of-match! mtch)
  (set-cdr! (array-ref mtch 1) (+ 1 (car (array-ref mtch 1)))))

(define (string->acronimo str)
  (let ((matches (list-matches "[a-zA-Z0-9.]+" str)))
    (map fst-of-match! matches)
    (map match:substring matches)))

(map (lambda (s)
       (display (string-concatenate (string->acronimo s))))
     (cdr (command-line)))
(newline)
