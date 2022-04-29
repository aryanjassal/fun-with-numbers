# Fun with Numbers

This project is an improvement over the existing project Fun with Numbers. Note that for best performance and visual effects, it is recommended to run this application on Linux, but it also supports Windows on the cost of sacrificing unicode characters.

**NOTE: There is a known issue in rendering statistics in linux. The cause is unknown yet, however the Windows version works as expected.**

## How to build (optional)

If you really want to build this project from source, then the following steps should be followed.

### For Linux users

It is fairly straightforward for Linux users. You need to install basic C++ development tools like `gcc` and `cmake`. Then, make a `build` directory in the root of this project and create the cache using cmake. Then, compile the source code and run it. The source code should be compiled in the `bin` directory in the root of the project. Look at the following command:

```bash
cmake -B build
cd build
cmake --build .
cd ../bin
./fun_with_numbers
```

### For Windows users

This is harder to achieve. If you don't already have MSYS2 installed, then you need to get that installed first. The redistributables for Windows can be found [here](https://www.msys2.org/). After installing MSYS2, you need to prepare the environment for compilation. Update the MSYS2 installation by running the following command:

```bash
pacman -Syu
```

Then, install the required packages by running the following command:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja git
```

Then, all that is left is to clone the project by running the following command:

```bash
git clone https://github.com/AryanJassal/FunWithNumbers.git
```

Note that you need to change the branch to `better` by running `git checkout better` because the improved code is in the `better` branch.

From here on out, the process is the same as linux's process. Note you need to rebuild the cmake cache by removing and re-making the `build` directory then running the command.

## How to run

### For Windows users (note that this has only been tested in Windows 11)

To run this on Windows, simply open a terminal window and run the following command first:

```text
REG ADD HKCU\CONSOLE /f /v VirtualTerminalLevel /t REG_DWORD /d 1
```

then, close the terminal window and run `fun_with_numbers.exe` located in `bin`. It should work without any issues.

### How to run for linux users

It is very easy for linux users. Just go to the `bin` directory from the root of the project and run the executable using `./fun_with_numbers`.
