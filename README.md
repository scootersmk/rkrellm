# rkrellm
A console based ncurses system monitoring application that provides a
visually appealing overview of system utilization in real-time.

##Requirements
  - libstatgrab 0.17 or newer - http://www.i-scream.org/libstatgrab/
  - ncurses
  - others

This program has the potential to run on any platform that libstatgrab
is supported on, but all my development and testing has been done on
linux2.6.

## Install
  
You do not need to(and probably should not) run this program as root. To
compile this from source and install it, run the following commands:
`./configure --prefix=/path/to/install && make && make install`

If you ommit the prefix, it will likely default to /usr, and you will
need to run the `make install` as root or with sudo.

Once installed successfully, simply run the binary found in the
bin directory within the install directory: `/usr/bin/rkrellm` or
`/path/to/install/bin/rkrellm`

## Current Project Status
The code mostly works, but isn't very flexible about handing different
environments(number of disks, presence of a battery, etc). See Known
Issues section below for more details, but I hope to make this code
significantly more flexible so anyone can run it on any platform.

## History
As someone who prefers to do most of their work in a full screen
terminal screen/tmux session often remotely via SSH, including a some
users of using the ratpoison windows manager, I wanted a program to
visualize the overall system activity. I also wanted a project that I
could write from scratch so I could get some experience setting up the
automake/autoconf/etc tool chain(See AUTOHELL file). This project was
on hiatus in the depths of sourceforge for the past 5-10 years, but I
have recently put it up on gitub to share and continue to improve.

#Known Issues
  - Disk Count - the code currently expects two disks, if not it will
  either error out or crash. To workaround this, you can try one of
  the following:
    - Comment out the `disks++` line in rkrellmDisk.c, this will just
      graph the first disk twice
    - Comment out the disk graph completely, there are two differnt
      blocks in rkrellmDisplay.c
  - Battery Stats - I don't currently have machine to test this code on,
    so the code is currently commented out. I believe it was working fine
    many years ago, but no guarantees.
