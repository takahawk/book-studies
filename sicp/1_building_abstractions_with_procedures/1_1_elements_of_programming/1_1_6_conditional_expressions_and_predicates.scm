(define (abs x)
  (cond ((> x 0) x)
        ((= x 0) 0)
        ((< x 0) (- x))))

(abs -1337)
(abs 1337)

(define (abs x)
  (cond ((< x 0) (- x))
        (else x)))

(abs -1337)
(abs 1337)

(define (abs x)
  (if (< x 0)
      (- x)
      x))

(abs -1337)
(abs 1337)

(define x 7)
(and (> x 5) (< x 10))

(define (>= x y) (or (> x y) (= x y)))
(>= 0 0)
(>= 1 0)
(>= 0 1)

(define (>= x y) (not (< x y)))
(>= 0 0)
(>= 1 0)
(>= 0 1)
