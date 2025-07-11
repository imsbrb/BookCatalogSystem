#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Book {
    string ISSN;
    string title;
    vector<string> authors;
    int refCopies;
    int issueCopies;
    Book* next;
    Book* prev;

    Book(string issn, string t, vector<string> auths, int ref, int issue)
        : ISSN(issn), title(t), authors(auths), refCopies(ref), issueCopies(issue),
        next(nullptr), prev(nullptr) {}
};

struct AVLNode {
    string ISSN;
    Book* bookNode;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(string issn, Book* book) : ISSN(issn), bookNode(book), left(nullptr), right(nullptr), height(1) {}
};

// Utility functions for AVL Tree
int height(AVLNode* node) {
    return node ? node->height : 0;
}

int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

AVLNode* insertAVL(AVLNode* node, string ISSN, Book* bookNode) {
    if (!node)
        return new AVLNode(ISSN, bookNode);

    if (ISSN < node->ISSN)
        node->left = insertAVL(node->left, ISSN, bookNode);
    else if (ISSN > node->ISSN)
        node->right = insertAVL(node->right, ISSN, bookNode);
    else
        return node; // Duplicate ISSNs not allowed

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && ISSN < node->left->ISSN)
        return rotateRight(node);

    if (balance < -1 && ISSN > node->right->ISSN)
        return rotateLeft(node);

    if (balance > 1 && ISSN > node->left->ISSN) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && ISSN < node->right->ISSN) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Doubly Linked List functions
Book* insertDLL(Book*& head, Book*& tail, string ISSN, string title, vector<string> authors, int ref, int issue) {
    Book* newBook = new Book(ISSN, title, authors, ref, issue);
    if (!head) {
        head = tail = newBook;
    }
    else {
        Book* current = head;
        while (current && current->ISSN < ISSN)
            current = current->next;

        if (!current) {
            tail->next = newBook;
            newBook->prev = tail;
            tail = newBook;
        }
        else {
            newBook->next = current;
            newBook->prev = current->prev;
            if (current->prev)
                current->prev->next = newBook;
            else
                head = newBook;
            current->prev = newBook;
        }
    }
    return newBook;
}

void printBook(Book* book) {
    if (!book) {
        cout << "Book not found." << endl;
        return;
    }
    cout << "ISSN: " << book->ISSN << "\nTitle: " << book->title << "\nAuthors: ";
    for (const string& author : book->authors)
        cout << author << " ";
    cout << "\nReference Copies: " << book->refCopies
        << "\nIssue Copies: " << book->issueCopies << endl;
}

// Main
int main() {
    Book* head = nullptr;
    Book* tail = nullptr;
    AVLNode* root = nullptr;

    vector<string> authors1 = { "Author A", "Author B" };
    vector<string> authors2 = { "Author X", "Author Y", "Author Z" };

    Book* book1 = insertDLL(head, tail, "1234", "Book One", authors1, 5, 3);
    Book* book2 = insertDLL(head, tail, "5678", "Book Two", authors2, 2, 1);

    root = insertAVL(root, book1->ISSN, book1);
    root = insertAVL(root, book2->ISSN, book2);

    // Review a book
    printBook(book1); // Example of review functionality

    return 0;
}
