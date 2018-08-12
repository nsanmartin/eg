#!/bin/bash
:; exec emacs -Q --script "$0" -f main -- "$@" # -*- mode:lisp -*-

(defun main ()
  (let ((filename (cadr argv)))
    (send-string-to-terminal
     (with-temp-buffer
       (insert-file-contents filename)
       (goto-char (point-min))
       (sin-cmt-c)
       (goto-char (point-min))
       (sin-cmt-cpp)
       (buffer-string))))
  (kill-emacs))


(defun sin-cmt-c ()
  (let ((hasta (search-forward "*/" nil t))
        (desde (search-backward "/*" nil t)))
    (if (and desde hasta)
        (progn
          (delete-region desde hasta)
          (sin-cmt-c)))))

(defun sin-cmt-cpp ()
  (while (search-forward "//" nil t)
    (backward-char 2) 
    (kill-line )))
