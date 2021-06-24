# Context Switch Project - Core part of the Operating System

This is an ARM CPU based context switch program which providing the basic operating system function.
It has been verified that it was working correctly on a `STM32F103` ARM processor.
The result indicates the program is a great solution for the resource limited embedded system to realize multi-tasking.

The code was presented in the form of different stages which gradually adding new features based on an initial draft implementation.
The purpose is to makes the repository an ideal resource for study the principles of operating system.
The source code was implemented based on the content in the textbook as show in the image below.

The demo is consisting of 4 stages:

+ The 1st stage implemented the context switch function for just two hardcoded tasks.

+ The 2nd stage optimizes the code structure to let it support more than two tasks.

+ The 3rd stage added the root function to switch the program from system status to OS status automatically.

+ The last stage added the feature to allow the task function to accept a single parameter as input.

The textbook below has more advanced operating system features introduced, such as task priority, task preempt, etc. which has not implemented in this project.
The `docs` folder of the repository contains a pdf file, it has the detailed explanation of the context switch program implemented at each stage in this repository.
However, the document is only friendly to Chinese reader.

Hope you can enjoy the code!

Timothy Huang

![alt text](https://github.com/yxh1126/context-switching-demo/blob/main/docs/book_cover.jpg?raw=true)
