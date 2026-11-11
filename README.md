*This project has been created as part of the 42 curriculum by svaladar.*

<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/minitalkm.png" alt="minitalk badge"/>
</p>

# minitalk

## Description

**minitalk** is a small data exchange program made of a **server** and a **client** that talk to each other using only two UNIX signals: `SIGUSR1` and `SIGUSR2`.

The server prints its PID and waits. The client takes that PID and a string, and sends the string to the server **one bit at a time**. The server rebuilds each byte and prints the message. The goal is to understand signals, signal handlers (`sigaction`) and process communication.

### How it works

- **Encoding**: each bit is one signal. `SIGUSR1` means `0` and `SIGUSR2` means `1`. Bits are sent from the most significant to the least significant.
- **Acknowledgement per bit**: after receiving a bit, the server answers the client with `SIGUSR1`. The client only sends the next bit after this answer. Because the client never sends faster than the server can handle, no signal is lost, even with long messages.
- **End of message**: after the last character, the client sends a null byte (`\0`, eight `0` bits). The server prints a newline and resets its state, ready for the next client. In the mandatory version it answers that last bit like any other one, and the client exits.
- **Interrupted client**: if a signal arrives from a PID that is not the current client (for example, a client was killed in the middle of a message), the server drops the unfinished byte, starts a new line and serves the new client from the start.
- **Identifying the client**: the server uses `sigaction` with `SA_SIGINFO`, which gives the sender's PID in `siginfo_t`. This is how it knows where to send the answers.

### Bonus

`make bonus` builds `server_bonus` and `client_bonus`:

- The server confirms each complete message by sending `SIGUSR2` to the client, and the client prints `Server confirmation received.`
- Unicode is supported: the message is sent byte by byte, so multi-byte UTF-8 characters arrive unchanged.

### Structure

```
.
├── include/minitalk.h
├── src/
│   ├── server.c            # mandatory server
│   ├── server_bonus.c      # bonus server: confirms each message
│   ├── server_utils.c      # shared: receives bits and rebuilds bytes
│   ├── client.c            # mandatory client
│   ├── client_bonus.c      # bonus client: prints the confirmation
│   └── client_utils.c      # shared: argument checks and bit sending
├── libft/                  # my own library (git submodule)
├── tester.sh
└── Makefile                # objects are built in obj/
```

The mandatory and bonus programs differ only in what happens at the end of a message, so each `_bonus.c` file is a small `main` and signal handler on top of the shared code.

### Error handling

The client checks the number of arguments, that the PID contains only digits, that it is greater than 0, and that the process exists (`kill(pid, 0)`), and prints a clear message for each case.

## Instructions

### Cloning

[libft](https://github.com/Soppinha/libft) is a submodule (with its own submodules), so clone recursively:

```bash
git clone --recurse-submodules https://github.com/Soppinha/MiniTalk.git
# or, in an existing clone:
git submodule update --init --recursive
```

### Compilation

```bash
make          # builds libft, server and client
make bonus    # builds server_bonus and client_bonus
make clean    # removes object files
make fclean   # removes object files and executables
make re       # rebuilds everything
```

### Usage

In one terminal, start the server:

```bash
./server
# Server PID: 12345
# Waiting for messages...
```

In another terminal, send a message:

```bash
./client 12345 "Hello, 42! 🚀"
```

The server prints `Hello, 42! 🚀`. With the bonus, the client also prints a confirmation:

```bash
./server_bonus
./client_bonus 12345 "Hello, 42! 🚀"
# Server confirmation received.
```

A test script is included:

```bash
./tester.sh
```

## Resources

- `man 2 sigaction`, `man 2 kill`, `man 2 pause`, `man 7 signal`
- [Signals – The GNU C Library](https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html)
- [Bitwise operators in C – GeeksforGeeks](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/)
- [UTF-8 – Wikipedia](https://en.wikipedia.org/wiki/UTF-8)

### AI usage

AI was used to draft this README from the existing source code. The implementation was written by the author.
