## How to run

- If you want to run C++ code, you `cd cpp_code`
- You run `make` and it compiles your C++ code according to the Makefile in the directory
- If you add a new file, you need to add the file in Makefile also and run `make` again
- If you want to remove previously compiled executable, run `make clean`
- If you need to test a single function, you need to write a `main` function inside that function like for example:
  - If you want to test `lines/slope.cc`, you need to write a `main` function inside the same file
  - `cd lines`
  - `g++ slopes.cc`
  - `./main`
