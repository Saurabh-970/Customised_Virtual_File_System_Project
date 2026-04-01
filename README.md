# 📁 Mini CVFS (Custom Virtual File System in C)

A **Custom Virtual File System (CVFS)** built in C that simulates basic file system operations like file creation, reading, writing, and deletion — all in memory.

This project helps understand **Operating System concepts** like inodes, file tables, memory management, and file handling.

---

## 🚀 Overview

Marvellous CVFS is a **command-line based virtual file system** that mimics how real file systems work internally.

- Files are stored in **memory (RAM)**, not on disk
- Uses **Inode structure** to manage files
- Supports multiple file operations through a shell interface

---

## ⚙️ Features

- 📄 Create files
- ✍️ Write data into files
- 📖 Read data from files
- ❌ Delete files
- 📂 List all files
- 📘 Help & Man page support
- 🧠 Inode & File Table management

---

## 🏗️ Architecture

The system is designed using core OS components:

- **Boot Block** → System startup info  
- **Super Block** → Tracks total & free inodes  
- **Inode List (DILB)** → Stores file metadata  
- **File Table** → Maintains opened files  
- **UAREA (User Area)** → Manages file descriptors  

---

## 🛠️ Compilation

```bash
gcc cvfs.c -o cvfs
