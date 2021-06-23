# Context Switch Project - core part of OS

This is an ARM CPU based context switch program, providing the basic OS feature for the resource limited embedded system.

The code at each stage is also a great resource for studying the principles of operating systems.

The source code is implemented based on the textbook as show in the image below.

The demos are consist with 4 stages:

+ The 1st stage implemented the context switch for just two hardcoded thread.

+ The 2nd stage extend the function of the context switch program to support more than two threads.

+ The 3rd stage added the root function as the entry point for users to use the OS.

+ The last stage added the feature to let the task function support argument input.

The textboot below has more advanced features introduced to the OS, such as task priority set, task preempt, etc. In the docs fold of the repository, the pdf has the detailed design of the OS implemented at each stage. However, the document is only friendly to Chinese reader.

![alt text](https://github.com/yxh1126/context-switching-demo/blob/main/docs/book_cover.jpg?raw=true)
