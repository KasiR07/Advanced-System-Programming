# Advanced System Programming 🚀

This repository contains personal projects completed. It focuses on advanced Linux system-level programming concepts such as signals, process management, file I/O, socket programming, multi-threading, shell scripting, and distributed systems.

---

## 📁 Project Structure
📦Advanced-System-Programming
┣  Shell scripting & File manipulation
┣  Signals and Process Scheduling
┣  Network & Client-Server TCP Programming
┣  Tarball creation, Archiving
┣  Distributed File System (C, sockets)
┗ 📜README.md


---

## 📌 Key Topics Covered

- Shell Scripting (`bash`)
- File I/O Operations
- Signal Handling & Process Management
- Inter-Process Communication
- TCP Client-Server Communication using Sockets
- Tarball and Archive Utilities
- Multi-threading in C
- Implementation of Distributed File System

---

## 🔧 Tech Stack

- **Languages:** C, Shell (Bash)
- **Operating System:** Linux (Ubuntu-based)
- **Tools & Utilities:** `gcc`, `make`, `tar`, `netstat`, `nc`
- **Editor:** VSCode / Vim / Nano

---

## 🖥️ Sample Projects

### ✅ Distributed File System (DFS)
A mini DFS implementation where:
- Clients can upload, download, delete, and view files.
- Servers are run independently and handle parallel file operations.
- Communication is achieved using TCP sockets and `pthread`.

### ✅ Tarball Generator
A custom script to archive modified files with versioning and file-type support using shell commands.

---

## 🔌 Getting Started

### Prerequisites
- Linux OS (WSL/VM/Native)
- GCC compiler
- Basic shell knowledge

### Running an Assignment
```bash
cd Assignment1
bash scriptname.sh  # or
gcc program.c -o output
./output


