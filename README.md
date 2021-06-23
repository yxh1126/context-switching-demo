# Context Switch Project - Core part of the Operating System

This is an ARM CPU based context switch program, providing the basic OS feature that optimal for the resource limited embedded system.
The code was presented in the form of each stages are also a great resource for study the principles of operating system.
The source code was implemented based on the textbook as show in the image below.

The demo is consist of 4 stages:

+ The 1st stage implemented the context switch for just two hardcoded threads.

+ The 2nd stage extended the function of the context switch program to support more than two threads.

+ The 3rd stage added the root function as the entry point for users to call the OS functions.

+ The last stage added the feature to let the task function support argument as input.

The textboot below has more advanced features introduced to the OS, such as task priority, task preempt, etc. 
The `docs` folder of the repository contains a pdf which has the detailed design of the OS implemented at each stage.
However, the document is only friendly to Chinese reader.

![alt text](https://github.com/yxh1126/context-switching-demo/blob/main/docs/book_cover.jpg?raw=true)
