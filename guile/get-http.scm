#!/usr/bin/guile
!#


(use-modules ((web uri)    #:select (string->uri))
             ((web client) #:select (http-get)))

(define (foo url)
  (call-with-values
      (lambda () (http-get (string->uri url)))
    (lambda (res-headers res-body) (display res-body) (newline))))

(map foo (cdr (command-line)))

