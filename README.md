# Philosophers
The problem says:

Dining philosopher problem
There are 5 philosophers sitting around a round table eating spaghetti and each of them has one chopstick between them. All 5 of them sit around the table and pick up the chopstick placed towards their right. But, here’s the problem. To eat the spaghetti they need both the chopsticks and since everyone picked up the chopstick to their right, nobody gets the left chopstick and hence, nobody can eat.

Logically thinking, this problem isn’t really a problem in real life scenario. The philosophers could have asked for a few extra pairs of chopsticks, or they could have eaten using their hands 😂 .

Jokes apart, but the dining philosophers problem is an excellent example to explain the concept of deadlock while resource sharing in OS.

Consider the philosophers to be processes and the chopsticks to be a shared resource. Every process needs two resources out of which one it has already acquired and the other is acquired by some other process. Till the other process does not free the resource, this process cannot proceed. Similarly, the other process is dependent on another process for its resource. Since every process is dependent on each other, it forms a circular-wait and the system goes into a deadlock condition.

Here, when each philosopher picks up the chopstick to their right, they also end up picking the left chopstick of the person sitting next to them which leaves every philosopher with just one chopstick and nobody can start eating.

To solve this problem, we can use this strategy:

Consider five philosophers: P0,P1,P2,P3,P4 &

five chopsticks: C0,C1,C2,C3,C4

Initially we let P0 enter into the dining room.

Since nobody else is present there all the chopsticks are free and P0 acquires chopsticks C0 and C1 and starts eating.


Now, P1 enters the room. Since P0 is already eating, chopstick C1 is not available for P1 and hence P1 cannot eat and is kept waiting.

PS : Since P1 does not get C1, it doesn’t claim C2.


Next, P2 enters the room. Since C2 and C3 both are available, P2 starts eating.


Next, P3 enters and is blocked and added to the waiting queue because C3 is not available.


Similarly P4 is blocked and is added to the waiting queue as C0 is not available


Now, consider P0 has finished eating and the resources claimed by it i.e. C0 and C1 are released. P1 cannot start eating since C2 is still not released and hence P4 starts eating since C4 and C0 both are released. Hence,


If now P2 releases the chopsticks C2 and C3, philosopher P1 can start eating

P3 has to stay in the waiting queue since chopstick C4 is not available.


Finally, consider that philosopher P4 has finished eating and has freed chopsticks C0 and C4, P3 can start eating.


This is the strategy using which we have ensured that all the philosophers have been served and avoided the circular wait situation.
