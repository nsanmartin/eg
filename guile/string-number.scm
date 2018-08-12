


(define (main str-nums)
  (let ((nums (map string->number str-nums)))
    (display nums))
  (newline))


(main (cdr (command-line)))

