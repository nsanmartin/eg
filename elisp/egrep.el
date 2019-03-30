(defun get-subdirs-accessible (dirname)
  (seq-filter
   (lambda (name) (and (file-accessible-directory-p name)
                       (not (string-match "/\\.$" name))
                       (not (string-match "/\\..$" name))))
   (directory-files dirname t)))


(defun get-files-matching (dirname string)
  (seq-filter
   (lambda (name) (and (not (file-directory-p name))
                       (string-match string name)
                       (file-regular-p name)
                       (file-readable-p name)))
   (directory-files dirname t)))

(defun grep-current-buffer (string)
  (interactive "sgrep for: ")
  (pop-to-buffer
   (let ((out-buffer (generate-new-buffer
		      (format "%s %s-%s" "grep" string (buffer-name)))))
     (with-current-buffer out-buffer
       (insert (format "%s %s-%s" "grep" string (buffer-name)))
       (newline))
     (save-excursion
       (goto-char (point-min))
       (while (search-forward string nil t)
      (let ((l (format "%5s: %s"
		       (line-number-at-pos)
		       (thing-at-point 'line t))))
	(with-current-buffer out-buffer (insert l)))
      (forward-line)))
     out-buffer))
  (goto-char (point-min)))
    

;; (defun grep-file (filename string)
;;   (pop-to-buffer
;;    (let ((out-buffer (generate-new-buffer
;; 		      (format "%s %s-%s" "grep" string filename))))
;;      (grep-file-to-buffer filename string out-buffer))))


(defun grep-file-to-buffer (filename string)
  (let ((tmp-buffer (generate-new-buffer "tmp-buffer")))
    (with-temp-buffer
      (insert-file-contents filename nil nil nil t)
      (goto-char (point-min))
      (while (search-forward string nil t)
	(let ((l (format "%5s: %s"
			 (line-number-at-pos)
			 (thing-at-point 'line t))))
	  (with-current-buffer tmp-buffer (insert l)))
	(forward-line)))
    tmp-buffer))

(defun rgrep-files (files string out-buffer)
  (mapc 
   (lambda (f) (let ((b (grep-file-to-buffer f string)))
                 (if (> (buffer-size b) 0)
                     (with-current-buffer out-buffer
                       (insert f)
                       (newline)
                       (insert-buffer-substring b)))
                 (kill-buffer b)))
   files))

(defun rgrep-directory (string dirname regex out-buffer)
  (rgrep-files (get-files-matching dirname regex)  string  out-buffer)
  (mapc (lambda (d) (rgrep-directory string d regex out-buffer))
        (get-subdirs-accessible dirname))
  out-buffer)

(defun ergrep () ;; elisp recursive grep
  (interactive)
  (let ((string (read-string "Search for: "))
	(regex  (read-string "files matching: "))
	(dirname (read-file-name "in dir: ")))
    (pop-to-buffer
     (let ((out-buffer (generate-new-buffer
                        (format "%s %s %s" "grep" string dirname))))
       (with-current-buffer out-buffer ;; header of the file
         (insert (format "grep recursive \"%s\" in %s:\n\n"  string dirname)))
       (rgrep-directory string dirname regex out-buffer)
       out-buffer))
  (goto-char (point-min))))

