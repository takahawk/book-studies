(define (abs x)
  (cond ((> x 0) x)
        ((= x 0) 0)
        ((< x 0) (- x))))

(display (abs -1337)) (newline)
(display (abs 1337)) (newline)

(define (abs x)
  (cond ((< x 0) (- x))
        (else x)))

(display (abs -1337)) (newline)
(display (abs 1337)) (newline)

(define (abs x)
  (if (< x 0)
      (- x)
      x))

(display (abs -1337)) (newline)
(display (abs 1337)) (newline)

(define x 7)
(display (and (> x 5) (< x 10))) (newline)

(newline)
(define (>= x y) (or (> x y) (= x y)))
(display (>= 0 0)) (newline)
(display (>= 1 0)) (newline)
(display (>= 0 1)) (newline)

(newline)
(define (>= x y) (not (< x y)))
(display (>= 0 0)) (newline)
(display (>= 1 0)) (newline)
(display (>= 0 1)) (newline)
