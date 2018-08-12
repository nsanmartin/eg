(display "Usando for-each:\n")

(for-each (lambda (e) (display e) (newline))
          (command-line))

(display "\nUsando map:\n")
(map  (lambda (e) (display e) (newline))
          (command-line))
