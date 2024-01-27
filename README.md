<h1 align="center">
	<p>
	minitalk
	</p>
	<img src="https://github.com/ayogun/42-project-badges/blob/main/badges/minitalkm.png">
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

## 🛠 Usage

### Requirements

The game is written in C language and thus needs the **`gcc` compiler** and some standard **C libraries** to run. 

### Instructions

Execute the binaries on from different shells:
```shell
$> make
$> ./server
Server PID: 4242
```
Give the server pid as the first argument to the client followed by the message to send
```shell
$> ./client 4242 "some_message"
```
