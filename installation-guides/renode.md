# Installation

### Windows

- Install renode from here [renode](https://renode.io/tutorials/#downloads).
- Complete the installation. Make sure to add renode to PATH!
- Open PowerShell and type:
```
renode

# This should open the renode monitor window
```
- Create a new machine:
```
mach create "my-machine"
```
- All created machines and other commands can be listed by using this command:
```
mach help
```

- Load in desired CPU or BOARD. I am using the stm32f4_discovery.repl. Look in the platforms folder for your desired target.
```
machine LoadPlatformDescription @platforms/boards/stm32f4_discovery.repl
```
- You can now see if it worked and list all the "hardware" registers with this command:
```
peripherals
```
- These are the minimum requirements to start testing bootloader and firmware on the target. The following command is used to load the binary to the simulated board or CPU:
```
sysbus LoadELF @/full/path/to/your_firmware_or_bootloader.elf
```
- Start CPU:
```
start
```
- Show printf logs:
```
showAnalyzer sysbus.usart2
```