# Project Report -- simple shell implementation
## Jinduo Guo 918330642
## Pengcheng Cao 916835301
##  22th, Feb 2023

## Summary
This project create a library which implemented the thread function with supported 
features like semaphore and preemption. Several test cases are provided in the 
apps file to test the funcationaility of the library. Public API are listed in
the header file for better reading. 

## Develop logic
The developing process strickly follows the 4 phases provided by the syllabus.
1. Queue was implemented and the make file is created as the first version. 
2. Uthread was implemented using the queue file from step1. Make file updated.
3. Semaphore file was implemented. Make file updated.
4. Preemption file compeleted, with several modification on Uthread file and 
semaphore file to prevent race condition. Make file updated, test file added
to *app* directory
 
## Queue
The Queue part is the basic implementation of several queue API. The core design
here is the design and use of the data struct, which is node, in our code. Also
the design of our struct queue is also important, we use two pointer to
saperately represent the current head and current tail, and the size of the
whole queue is also included in this struct. After the building of the data
struct that we want to use, the next step we did is implement those useful API.
The core idea for these implementation is first to insert a node(enqueue()) to
the end of the queue, remove one node from the beginning(dequeue()), or
search&delete(delete()). The core design part here also include the part of
memory leak control. Instead of writing a saperate part to free the memory space
we allocated, we use the method of clear one node when we don't need it anymore
in our delete and dequeue API. The way we do that is to avoid possible double
free problem. Last but not least, to avoid any error caused by input error or
error of allocating any space, we also set bunch of error testing in our code,
the way we achieve that is to detect if the input is equal to NULL, and check if
the memory is actually allocated by checking if the pointer is equal to NULL.

## Queue test file
The first two tests are from the example file, which only help us test the basic
function of our implementation. Based on that consideration, we further add
several tests. First, we add the iterator tests from the instruction to test if
our iterator API works. In the function, it keeps iterating the enqueue function
to add node to a queue until all the elements in the lists are inserted. Since
the iterator tests only test iterator and enqueue, we then add another testing
function called simple2, which is another simple test but test more complicated
case that may happen when using enqueue, dequeue, or delete. We add the case of
input error, like trying to insert a NULL to the queue, or delete something from
the queue and add the value to a null pointer. Through the simple2 test, it can
make sure that our basic function is working and functional. Besides, we also
add a saperate test funciton to test the delete function, since we want to
figure out if there's any possible memory leak if we only call delete and no
dequeue. Since in our implementation, we only free memory space in dequeue or
delete, so the test that only test one of them can help us find out which
function may have possible memory leak.

## Uthread
Uthread file is implemented by first create a data structure to contain all the
information about a thread(stack pointer, context, runnig state). After the 
structure *tcb* is created to hold all information for the thread, it is also
critical to have a pointer that keep points to the main thread. In this case,
the gloabl variable main thread is introducted to keep track of the main thread
of the library that manage the whole thread library. To get this information in
other files, we set the **uthread_current** function to return the main thread
pointer. We then implement the **uthread_run** function. This fucntion acts as
a main function in ordinary file. It creates the manager thread as well with the
first thread specify by the parameter. The preempt parameter will be implemented
in phase 4 and is ignored here. To keep track of all the available thread or 
ready thread, we create a queue of threads using the queue file from phase1. We
then make the main thread and let the main thread pointer points to our main
thread. An infinite loop is set up until the *readyqueue* is empty. We then begin
the yield in the loop. This will give us the big picture of how it works. Few
other functions in this file are to be impelemented. The **uthread_yield** and 
**uthread_exit** functions shares almost the same logic. They get the next 
available thread from the *readyqueue* and make the main pointer points to the 
current main thread. However, the **uthread_yield** function will put the
previous thread back into to the *readyqueue* while **uthread_exit** will discard
the privous thread and free the space. The **uthread_create** function will
allocate space and use the *uthread_ctx_init* and *uthread_ctx_alloc_stack* to
initalize the new thread. **uthread_block** and **uthread_unblock** will be set
in phase 3 and are igonred here. 

## Semaphore -- ni lai xie 


## Preempt
Preempt file should work to interrupt the thread every 1/100 seconds. The signal
handler is set up to yield the thread when receive the virtual signal sent by 
the timer. The timer and the sigaction are set up in the **preempt_start**
function. The global variable sa will initalize an empty set every and flags.
Once the function is called, sa will change the handler to the singal handler
we wrote and stored the old handler to another global variable. Also, it will
set up a timer that keep sending virtual singal every 1/100 seconds. We use the
method from the website 
*https://www.gnu.org/software/libc/manual/2.36/html_mono/libc.html#Setting-an-Alarm*
to convert a *alarm()* to *setitmer()*. To stop the preempt, **preempt_start**
will be called. In this fucntion, the old handler is set back to the handler and
the timer is set back to normal. **preempt_disable** and **preempt_enable**
manage to mask and unmask the signal sent by the timer. To avoid race condition,
we have to modify the *uthread* file and the *sem* file. Several critical parts
are protected by disable the preemption first and enable them again once the
critical steps are over. Those critical parts include the thread creation in the
*uthread* file and the *sem-up()* and *sem_down()* function in the *sem* file.

## Preempt test file
Preempt test file set up a two thread. The first thread will simply call the
second thread at first and then yield to it. The second thread will run an 
infintie loop until the global varibal is set to 0. The global variable *cost*
is initialize to 1 and will be changed to 0 once the thread 2 is preempt and
thread 1 is entered again. When thread 1 is entered again, it means that
the preemption is sucessed. The *cost* will then be changed to 1 in thread1
and thread2 will end the loop once entered again. 



