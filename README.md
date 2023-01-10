[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9638540&assignment_repo_type=AssignmentRepo)
# Datastructure program 4

-------------------------------------
# The comparison between Arithmetic coding and Huffman coding in C and c++

This is assignment 4

## Compile & Run

```sh
# Compile
cd src/
g++ Main.cpp arth.h arth.cpp bitstream.h bitstream.cpp huffman.h huffman.c -o Main.out -Wall

# Run for encoding
./Main.out -e Test1.txt output_arth.txt output_huff.txt
```
##Result
```sh
# Result for Test1
start Arithmetic encoding...
start Huffman encoding...
time cost of arithmetic coding: 0.000582 ms
time cost of huffman coding: 0.000269 ms
```sh
# Result for Test2
start Arithmetic encoding...
start Huffman encoding...
time cost of arithmetic coding: 0.000980 ms
time cost of huffman coding: 0.000441 ms
```sh
# Result for Test3
start Arithmetic encoding...
start Huffman encoding...
time cost of arithmetic coding: 0.006653 ms
time cost of huffman coding: 0.000197 ms
```sh
