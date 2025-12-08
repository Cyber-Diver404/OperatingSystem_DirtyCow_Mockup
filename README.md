# OperatingSystem_DirtyCow_Mockup
### Dirty COW Breakdown

Dirty COW is an old Linux vulnerability that allows any user that can read system binaries to write to them. This allows local code execution with root level privileges by any user. It involves a race condition where the write file command races against the madvise command to write to the real copy of the file on the disk. It is Dirty since, when writing to the file’s memory page, the page becomes dirty, causing it to be written to the disk. 

COW stands for Copy-On-Write, and is the action the kernel uses during writing. If a user tries to write to a system binary without root level permissions, a copy of that file is created in memory, and any changes are made to that copy, so as to not actually change the real file. But with the race condition, write accidentally modifies the actual memory page of the system file, marking it as dirty, and saving it to the disk.
Now when that binary is run, it will include such changes, allowing for LCE with root level permissions.

### Mock-up Race Condition Code 

The C code attached is a representation of the type of race condition that the DirtyCOW vulnerability was based on. The c file named race is the race condition version and the c file named race_fixed implements the fixed version.
In the defective version of our program, we create two threads that both increment the same shared variable, counter, one million times. Since the increments have no form of synchronization both threads attempt to read and update at the same time. Being that counter++ is not atomic, some updates are lost and the final result ends up lower than the expected value of two million. This inconsistent behavior demonstrates a race condition where the program’s output depends on the timing of the threads.

The corrected version of our programs uses a pthread_mutex_t lock to prevent both threads from modifying the shared counter at the same time. Before a thread updates the counter it locks the mutex and after its done it unlocks the mutex. This ensures that only one thread can modify the counter at any given moment. With the proper synchronization no increments are lost and the program consistently has an output of two million. This demonstrates how mutual exclusion eliminates race conditions and ensures safe access to shared memory.

### The Dangers of DirtyCOW

There is a reason why DirtyCOW is such a famous example of a critical vulnerability. The biggest reason was how prevalent the vulnerability was. This was an issue that existed in the Linux Kernel since 2007, so every linux distro was vulnerable, and unlike other vulnerabilities, the only real solution was to update to a new version, there was no patch or workaround that could be used to prevent the exploitation of this bug. This meant any machine that was running distros older than 2016 (which was when this vulnerability first made headlines) needed to be patched, and how often legacy systems exist in corporations, it led to a significant need to spread the word on this issue.

The end result of the vulnerability is an elevation of privileges on a system, which can lead to 3rd parties accessing information they aren’t allowed to, and potentially remote code execution if paired with other vulnerabilities.
Ultimately, in terms of danger, DirtyCOW is not nearly as dangerous as many other kinds of vulnerabilities, but the sheer prevalence and amount of systems impacted by it, is why it remains a keen example of the importance of good security on the OS level.
