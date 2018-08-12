(define (main str-nums)
  (let ((nums (map string->number str-nums)))
    (display (apply * nums)))
  (newline))


(main (cdr (command-line)))

