(define (square x) (* x x))

(display (square 21)) (newline)
(display (square (+ 2 5))) (newline)
(display (square (square 3))) (newline)

(define (sum-of-squares x y)
  (+ (square x) (square y)))

(display (sum-of-squares 3 4)) (newline)

(define (f a) 
  (sum-of-squares (+ a 1) (* a 2)))
(display (f 5)) (newline)
