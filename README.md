# Example project to demonstrate build process

## Dependencies for x86

### HIDAPI
Install hidapi library from https://github.com/signal11/hidapi/blob/master/README.txt.

Copy .pc files in [installFiles](../master/installFiles) folder to /usr/local/lib/pkgconfig/

Copy [99-hid.rules in installFiles](../master/installFiles/99-hid.rules) to /etc/udev/rules.d/


### Phidget Libraries
Install phidget library from https://www.phidgets.com/downloads/phidget22/libraries/linux/libphidget22.tar.gz

README file explains everything that is required.


## Dependencies for arm64

**There are many challenges with porting x86 code to an embedded platform.  
One area that can difficult is attaining the same library support x86 as the embedded target.  
Libraries can be attained the following ways.**

> 1. Compile natively like we do for x86, this requires all the necessary tool chain like cmake, gcc for arm.  
> 2. Cross compile on x86 machine, this also needs cross compile tool chain and cross compiled libraries.  

**For big code base it is not a good option to compile natively on the arm machine  
due to hardware limitations so we chose the second option.**  

**While cross compiling the code we have to cross compile the dependencies also.  
Cross-compiling the dependencies can be tedious and time consuming.  
One way to avoid this is to install the dependecies on AMR64 target and copied over the generated
libraries to this repository (this is what we did), you can check the libraries [here](../master/src/exynosDDS)**  

How the libraries are linked can be seen in these
> [CMakeLists.txt](../master/src/buttonExynos/src/CMakeLists.txt)  
> [CMakeLists.txt](../master/src/libblinkstick/src/CMakeLists.txt)  

**If you have any questions, please contact [Howard Butler](h.butler@samsung.com) or  
[Ragu Manjegowda](r.manjegowda@samsung.com) or [Shobhit Kukreti](shobhit.k1@samsung.com)**  

## Compile, Build and Execute

### For x86
> mkdir buildX86 && cd buildX86  
> cmake ..  
> make  
> cd bin  
> ./blinkstick  
> ./buttonpub  

### For arm64
> mkdir buildArm && cd buildArm  
> cmake -D cmake -D TARGET_ARCHITECTURE:STRING=arm ..  
> make  
> cd bin  
> ./blinkstick  
> ./buttonpub  
