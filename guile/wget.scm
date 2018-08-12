#!/usr/bin/guile
!#

(use-modules (web uri)
             (web client)
	     (web http)
             (web request))

(define (print-given-url url)
  (let ((page (http-get (string->uri url))))
    (newline)
    (map display `("el url:" ,url))
    (newline) (newline)
    (write page)
    (newline)
    page))
	      

;; (let lp ((urls (cdr (command-line))))
;;   (if (not (null? urls))
;;       (begin (print-given-url (car urls))
;; 	     (lp (cdr urls)))))

(print-given-url (cadr (command-line)))

