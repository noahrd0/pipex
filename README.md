# Pipex

## Table of Contents

- [Introduction](#introduction)
- [Project Description](#project-description)
- [Usage](#usage)
- [Requirements](#requirements)
- [How to Run](#how-to-run)
- [Features](#features)

## Introduction

Welcome to the "Pipex" project. This project challenges you to recreate the functionality of the shell pipe ("|") command in Unix/Linux systems using C programming.

## Project Description

In the "Pipex" project, you are tasked with implementing a program that can execute two commands connected by a pipe. This simulates the behavior of the shell pipe operator, allowing the output of the first command to serve as the input for the second command.

## Usage

You'll typically compile your program and execute it with two commands and the pipe operator ("|"), as well as input and output files, as command-line arguments.

## Requirements

- The project must be written in C.
- You are allowed to use only the following standard library functions: `open`, `close`, `read`, `write`, `malloc`, `free`, `pipe`, `fork`, `wait`, `waitpid`, `execve`, and `exit`.
- The use of other functions or libraries (e.g., `system`) is strictly forbidden.

## How to Run

To run the program, compile it and execute it with the appropriate command-line arguments. For example:

```shell
./pipex file1 cmd1 cmd2 file2
```


This will execute `cmd1 < file1 | cmd2 > file2` using your "Pipex" program.

## Features

- Executes two commands connected by a pipe.
- Handles input and output redirection.
- Efficiently manages processes using `fork` and `execve`.
- Ensures proper error handling and reporting.
