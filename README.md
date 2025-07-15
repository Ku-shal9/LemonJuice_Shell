# Kushal Thapa

# Student | Developer | Creator of LemonJuice Shell

# 🍋 LemonJuice Shell

**LemonJuice** is a lightweight, custom-built Unix-like shell written in C. It supports both built-in commands and external program execution using `fork` and `execvp`.

---

## Features

- Built-in commands:
  - `help`/ `sahayog` — Show help menu
  - `cd` / `paribartan [dir]` — Change directory
  - `exit` / `niski` — Exit the shell
  - `ls` / `jhalak` — List directory contents
  - `date` / `samaya` — Show current system date
  - `calc` / `shusankhya` — Perform basic arithmetic (+, -, \*, /)
- External command support via `execvp`
- Dynamic input reading and token parsing
- Colored prompt displaying hostname and working directory
- Custom commands with Nepali localization (e.g., `jhalak`)

---

## Build Instructions

Make sure you have GCC and Make installed. Then, to compile the shell:

```bash
make
```

To clean up the compiled binaries (Only run if you make changes to your compiled code):
After running make clean, it will clean the -o files
Proceed running, make to compile the code again

```bash
make clean
```

After building, run:

```bash
./lemonjuice
```

You’ll see a colored prompt like:

```bash
hostname:/current/directory>
```

You can now type supported commands. For example:

```bash
cd
ls
calc 10 + 5
exit
```

# Project Structure

```
├── main.c              # Entry point with welcome prompt
├── shell.h             # Header file with constants and declarations
├── loop.c              # Handles the shell loop and prompt
├── input.c             # Reads and tokenizes user input
├── executor.c          # Executes built-in and external commands
├── Makefile            # Automates compilation
└── README.md           # Project documentation
```

# License

```
KINGS License. You are free to use, modify, and distribute this shell with attribution.
```
