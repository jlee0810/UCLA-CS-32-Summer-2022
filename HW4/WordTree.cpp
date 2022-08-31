#include "WordTree.h"
#include <string>
using namespace std;

void WordTree::createNode(WordType word, WordNode *&temp, int count)
{
    temp = new WordNode;
    temp->m_data = word;
    temp->m_left = nullptr;
    temp->m_right = nullptr;
    temp->count = count;
}

void WordTree::format(WordType &word)
{
    for (int i = 0; i < word.length(); i++)
    {
        word[i] = tolower(word[i]);

        if (word[i] == '\'')
        {
            continue;
        }

        else if (word[i] == '-') {
            string first = word.substr(0, i);
            string second = word.substr(i + 1);
            word = first;
            this -> add(second);
        }

        else if (ispunct(word[i]) || isdigit(word[i]) || word[i] == ' ')
        {

            word = word.substr(0, i) + word.substr(i + 1);
            i--;
        }
    }
}

void WordTree::copyNodes(WordNode *&dest, WordNode *source)
{
    if (source == nullptr)
    {
        return;
    }
    else
    {
        createNode(source->m_data, dest, source->count);
        copyNodes(dest->m_left, source->m_left);
        copyNodes(dest->m_right, source->m_right);
    }
}

WordTree::WordTree(const WordTree &rhs)
{
    if (rhs.root == nullptr)
    {
        root = nullptr;
    }
    else
    {
        copyNodes(root, rhs.root);
    }
}

void WordTree::swapTrees(WordTree &other)
{
    WordNode *temp = other.root;
    other.root = root;
    root = temp;
}

const WordTree &WordTree::operator=(const WordTree &rhs)
{
    if (this != &rhs)
    {
        WordTree temp(rhs);
        swapTrees(temp);
    }
    return *this;
}

void WordTree::add(WordType v)
{
    format(v);
    if (root == nullptr)
    {
        createNode(v, root, 1);
        return;
    }
    WordNode *curr = root;
    for (;;)
    {
        if (curr->m_data == v)
        {
            curr->count++;
            return;
        }

        if (v < curr->m_data)
        {
            if (curr->m_left != nullptr)
            {
                curr = curr->m_left;
            }
            else
            {
                createNode(v, curr->m_left, 1);
                return;
            }
        }
        else if (v > curr->m_data)
        {
            if (curr->m_right != nullptr)
            {
                curr = curr->m_right;
            }
            else
            {
                createNode(v, curr->m_right, 1);
                return;
            }
        }
    }
}

int WordTree::distinctWords_help(WordNode *root) const
{
    if (root == nullptr)
    {
        return 0;
    }
    return (distinctWords_help(root->m_left) + 1 + distinctWords_help(root->m_right));
}

int WordTree::distinctWords() const
{
    return distinctWords_help(root);
}

int WordTree::totalWords_help(WordNode *root) const
{
    if (root == nullptr)
    {
        return 0;
    }
    return (totalWords_help(root->m_left) + root->count + totalWords_help(root->m_right));
}

int WordTree::totalWords() const
{
    return totalWords_help(root);
}

void WordTree::print_help(ostream &output, WordNode *root) const
{
    if (root == nullptr)
    {
        return;
    }
    print_help(output, root->m_left);
    output << root->m_data << " " << root->count << endl;
    print_help(output, root->m_right);
}

ostream &operator<<(std::ostream &out, const WordTree &rhs)
{
    rhs.print_help(out, rhs.root);
    return out;
}

void WordTree::free(WordNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    free(root->m_left);
    free(root->m_right);
    delete root;
}

WordTree::~WordTree()
{
    free(root);
}
