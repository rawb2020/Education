# Chapter 1 Exercises

## 1.1

**Q.** Below is a sequence of expressions. What is the result printed by the interpreter in response to each expression? Assume that the sequence is to be evaluated in the order in which it is presented.

**A.**
```
10				=> 10

(+ 5 3 4)			=> 12

(- 9 1)				=> 8

(/ 6 2)				=> 3

(+ (* 2 4) (- 4 6))		=> 6

(define a 3)			=> Value: a

(define b (+ a 1))		=> Value: b

(+ a b (* a b))			=> 19

(= a b)				=> #f

(if (and (> b a) (< b (* a b)))
	b
	a)			=> 4

(cond ((= a 4) 6)
      ((= b 4) (+ 6 7 a))
      (else 25))		=> 16

(+ 2 (if (> b a) b a))		=> 6
```

## 1.2

**Q.** Translate the following expression into prefix form

-Insert Picture Of Equation Here-

**A.**
```
(/ (+ 5 4 (- 2 (- 3 (+ 6 (/ 4 5))))) (* 3 (- 6 2) (- 2 7))
```

This can be _pretty-printed_ to resemble the original equation more closely:
```
(/ (+ 5 4 (- 2 (- 3 (+ 6 (/ 4 5)))))	;;;Numerator
   (* 3 (- 6 2) (- 2 7))		;;;Denominator
```

## 1.3

**Q.** Define a procedure that takes three numbers as arguments and returns the sum of the squares of the two larger numbers.

**A.** Here's my _Pseudo code_ for this problem:
```
- Take 3 numbers
- Square them all
- Add all the squares
- Find the smallest number
- Square it
- Minus it from the total of the three squares
```

Turning it into Scheme code:
```
(define (square x) 
	(* x x))			=> Value: square

(define (sum-three-squares x y z)
	(+ (square x) 
	   (square y) 
	   (square z)))			=> Value: sum-three-squares

(define (smallest-square x y z)
	(square (min x y z)))		=> Value: smallest-square

(define (sum-of-largest-squares x y z)
	(- (sum-three-squares x y z) 
	   (smallest-square x y z)))    => Value: sum-of-squares
```

**Note:** This isn't the most elegant (or perhaps even correct) solution but it was what I came up with on my own without looking at other solutions. I wanted to solve it without using things in the Scheme language that haven't been covered in the book yet. I did use the `min` comparison operator as it is included in most programming languages, but it would have been easy to implement regardless.

## 1.4

**Q.** Observe that our model of evaluation allows for combinations whose operators are compound expressions. Use this observation to describe the behavior of the following procedure:

```
(define (a-plus-abs-b a b)
  ((if (> b 0) + -) a b))
```

**A.** The name of the procedure pretty much explains it all but here's my best attempt at explaining it:
```
Take two parameters a and b. 
IF b is greater than 0, this condition is true and evaluates to a + b
IF b is less than 0, this condition is false and evaluates to a - (-b)
Two negatives makes a positive and evaluates to a + b.
```
So, in the case that b is positive, the expression `(if (> b 0) + -)` will evaluate to + and the result is a+b.

In all other cases, the result will be a-b.

Therefore, this function computes a + |b|. 
(As the name of the procedure suggests lol)

## 1.5

**Q.** Ben Bitdiddle has invented a test to determine whether the interpreter he is faced with is using applicative-order evaluation or normal-order evaluation. He defines the following two procedures:

```
(define (p) (p))

(define (test x y)
  (if (= x 0)
      0
      y))
```
Then he evaluates the expression
```
(test 0 (p))
```

**Q1.** What behavior will Ben observe with an interpreter that uses applicative-order evaluation?

**A1.** It's important to notice that the function `(p)` evaluates to itself. Remember that applicative-order interpreters evaluate the arguments, and then apply the function. 

Therefore, when the interpreter tries to evaluate `(test 0 (p))`, it will evaluate `0` and then it will attempt to evaluate `(p)` and _then_ apply the function `test`.

* `test` will evaluate to defined procedure.
* `0` will evaluate to the number 0.
* `(p)` evaluates to `(p)` which evaluates to `(p)` which evaluates to `(p)`, thus creating an endless loop.

**Q2.** What behavior will he observe with an interpreter that uses normal-order evaluation?

**A2.** Remember that normal-order interpreters full expand, and then reduce:

`(test 0 (p))`

will expand to:
```
if (= 0 0)
   0
   (p))
```
Since `(= 0 0)` evaluates to True or `#t`, then the result will be `0` since `(p)` does not get evaluated.

## 1.6

Alyssa P. Hacker doesn't see why `if` needs to be provided as a special form. "Why can't I just define it as an ordinary procedure in terms of `cond`?" she asks. Alyssa's friend Eva Lu Ator claims this can indeed be done, and she defines a new version of `if`:

```
(define (new-if predicate then-clause else-clause)
  (cond (predicate then-clause)
  	(else else-clause)))				=> Value: new-if
```

Eva demonstrates the program for Alyssa:

```
(new-if (= 2 3) 0 5)					=> 5

(new-if (= 1 1) 0 5)					=> 0
```

Alyssa uses `new-if` to rewrite the square-root program:

```
(define (sqrt-iter guess x)
  (new-if (good-enough? guess x)
  	  guess
	  (sqrt-iter (improve guess x)
	  	     x)))				=> Value: sqrt-iter
```

**Q.** What happens when Alyssa attempts to use this to compute square roots? Explain

**A.** Recall that the regular `if` is a special procedure that doesn't need to evaluate its arguments first. However, `new-if` is a regular procedure, and since Scheme uses applicative-order evaluation, _all_ arguments must be evaluated first.

```
(if (good-enough? guess x)
    guess
    (sqrt-iter (improve guess x)
    	       x)))
```

Using the regular `if` above, our `guess` will continually be improved until `(good-enough? guess x)` is `#t`. Once our predicate evaluates to `#t` the interpreter will return the value of `guess`.

```
(new-if (good-enough? guess x)
    guess
    (sqrt-iter (improve guess x)
    	       x)))
```

Using the `new-if` above, our `guess` will continually be improved regardless of whether `(good-enough? guess x)` is `#t` or `#f`. This is because `new-if` is a procedure and will evaluate _ALL_ parameters the moment it is called thus resulting in an endless loop.
