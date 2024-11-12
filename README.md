# Lines

`lines` is a simple command-line tool that counts the number of lines of code in a directory. This program can be compiled and set up as an alias in your terminal for quick and easy usage.

## Installation

Follow these steps to set up `lines` as a command in your terminal.

### Step 1: Clone the Repository

First, clone this repository to your local machine:

```bash
git clone https://github.com/Alexei-Ionov/lines
cd lines
```

### Step 2: Compile program
Use gcc to compile the C program:
```bash
gcc -o lines lines.c
```

### Step 3: Move executable
Move the compiled executable to a directory that’s in your system’s PATH, such as /usr/local/bin:
```bash
sudo mv lines /usr/local/bin/
```

### Step 4: Set up an alias
To make it easier to run the program, add an alias in your shell configuration file. Open either your .zshrc or .bashrc file (depending on your shell):
```bash
nano ~/.zshrc
```
Then add the following line to create an alias:

```bash
alias lines="/usr/local/bin/lines"
```
Save and close the file, then apply the changes by sourcing the configuration:

```bash
source ~/.zshrc
```

###Usage 
To use the program, simply type the alias in the desired directory 
```bash
lines
```









