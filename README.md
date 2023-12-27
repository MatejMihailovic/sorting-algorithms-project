# Sorting Algorithms Project
This project implements various sorting algorithms for different data types including integers, player structures, and dot structures. It provides a menu-driven interface for users to perform sorting operations on specific data sets.

## Table of Contents
* Introduction
* Features
* Setup
* Usage
* File Structure
  
## Introduction
This program serves as a demonstration of sorting algorithms applied to different data structures. It includes implementations for insertion sort, heap sort, counting sort, quick sort, and selection sort.

## Features
* Sorting of integer arrays using insertion sort.
* Sorting of player structures based on height using heap sort and counting sort.
* Sorting of dot structures based on coordinates using quick sort and selection sort.

## Setup
1. Clone the repository:
```
git clone https://github.com/MatejMihailovic/sorting-algorithms-project.git
```
2. Compile the source files using a C compiler like GCC:
```
gcc main.c -o sorting_program
```

## Usage
* Run the compiled program:
```
./sorting_program
```
File Structure
main.c: Contains the main code for the sorting algorithms and user interface.
players.txt: Input file containing player information in the format: <First Name> <Last Name> <Height>.
dots.txt: Input file containing dot coordinates in the format: <X Coordinate> <Y Coordinate>.
