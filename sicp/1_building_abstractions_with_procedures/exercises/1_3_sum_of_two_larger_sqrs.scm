(define (max a b c) 
  (if (> a b) 
      (if (> a c) 
          a
          c) 
      (if (> b c)
          b
          c)))

(define (middle a b c)
  (if (> a b)
      (if (> b c)
          b
          (if (> a c)
              c
              a))
      (if (> a c)
          a
          (if (> b c)
              c
              b))))


(middle 0111 1337 2000)
(middle 1337 0111 2000)
(middle 2000 0111 1337)
(middle 0111 2000 1337)

(define (sqr x) (* x x))

(define (sum-of-2-lrgst-sqrs a b c)
  (+ (sqr (max a b c))
     (sqr (middle a b c))))

(sum-of-2-lrgst-sqrs 2 3 4)
