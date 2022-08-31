#ifndef WORDTREE_H
#define WORDTREE_H

#include <iostream>
#include <string>

typedef std::string WordType;

struct WordNode
{
    WordType m_data;
    WordNode *m_left;
    WordNode *m_right;
    // You may add additional data members and a constructor
    // in WordNode

    int count;
};

class WordTree
{
private:
    WordNode *root;

    void createNode(WordType word, WordNode *&temp, int count);

    void format(WordType &word);
    void copyNodes(WordNode *&dest, WordNode *source);
    void swapTrees(WordTree &other);
    int distinctWords_help(WordNode *root) const;
    int totalWords_help(WordNode *root) const;
    void print_help(std::ostream &output, WordNode *root) const;

    void free(WordNode *root);

public:
    // default constructor
    WordTree() : root(nullptr){};

    // copy constructor
    WordTree(const WordTree &rhs);

    // assignment operator
    const WordTree &operator=(const WordTree &rhs);

    // Inserts v into the WordTree
    void add(WordType v);

    // Returns the number of distinct words / nodes
    int distinctWords() const;

    // Returns the total number of words inserted, including
    // duplicate values
    int totalWords() const;

    // Prints the WordTree
    friend std::ostream &operator<<(std::ostream &out, const WordTree &rhs);

    // Destroys all the dynamically allocated memory in the
    // tree
    ~WordTree();
};

#endif // WORDTREE_H