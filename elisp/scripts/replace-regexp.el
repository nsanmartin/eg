#!/bin/bash
:; exec emacs -Q --script "$0" -f main -- "$@" # -*- mode:lisp -*-

(defun main ()
  (let ((filename (cadr argv))
	(str-from (cadr (cdr argv)))
	(str-to (or (cadr (cddr argv)) "")))
    (if (null str-from)
      (error "falta especificar el pattern"))
    (send-string-to-terminal
     (with-temp-buffer
       (insert-file-contents filename)
       (while (search-forward-regexp str-from nil t)
         (replace-match str-to nil t))
       (buffer-string))))
  (kill-emacs))




