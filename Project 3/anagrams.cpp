#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <string>
using namespace std;

const int MAXRESULTS = 20;      // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

////////////////////////////////////////////////////////////////////////////////////////////////////
// Function: lexiconBuilder/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
int create(istream &dictfile, string *dict, int max)
{ // Made another function so we could COPY (not pass by reference) the MAXDICTWORDS and decrement it
    if (max == 0)
    { // This means that we have reached the end of the dictionary (base case)
        return 0;
    }
    if (getline(dictfile, dict[0]))
    {                                                   // read the line from dictfile and put it as the first element of the dictionary array
        return 1 + create(dictfile, dict + 1, max - 1); // recursion - increment word count by one; we assume magic that the word other than the first word in the dictionary has been imported
    }
    return 0;
}

int lexiconBuilder(istream &dictfile, string dict[])
{
    return create(dictfile, dict, MAXDICTWORDS); // simply call the create function
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Function: theJumbler/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
int findIndex(const string &word, char target, int start) // find the index of the character in the word helper function
{
    if (start == word.length()) // if we have reached the end of the word return -1
    {
        return -1;
    }
    if (word[start] == target) // If the character is the same as the target character return the index
    {
        return start;
    }
    return findIndex(word, target, start + 1); // Move onto the next idnex of the word
}

bool isAnagram(const string &word, const string &dictWord)
{
    if (word.length() == 0 && dictWord.length() == 0) // If the length of the word inputted and dictionary word end up being 0 at the same time it is an anagram so return true
    {
        return true;
    }
    if (word.length() != dictWord.length()) // If the length of the word inputted and dictionary word doesn't match up it is not an anagram
    {
        return false;
    }
    int index = findIndex(word, dictWord[0], 0); // Find the index of the first letter of the dictionary word in the word inputted
    if (index == -1)                             // If the find index function could not find the index of the first letter of the dictionary word return false
    {
        return false;
    }
    return isAnagram(word.substr(0, index) + word.substr(index + 1), dictWord.substr(1)); // recursive function: substring the word inputted so it gets rid of the first char of the dictionary word that we verified existed
}

int goThroughDict(const string &word, const string *dict, int size, string *results, int count)
{
    if (count >= MAXRESULTS || size <= 0) // First check if the word count in results reached MAXRESULTS or the size of the dictionary is 0. If it is stop adding words into results and return count.
    {
        return count;
    }
    if (isAnagram(word, dict[0])) // If it is anagram insert word into results and increment count.
    {
        results[count] = dict[0];
        count++;
    }

    return goThroughDict(word, dict + 1, size - 1, results, count); // Recursive function go to the next element in the dictionary.
}

int theJumbler(string word, const string dict[], int size, string results[])
{
    return goThroughDict(word, dict, size, results, 0); // simply return go through dict
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Function: divulgeSolutions////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void divulgeSolutions(const string results[], int size) 
{
    if (size <= 0) // If size of results is 0 then return because we finished outputting solutions
    {
        return;
    }
    cout << "Matching word " << results[0] << endl; // Print the word in results
    divulgeSolutions(results + 1, size - 1);        // recursive function: go to the next element in the results array
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Function: main////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    return 0;
}