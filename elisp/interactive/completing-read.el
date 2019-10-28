(defun foo (arg)
  (interactive
   (list
    (completing-read
     "choose: "
     '("cero" "uno" "dos" "tres" "cuatro" "cinco"
       "seis" "siete" "ocho" "nueve"))))
  (insert arg))



(defun get-interactive-functions ()
  (cl-loop for x being the symbols
          if (commandp x)
          collect x))

(defun bar (arg)
  (interactive
   (list
    (completing-read "foo: " (get-interactive-functions)))))


