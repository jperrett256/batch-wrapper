# batch-wrapper

## Motivation

I have various batch utilties included in my PATH that do work and call other programs (e.g. `cl.bat`, which sets up my environment, adds `cl.exe` to PATH and calls it). Sometimes, I want to call these utilities from other programs (e.g. GNU Make).

Unfortunately, not all programs on Windows work properly with batch files. Since they work fine with `.exe` files, this project makes it very easy to create `.exe` files that call `.bat` files of the same name.

## Building

Use `build_generic.bat` to build, using the following format:
```
build_generic.bat <target> <bat_filename>
```
The output `.exe` filename will match whatever you put for `<bat_filename>`.

I have my editor set up to run `build.bat` when I hit a hotkey, so all it does is run `build_generic.bat` with my desired arguments. That is the only reason it exists; it will likely not be of use to anyone else using this.

## Running

Just take the output executable and put it in your PATH somewhere. If called, it will call the corresponding batch file. Since the executable explicitly calls a `.bat` file, it should not call itself in an infinite loop, regardless of where you put it in PATH.

Obviously, the batch file it tries to execute should probably also be in your PATH variable.
