(define (a-plus-abs a b)
  ((if (> b 0) + -) a b))

(display (a-plus-abs 1000 337)) (newline)
(display (a-plus-abs 1000 (- 337))) (newline)
