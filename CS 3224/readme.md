# Operating Systems

This is a simple operating system that we have absolutely no business using and only compiles on 12.04 so I Dockerized that shit.

There are two ways t provide to work with this:
    Option 1: Do everything in Docker.
    Option 2: Compile xv6 in Docker to take care of all the awful dependancies and run the generated images on host via QEMU (vs in QEMU in Docker)

You invoke this by running:

    Option 1: `make run-full` 

    Option 2: `make run-compile` 
