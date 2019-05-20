#!/bin/bash
:; emacs -Q --script "$0" -f main -- "$@" # -*- mode:lisp -*-

(defun parseopt (opt optlist &optional arg-required)
  (let* ((found (member opt optlist))
        (optarg (cadr found)))
     (if arg-required
         (if (and found (or (null optarg) (string-prefix-p "-" optarg)))
             (error (format "error: %s has arg %s" opt optarg))
        (not (null found)))))
        
;;ej wih "ab:cd:"

(defun main ()
  (let ((a (parseopt "-a" argv))
        (b (parseopt "-b" argv t))
        (c (parseopt "-c" argv))
        (d (parseopt "-d" argv t)))
    (message (format "a: %s" a))
    (message (format "b: %s" b))
    (message (format "c: %s" c))
    (message (format "d: %s" d))))
