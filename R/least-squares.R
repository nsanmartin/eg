#'    Least sqares - Cuadrados mínimos (lineales)
#'
#' David Watkins - Fundamentals of martix computation 
#'
#' Supongamo que disponemos de un conjunto de puntos (t_i, y_i), que
#' sabemos (o creemos) que hay una combinación lineal de m funciones
#' phi_1, ..., phi_m tal que:
#' 
#'     phi_1(t_i) + ... + phi_m(t_i) = y_i
#'
#' Entonces, si A es la matriz
#'     phi_1(t_1)  ...  phi_m(t_1)
#'     .
#'     .     .
#'     .           .
#'     phi_1(t_n) ... phi_m(t_n)
#'
#' Y   b^t = y_1 ... y_n
#'
#' podemos encontrar los coeficientes x = x_i ... x_n que minimizan
#'     Ax = b
#'
#' Ejemplo.
#' Sean
#' x <- sample(0:99, 10, TRUE)
#' b <- 1.1 + 2.4*x + 1.2 x^2
#'
#' Entonces para 'hayar' los coeficientes hacemos:
#'
#' A <- cbind(rep(1, length(x),
#'            x,
#'            x^2)
#' qr.solve(A,b)
#'
#' Usamos qr.solve en vez de solve porque A no es inversible.
#'
#' Otra forma de hacerlo es con:
#'
#' lm(y ~ I(x) + I(x^2))
  

