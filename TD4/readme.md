# Buffer overflow attack

## Turning off countermeasures

- Several linux based systems use address space randomization to prevent this attack by randomizing the starting addresses of the heap and the stack. this command turns it off:
```shell
$ sudo sysctl -w kernel.randomize_va_space=0
```
- Our vulnerable program is a set-UID program (meaning it can run with permissions different that the user running it), there is a countermeasure in the usual shell in bin/dash so we'll use a different shell and link it to /bin/sh:
```shell
sudo ln -sf /bin/zsh /bin/sh
```

## shellcode

after running the call_shellcode.c file, i get a shell where i can input any command. However, it's a normal shellcode with my privileges, after adding the option sudo i get a root shell.

## the attack

- we have to overwrite the return address in the stack, using the addresses of ebp and the buffer, we deduce the offset, the position where we need to put the new address that will point effectively at the shellcode. (at the nop sleds that will guide you to the shellcode)

- given a buffer size the attack is easy, however, we can do it even without knowing the exact address and only knowing a range of the buffer's size, what we'll do is place the address in that range repeatadly padded by 4's, between the initial offset and a new upper limit. That way no matter where the actual return address is, it's going to be the one pointing to the shellcode

## countermeasures

### dash countermeasure

-  The dash program, as well as bash, has implemented a security countermeasure thatprevents itself from being executed in a Set-UID process.  Basically, if they detect that they are executedin a Set-UID process, they will immediately change the effective user ID to the process’s real user ID,essentially dropping the privilege.Since  our  victim  program  is  a Set-UID program,  and  our  attack  relies  on  running /bin/sh.

- in order to defeat this countermeasure, we simply set the USER ID (setUID) in the assembly shellcode to 0, effectively rendering the shell code running with root privileges.

### Address randomization

- On 32-bit Linux machines, stacks only have 19 bits of entropy, which means the stack base address can have 219=524,288 possibilities. This number is not that high and can be exhausted easily with the brute-force approach. 
- through the script provided, we run the ./stack-L1 in an infinite loop, until it eventually find the address corresponding to the one, we specified.

### Stackguard protection 

- upon changing the flag to noexecstack, i get the following error:
```bash
Input size: 517
*** stack smashing detected ***: terminated
Aborted
```
#### ***Explanation***
- **Canary Insertion**: StackGuard places a "canary" value on the stack right before the return address.
  
- **Function of Canary**: The canary serves as a sentinel to detect unauthorized overwrites. It's a unique value set when a function is entered and checked when the function exits.

- **Overflow Detection**: If a buffer overflow occurs, the canary value is likely to be overwritten. Before the function returns, StackGuard verifies if the canary remains unchanged.

- **Termination**: If the canary is altered, StackGuard triggers a termination sequence, thereby preventing the exploit.

This mechanism makes it difficult for an attacker to exploit buffer overflows to overwrite the return address, adding a layer of security against such attacks.

### Non executable stack

- **What Is It**: An executable stack allows code to be run directly from the stack memory region.

- **Compilation Flag**: Compiled with the `-z execstack` option, making the stack segment executable. 

- **Security Implications**: This is risky as it makes it easier for attackers to execute arbitrary code through stack-based buffer overflows.

- **Shellcode Execution**: In the context of exploits, an executable stack allows injected shellcode to run, leading to potential system compromise.

- **Segmentation Fault**: Without an executable stack, any attempt to execute code from the stack results in a segmentation fault, serving as a basic security measure.

Enabling an executable stack simplifies the exploit process for attackers, making it a practice generally avoided in secure systems.

**However, the non executable stack is not invincible to stack overflows, because there are other ways to run malicious code after exploiting a buffer-overflow vulnerability.  The return-to-libcattack is an example.**