#include <iostream>
#include <unordered_map>
#include <string.h>
#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

int displayCount = 0;
struct Trie
{

    // isEndOfWord is true if the node represents end of a word
    bool isEndOfWord;

    /* a map to child node */
    unordered_map<char, Trie *> map;

    int count;
};

/*function to make a new trie*/
Trie *getNewTrieNode()
{
    Trie *node = new Trie;
    node->isEndOfWord = false;
    return node;
}

/*function to insert in trie*/
void insert(Trie *&root, const string &str, int val)
{
    if (root == nullptr)
        root = getNewTrieNode();

    Trie *temp = root;
    for (int i = 0; i < str.length(); i++)
    {
        char x = str[i];

        /* make a new node if there is no path */
        if (temp->map.find(x) == temp->map.end())
            temp->map[x] = getNewTrieNode();

        temp = temp->map[x];
    }

    temp->isEndOfWord = true;
    temp->count=val;
}

/*function to search in trie*/
bool search(Trie *root, const string &str)
{
    /*return false if Trie is empty*/
    if (root == nullptr)
        return false;

    Trie *temp = root;
    for (int i = 0; i < str.length(); i++)
    {

        /* go to next node*/
        temp = temp->map[str[i]];

        if (temp == nullptr)
            return false;
    }
    temp->isEndOfWord ? displayCount = temp->count : 0;
    return temp->isEndOfWord;
}

/*Driver function*/
int main()
{
    string word, line, val;
    ifstream fin;
    Trie *root = nullptr;

    fin.open("EnglishDictionary.csv");

    while (!fin.eof())
    {
        fin >> line;
        stringstream s(line);
        getline(s, word, ',');
        getline(s, val);
        insert(root, word, stoi(val));
    }

    search(root, "keyboard") ? cout<<"Yes, " : cout<<"No\n";
    if(search(root, "keyboard"))
        cout<<displayCount<<"\n";
    search(root, "Rahul") ? cout << "Yes, " : cout << "No\n";
    if (search(root, "Rahul"))
        cout << displayCount;
    return 0;
}
