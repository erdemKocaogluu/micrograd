# micrograd
From-scratch C++ implementation of micrograd, built to deeply understand backpropagation.



# How I Do It?
I first watched Andrej Karpathy's Neural Networks: Zero to Hero series on YouTube. Then, I implemented this entirely on my own, from scratch, in C++ — to make sure I truly understood backpropagation rather than just following along. With the help of this, I can truly understand how this neural network works and how to implement the math behind it.

# Challenging Part
I wrote this micrograd in c++ so I need to work with pointers and I need to be sure that I can do the memory management well, and not lead to any memory leaks.


The final version is in micrograd folder ; the two other folders show the earlier stages I went through while building it.


## Project structure

- `micrograd/` — final version (`Value.h/.cpp`, `Layer.h`, `MLP.h/.cpp`)
- `step1-1d-arrays/` — my first working version, using 1D double arrays
- `step2-2d-arrays/` — refactor to 2D double arrays

## Build & run

```bash
cd micrograd
clang++ -std=c++14 MLP.cpp Value.cpp -o MLP
./MLP
```