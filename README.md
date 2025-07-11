# Book Catalog System

This C++ project implements a simple book catalog management system using:

- ✅ **Doubly Linked List** – to store books in sorted order (by ISSN)
- ✅ **AVL Tree** – to enable fast book lookup via ISSN

## 📚 Features

- Insert book details (ISSN, title, authors, copies)
- Store them in a sorted doubly linked list
- Insert book reference in an AVL tree
- Print full book details
- Maintains balance in AVL tree automatically

## 🔧 Technologies

- Language: C++
- Structures used: Doubly Linked List, AVL Tree

## 🚀 Getting Started

To compile:

```bash
g++ main.cpp -o catalog
./catalog
