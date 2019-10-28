(defun get-variables ()
    (loop for x being the symbols
          if (boundp x)
          collect x))
          
(defun get-functions ()
    (loop for x being the symbols
          if (fboundp x)
          collect x))

(defun get-interactive-functions ()
     (loop for x being the symbols
          if (commandp x)
          collect x))
