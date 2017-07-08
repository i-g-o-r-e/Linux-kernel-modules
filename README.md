# Linux-kernel-modules
Igore's modules playground

These are some experiments I am doing for learning about Linux Kernel modules. 
Don't try these out, if you care about your system ;)

## Build Instructions

```shell
$ cd src
$ make
``` 
## Testing the module
**WARNING** 
The module has full access to the kernel and might crash your system. Try it at
your own risk!

### Loading module
```shell
$sudo insmod igore.ko
```

You can see the output on dmesg:
```shell
$ dmesg | tail
[13224.999110] Loading Igore Module.                                                                                                                                         
[13224.999117] /proc/igore created
```

### Module output
```shell
$ cat /proc/igore                                                                                                           
Hi!                                                                                                                                                                          
Go cat yourself!                                                                                                                                                             
Mem Total: 8107324 KiB                                                                                                                                                       
Free RAM : 200684 KiB                                                                                                                                                        
Page size: 4096 bytes 

```

### Unloading module
```shell
$ sudo rmmod igore
```
Dmesg Output:
```shell
$ dmesg | tail
[13287.442878] Unloading Igore Module.                                                                                                                                       
[13287.442883] Removing /proc/igore                                                                                                                                          
[13287.442889] /proc/igore removed.                                                                                                                                          
[13287.442891] Igore module unloaded.
```

