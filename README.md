# Minishell

Minishell is a minimalist command-line interpreter developed as part of the **42 School** curriculum. It aims to replicate certain functionalities of a Unix shell (such as `bash`) with a controlled and limited feature set.

---

## 🚀 Main Features

* Command input via an interactive prompt
* Execution of external commands using `fork` + `execve`
* Redirections: `>`, `>>`, `<`, `<<` (here-doc)
* Pipes (`|`) for chaining multiple commands
* Environment variable handling (`$VAR`)
* Expansion of the special variable `$?` (exit status of the last process)
* Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
* Signal management (e.g., `Ctrl-C` (SIGINT), `Ctrl-D` to exit)
* Memory management without leaks (careful handling of dynamic allocations)
* Parsing: command analysis supporting quotes, spaces, and redirections

---

## 🛠️ Installation & Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/xaviecat/minishell.git
   cd minishell
   ```

2. Compile:

   ```bash
   make
   ```

3. Launch the shell:

   ```bash
   ./minishell
   ```

The shell prompt allows entering commands such as `ls`, `echo`, `cd`, etc.

---

## ✅ Best Practices & Constraints

* Avoid memory leaks
* Do not leave file descriptors open unnecessarily
* Properly handle signals to prevent shell crashes
* Implement robust parsing: handle quotes, redirections, and pipes
* Follow the **42 Norm** (coding style, short functions, etc.)

---

## 🎯 Educational Objectives

* Understand **UNIX process management** (`fork`, `execve`, `wait`)
* Learn **stream redirection** and **pipes**
* Master system calls related to file operations
* Develop a **command-line parser** (lexer / parser)
* Manage **environment variables** and their expansion
* Efficiently handle **dynamic memory**
* Implement **built-in shell commands**
* Handle **POSIX signals**

---

## 📚 Useful Resources

* [42 Docs — Minishell](https://harm-smits.github.io/42docs/projects/minishell) — official documentation
* Tutorials on building a shell in C (lexer, parser, executor)
* POSIX references for `fork`, `pipe`, `execve`, and signal handling

---

## 👥 Authors

* **xaviecat** (Xavier CHARRA)
* **ArhKaZ** (Sylvain LUISET)
* **limastic** (Nino Faust)
