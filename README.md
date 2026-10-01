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

`step1-1d-arrays/` and `step2-2d-arrays/` are snapshots of earlier stages and are kept only to show how the project evolved. At that point the MLP worked on plain `double` arrays and was not yet connected to the autograd engine, so these two folders are not meant to be built and run. The runnable version is in `micrograd/`.

## Build & run

```bash
cd micrograd
clang++ -std=c++14 MLP.cpp Value.cpp -o MLP
./MLP
```

Both `.cpp` files have to be compiled together, because `Value.cpp` contains the implementation of the autograd engine that `MLP.cpp` uses. Compiling only `MLP.cpp` (for example with the "Run" button of the VS Code Code Runner extension) fails with `Undefined symbols ... Value::...`.

The program trains a small MLP on 50 random inputs so that every output moves towards 10, and prints the mean squared error at each step:

```
loss: 327.919 , step: 0
loss: 283.392 , step: 1
...
loss: 7.086 , step: 499
```

Exact numbers can differ between platforms because `rand()` is implementation-defined.

## What's next

The next step, a bigram language model built on top of this engine, is in my [makemore](https://github.com/erdemKocaogluu/makemore) repository.