(define (a-plus-abs a b)
  ((if (> b 0) + -) a b))

(a-plus-abs 1000 337)
(a-plus-abs 1000 (- 337))
