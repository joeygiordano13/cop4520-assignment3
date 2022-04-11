# cop4520-assignment3

**To run code**: 
```
cargo build
cargo run
```

**Problem 1: The Birthday Presents Party**

***The Minotaur’s birthday party was a success. The Minotaur received a lot of presents from his guests. The next day he decided to sort all of his presents and start writing “Thank you” cards. Every present had a tag with a unique number that was associated with the guest who gave it.***

`From this we know we will need a linked list structure of some kind, with an ID for each node (present) in the list. We must be able to sort/move the nodes in this list.`

***Initially all of the presents were thrown into a large bag with no particular order.***

```Given an unordered set of presents (IDs).```

***The Minotaur wanted to take the presents from this unordered bag and create a chain of presents hooked to each other with special links (similar to storing elements in a linked-list). In this chain (linked-list) all of the presents had to be ordered according to their tag numbers in increasing order.***

```Increasing order sorting of presents in linked list.```

***The Minotaur asked 4 of his servants to help him with creating the chain of presents and writing the cards to his guests. Each servant would do one of three actions in no particular order:***

```We have 4 threads (servants) working on the same set of tasks, and there are 3 tasks that don't have any particular ordering.```

***Take a present from the unordered bag and add it to the chain in the correct location by hooking it to the predecessor’s link. The servant also had to make sure that the newly added present is also linked with the next present in the chain.***

**Task 1: Add a New Present**

```We will need a lock to make sure that only one servant/thread can access the unordered set (bag) at a time.```

```We must ensure that once a thread has an ID, they remove the item from the unordered set, they create a node from it, and correctly place it in the linked list by hooking it up to the predecessors link and link the new present to the following one.```

***Write a “Thank you” card to a guest and remove the present from the chain. To do so, a servant had to unlink the gift from its predecessor and make sure to connect the predecessor’s link with the next gift in the chain.***

**Task 2: Write a Card**

```Print "Thank You Guest <ID> to the console" and unlink the gift from the linked list and deal with the adjacent nodes (relink them)```

***Per the Minotaur’s request, check whether a gift with a particular tag was present in the chain or not; without adding or removing a new gift, a servant would scan through the chain and check whether a gift with a particular tag is already added to the ordered chain of gifts or not.***

**Task 3: Contains Present with Requested Tag**

```When the minotaur (main thread) asks (randomly, as with the other tasks), check if a specific tag/ID is present in the linked list, return whether it is present by printing to the console.```

***As the Minotaur was impatient to get this task done quickly, he instructed his servants not to wait until all of the presents from the unordered bag are placed in the chain of linked and ordered presents. Instead, every servant was asked to alternate adding gifts to the ordered chain and writing “Thank you” cards. The servants were asked not to stop or even take a break until the task of writing cards to all of the Minotaur’s guests was complete.***

```I'm not sure what is meant here. By "alternate" do we mean that each thread must remove a present from the set and add it to the list, followed by the task of writing a thank you card, and cycle between them unless the minotaur asks for the servants to check ContainsPresent()? Or, do we simply mean that these tasks will always occur in parallel until we have finished all of the thankyou cards (the unordered set and linked list are both empty (.empty() == true)).```

***After spending an entire day on this task the bag of unordered presents and the chain of ordered presents were both finally empty!***

***Unfortunately, the servants realized at the end of the day that they had more presents than “Thank you” notes. What could have gone wrong?***

```This could happen (I think) if we incorrectly linked the list, and lost a present before being able to write a thank you note, i.e. due to incorrect linking, or not carefully locking the linked list, we lost access or reference to (a) specific node(s).```

***Can we help the Minotaur and his servants improve their strategy for writing “Thank you” notes?***

```Design a linked list following the rules of one of the 4 methods described for concurrent linked-lists.```

1. Fine-Grained Synchronization
2. Optimistic Synchronization
3. Lazy Synchronization
4. Lock-Free Synchronization

***Design and implement a concurrent linked-list that can help the Minotaur’s 4 servants with this task. In your test, simulate this concurrent “Thank you” card writing scenario by dedicating 1 thread per servant and assuming that the Minotaur received 500,000 presents from his guests.***

```NumGifts = 500,000```
```NumServants = 4```

**Problem 2: Atmospheric Temperature Reading Module**

***You are tasked with the design of the module responsible for measuring the atmospheric temperature of the next generation Mars Rover, equipped with a multi-core CPU and 8 temperature sensors. The sensors are responsible for collecting temperature readings at regular intervals and storing them in shared memory space.***

```The module consists of 8 threads that will write to a shared memory (an array), so we will need to place a lock on the array.```

***The atmospheric temperature module has to compile a report at the end of every hour, comprising the top 5 highest temperatures recorded for that hour, the top 5 lowest temperatures recorded for that hour, and the 10-minute interval of time when the largest temperature difference was observed.***

```The loop will have a counter for every minute, and of the 8 sensors, we select the 5 highest and lowest recorded temperatures and the ten min interval with the highest the largest temperature change.```
 
**The data storage and retrieval of the shared memory region must be carefully handled, as we do not want to delay a sensor and miss the interval of time when it is supposed to conduct temperature reading.***

```So, before we move into the next interval (mins) we must ensure that all threads have done a measurement of temperature before incrementing the time.```


***Design and implement a solution using 8 threads that will offer a solution for this task. Assume that the temperature readings are taken every 1 minute. In your solution, simulate the operation of the temperature reading sensor by generating a random number from -100F to 70F at every reading. In your report, discuss the efficiency, correctness, and progress guarantee of your program.***

```Discuss the solution with respect to deadlock/starvation when it comes to the atomic step of accessing the shared memory array.```

**Resources**

- https://docs.rs/atomic-array/latest/atomic_array/
