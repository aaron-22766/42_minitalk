<h1 align="center">
	<p>
	minitalk
	</p>
	<img src="https://github.com/aaron-22766/aaron-22766/blob/main/42-badges/minitalkm.png">
</h1>

<p align="center">
	<b><i>Bit by bit, signals make you want to quit</i></b><br><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/aaron-22766/42_minitalk?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/aaron-22766/42_minitalk?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/aaron-22766/42_minitalk?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/aaron-22766/42_minitalk?color=green" />
</p>

---

## 🗣 About

The purpose of this project is to code a small data exchange program using UNIX signals. It is an introductory project for the bigger UNIX projects that will appear later on in the cursus.

![Play Demo](https://github.com/aaron-22766/aaron-22766/blob/main/bin/gifs/minitalk.gif)

## 🛠 Usage

### Requirements

The game is written in C language and thus needs the **`gcc` compiler** and some standard **C libraries** to run. 

### Instructions

Execute the binaries from different shells. First, start the server.
```shell
$> make
$> ./server
Server PID: 4242
```
The server will print its process id to the output. Use it as the first argument to the client and as teh second argument pass the message you want to send.
```shell
$> ./client 4242 "some_message"
```
You will see that the server will receive the message and print it to its output. Since the subject states to print the message **after** the server received it but with large messages the communication takes a lot of time, the server will store the incoming characters in a buffer and only print it once it's full or it receives a NUL-character as the indication for the end of the message.
