#include "node.hpp"
#include "trie.hpp"
#include "illegalargument.hpp"
#include <iostream>
#include <fstream>

int main() {
    Trie myTrie;
    std::string cmd;
    std::string addWord;
    std::ifstream fin("corpus.txt");
    jump:
    while(std::cin>>cmd) {
        if(cmd == "load") {
            while(fin>>addWord) {
                myTrie.insert(addWord, true);
            }
            std::cout<<"success"<<std::endl;
        }
        else if(cmd == "i") {
            std::cin >> addWord;
            for(int i{0}; i<addWord.size(); i++) {
                if(isupper(addWord[i]) == false){
                    try {
                        throw illegal_argument(); 
                    }
                    catch(illegal_argument it) {
                        std::cout<<it.what()<<std::endl;
                        goto jump;
                    }
                }
            }
            myTrie.insert(addWord, false);
        }
        else if(cmd == "p") {
            myTrie.printDriver();
        }
        else if(cmd == "e") {
            std::cin>>addWord;
            for(int i{0}; i<addWord.size(); i++) {
                if(isupper(addWord[i]) == false){
                    try {
                        throw illegal_argument(); 
                    }
                    catch(illegal_argument it) {
                        std::cout<<it.what()<<std::endl;
                        goto jump;
                    }
                }
            }
            myTrie.deleteDriver(addWord);
        }
        else if(cmd == "empty") {
            myTrie.checkEmpty();
        }
        else if(cmd == "size") {
            myTrie.checkNumWords();
        }
        else if(cmd == "c"){
            std::cin>>addWord;
            for(int i{0}; i<addWord.size(); i++) {
                if(isupper(addWord[i]) == false){
                    try {
                        throw illegal_argument(); 
                    }
                    catch(illegal_argument it) {
                        std::cout<<it.what()<<std::endl;
                        goto jump;
                    }
                }
            }
            myTrie.countDriver(addWord);
        }
        else if(cmd == "clear"){
            myTrie.clearDriver();
        }
        else if(cmd == "spellcheck"){
            std::cin>>addWord;
            myTrie.spellCheck(addWord);
        }
        else if(cmd == "exit") {
            return 0;
        }
    }
}