#!/bin/bash
":"; exec emacs -Q  --script "$0" -f main -- "$@" # -*-emacs-lisp-*-

;; (defun main ()
;;   (mapc 'message (cdr (mapc ' filename-with-extension argv)))
;;   (kill-emacs))

(defun main ()
  (mapc 'hacer-pdf (cdr  argv))
  (kill-emacs))

(defun filename-with-extension (filename)
    (if (string-match "\\." filename)
        filename
      (format "%s.txt" filename)))

(defun hacer-pdf (filename
                  &optional async subtreep visible-only body-only ext-plist)
  (require 'ox-latex)
  (with-temp-buffer
    (insert "#+OPTIONS: toc:nil author:nil title:nil date:nil") (newline)
    (insert "#+TITLE:") (newline)
    (insert 
     "#+LaTex_CLASS_OPTIONS: [12pt]")
    (newline)
    (insert 
     "#+LaTex_HEADER: \\usepackage[margin=1cm]{geometry}")
    (newline)
    (insert "#+BEGIN_SRC") (newline)
    (insert-file-contents filename)
    (goto-char (point-max))
    (newline)
    (insert "#+END_SRC")
    (org-export-to-file
     'latex
     (concat
      "./"
      (replace-regexp-in-string "\.[^.]+$" ""
                                (filename-with-extension filename))
      ".tex")
     async subtreep visible-only body-only ext-plist
     (lambda (file) (org-latex-compile file)))))




