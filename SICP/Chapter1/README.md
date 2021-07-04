# Chapter 1 
### Building Abstractions with Procedures
- As _abstractions_ (known as _computational processes_) evolve, they manipulate other abstractions known as data.
- The rules that direct a processes evolution is known as a _program._
- Programs are composed from _programming languages._

### Programming in Lisp
- Lisp is a 'practical programming language'.
- A Lisp _interpreter_ is what carries out processes described in the Lisp language.
- Lisp stands for LISt Processing.

- Lisp uses _prefix_ notation instead of _infix_ notation:
``` 
Infix: 1 + 6
Prefix: + 1 6
```

## 1.1 The Elements of Programming
**ALL** programming languages have:
* Primitive expressions
	* Simplest entities the language is concerned with
* Means of combination
	* Compound elements built from simpler ones
* Means of abstraction
	* Compound elements can be named and manipulated as units

The two kinds of elements in programming:
* Procedures - rules for manipulating data
* Data - the 'stuff' that we want to manipulate

### 1.1.1 Expressions
An expression in Scheme is a construct that returns a value.

Primitive number expressions:
```
486			=> 486
1			=> 1
77777			=> 77777
```

Compound expressions built from numbers and primitive procedures:
```
(+ 137 349)		=> 486
(- 1000 334)		=> 666
(* 5 99)		=> 495
(/ 10 5)		=> 2
(+ 2.7 10)		=> 12.7
```

Prefix notation can accomodate procedures that take an arbitrary number of arguments:
```
(+ 21 35 12 7)		=> 75
(* 25 4 12)		=> 1200
```

Prefix notation also allows for the _nesting_ of other combinations:
```
(+ (* 3 5) (- 10 6))	=> 19
```

There is no limit to the depth of such nesting:
```
(+ (* 3 (+ (* 2 4) (+ 3 5))) (+ (- 10 7) 6))	=> 57
```

The same expression as above, but _pretty-printed_:
```
(+ (* 3
      (+ (* 2 4)
      	 (+ 3 5)))
   (+ (- 10 7)
      6))
```

The basic cycle of the interpreter is always the same. It reads an expression, evaluates the expression, and prints the result. This is also known commonly as the _read-eval-print loop._

### 1.1.2 Naming and the Environment

In the Scheme dialect of Lisp, we name things with `define`.
```
(define size 2)		=> Value: size
size			=> 2
(* 5 size)		=> 10
```

`Define` is the simplest means of abstraction as it allows us to use simple names to refer to the results of compound expressions. Complex programs are made up of building, step by step, computational objects of increasing complexity.

Associating values with symbols and retrieving them means the interpreter must have some sort of memory to keep track of name-object pairs. This memory is called the _environment_, and in the case above, the _global environment_.

### 1.1.3 Evaluating Combinations

* To evaluate a combination, do the following:
1. Evaluate the subexpressions of the combination
2. Apply the procedure that is the value of the leftmost subexpression (operator) to the arguments that are the values of the other subexpressions (the operands).

The evaluation rule above is _recursive_ in nature due to the fact that as one of its steps, it needs to invoke the rule itself.

Often times, you can visualize evaluation in terms of a tree diagram. When evaluations "percolate upwards", this process is known as _tree accumulation._

In terms of primitive cases in the tree:
* the values of numerals are the numbers that they name,
* the values of built-in operators are the machine instruction sequences that carry out the corresponding operations, and
* the values of other names are the objects associated with those names in the environment.

**Note:** `(define x 3)` is not a combination and is a _special form_ with its own evaluation rule.

### 1.1.4 Compound Procedures

Elements required in any powerful programming language:
* Numbers and arithmetic operations are primitive data and procedures.
* Nesting of combinations provies a means of combining operations.
* Definitions that associate names with values provide a limited means of abstraction.

General form of a  _procedure defenition_:
`(define (<name> <formal paramaters>) <body>)`

A procedure defenition for squaring:
`(define (square x) (* x x))`

Using `square`:
```
(square 21)				=> 441
(square (+ 2 5))			=> 49
(square (square 3))			=> 81
```

Using `square` to build other procedures:
```
(define (sum-of-squares x y)
  (+ (square x) (square y)))		=> Value: sum-of-squares

(sum-of-squares 3 4)			=> 25

(define (f a)
  (sum-of-squares (+ a 1) (* a 2)))	=> Value: f
```

Compound procedures are used exactly the same as primitive procedures.

### 1.1.5 The Substitution Model for Procedure Application

The interpreter evaluates the elements of a combination and applies the procedure (value of the operator of the combination) to the arguments (values of the operands of the combination).

For compound procedures:
* To apply a compound procedure to arguments, evaluate the body of the procedure with each formal parameter replaced by the corresponding argument.

Evaluating the combination `(f 5)` from **1.1.4** using the _substitution model_:
```
1. (f 5)
2. (sum-of-squares (+ a 1) (* a 2))		;;;Body of f
3. (sum-of-squares (+ 5 1) (* 5 2))		;;;Replacing formal paramater a with 5
4. (+ (square 6) (square 10))			;;;Body of sum-of-squares
5. (+ (* 6 6) (* 10 10))			;;;Using the definition of square
6. (+ 36 100)					;;;Reduces to multiplication
7. 136						=> 136
```

Two key points about this model:
* The purpose of the substitution is to help us think about procedure application.
* The substitution model is a simple and incomplete model.

### Applicative Order vs. Normal Order

**Applicative Order:** Evaluate the arguments and then apply

* A functions arguments are evaluated before the function is applied.
* Internal reductions are applied first. After all internal reductions are complete, the left-most redex is reduced.

**Normal Order:** Fully expand and then reduce

* A functions arguments are not evaluated before the function is applied.
* An expression is evaluated by repeatedly evaluating its leftmost outermost reducible expression.

Evaluating the combination `(f 5)` using normal order:
```
1. (f 5)
2. (sum-of-squares (+ 5 1) (* 5 2))		;;;Body of f
3. (+ (square (+ 5 1)) (square (* 5 2)))	;;;Substitute operand expressions for parameters
4. (+ (* (+ 5 1) (+ 5 1)) (* (* 5 2) (* 5 2)))	;;;Substitute operand expressions for parameters
5. (+ (* 6 6) (* 10 10))			;;;Reduction
6. (+ 36 100)					;;;Reduction
7. 136						=> 136
```

We get the same answer but the process is different. Note that the evaluations `(+ 5 1)` and `(* 5 2)` are performed twice here corresponding to the reduction of the expression `(* x x)` with `x` replaced by `(+ 5 1)` and `(* 5 2)`.

**Lisp uses applicative-order evaluation because it is more effecient due to the fact it avoids multiple evaluations of expressions as mentioned above.**

### 1.1.6 Conditional Expressions and Predicates

Taking different actions in different cases according to certain rules is called _case analysis_. In Lisp, we use the conditional expression `cond` to notate such a case analysis.

General form of a _conditional expression_:
```
(cond (<p_1> <e_1>)			;;;Clause 1
      (<p_2> <e_2>)			;;;Clause 2
      .	
      .
      (<p_n> <e_n>))			;;;Clause n
```

* Parenthesized pairs of expressions `(<p> <e>)` are called _clauses_.
* The first expression in each pair `<p>` is known as a _predicate_ and is either True or False.
* The second expression `<e>` is the corresponding _consequent expression_ of the clause.
* If 

Absolute value function:
```
(define (abs x)
  (cond ((> x 0) x)
	((= x 0) 0)
	((< x 0) (- x))))			=> Value: abs
```

Alternate:
```
(define (abs x)
  (cond ((< x 0) (- x))
  	(else x)))				=> Value: abs
```

Another alternate:
```
(define (abs x)
  (if (< x 0)
      (- x)
      x))					=> Value: abs
```

`if` is a restricted type of conditional that can be used when there are precisely two cases in a case analysis.

To construct compound predicates, we can use logical composition operations:
* `(and <e_1> ... <e_n>)`
* `(or <e_1> ... <e_n>)`
* `(not <e>)`

`and` and `or` are special forms and not procedures because the subexpressions are not necessarily all evaluated. `not` is an ordinary procedure.

A number x in the range 5 < x < 10:
```
(and (> x 5) (< x 10))
```

Greater than or equal to another:
```
(define (>= x y)
  (or (> x y) (= x y)))				=> Value: >=
```

Alternatively:
```
(define (>= x y)
  (not (< x y)))				=> Value: >=
```

### 1.1.7 Example: Square Roots by Newtons Method

* There's an important difference between mathematical functions and computer procedures.
	* Procedures must be effective.

* In mathematics, we are typically concerned with declaritive (what is) descriptions.
* In computer science, we are typically concerned with imparitive (how to) descriptions.

The most common way of computing square roots is to use Newton's method of successive approximations:

| Guess | Quotient | Average |
| --- | --- | --- |
| 1 | (2/1) = 2 | ((2 + 1)/2) = 1.5 |
| 1.5 | (2/1.5) = 1.3333 | ((1.3333 + 1.5)/2) = 1.4167 |
| 1.4167 | (2/14167) = 1.4118 | ((1.4167 + 1.4118)/2) = 1.4142 |
| 1.4142 | ... | ... |

First we start with the number whos square root we are trying to compute (the radicand) and a value for the guess. If the guess is good enough, we have our answer. If not, we repeat the process with an improved guess.

```
(define (sqrt-iter guess x)
  (if (good-enough? guess x)
      guess
      (sqrt-iter (improve guess x)
      		 x)))				=> Value: sqrt-iter
```

Improving the guess:
```
(define (improve guess x)
  (average guess (/ x guess)))			=> Value: improve

(define (average x y)
  (/ (+ x y) 2))				=> Value: average
```

Setting a tolerance that is 'good enough':
```
(define (good-enough? guess x)
  (< (abs (- (square guess) x)) 0.001))		=> Value: good-enough?
```

Guess that the square root of any number is 1:
```
(define (sqrt x)
  (sqrt-iter 1.0 x))				=> Value: sqrt
```
