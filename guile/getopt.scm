#!/usr/bin/guile -s
!#

(use-modules (ice-9 getopt-long))

(define (drop l n)
  (if (= n 0)
      l
      (drop (cdr l) (1- n))))

(define (main args)
  (let* ((nopts 0)
         (option-spec '((version (single-char #\v) (value #f))
                        (help    (single-char #\h) (value #f))))
         (options (getopt-long args option-spec))
         (help-wanted (option-ref options 'help #f))
         (version-wanted (option-ref options 'version #f)))
    (if (or version-wanted help-wanted)
        (begin
          (if version-wanted
              (begin
                (set! nopts (1+ nopts))
                (display "getopt-long-example version 0.3\n")))
              
          (if help-wanted
              (begin
                (set! nopts (1+ nopts))
                (display "\
getopt-long-example [options]
  -v, --version    Display version
  -h, --help       Display this help
"))))
        (begin
          (display (command-line)) (newline)))

    (display
     (drop (command-line) (1+ nopts)))
    (newline)))
(main (command-line))
