#include <iostream>

class Trie {
    public:
    Trie() {
        root = new Node;
        numWords=0;
    }

    ~Trie(){
        clearDriver();
        delete root;
        root = nullptr;
    }

    bool hasChildren(Node* node) {
        if(node == nullptr) {
            return false;
        }
        for(int i{0}; i<26; i++){
            if(node->getChild(i) != nullptr) {
                return true;
            }
        }
        return false;
    }

    void insert(std::string word, bool outputOff){
        Node *current = root;
        for(int i{0}; i<word.length(); i++) {
            char currentChar = word[i];
            int charNum = (int(currentChar))-65;
            if(current->getChild(charNum) == nullptr) {
                current->setChild(charNum, new Node);
                (current->getChild(charNum))->setParent(current);
            }
            current = current->getChild(charNum);
        }

        if(current->getTerminal() == true) {
            if(outputOff==false) std::cout<<"failure"<<std::endl;
        }
        else {
            current->setTerminal(true);
            numWords++;
            if(outputOff==false) std::cout<<"success"<<std::endl;
        }
    }

    void printDriver() {
        if(numWords == 0) {
            return;
        }
        std::string prefix;
        print(root, prefix, 0);
        std::cout<<std::endl;
    }

    void print(Node* node, std::string prefix, int j){
        prefix+= " ";
        if(node->getTerminal() == true){
            std::string outputString = prefix.substr(0, j);
            std::cout<<outputString<<" ";
        }
        for(int i{0}; i < 26; i++) {
            if(node->getChild(i) != nullptr) {
                prefix[j] = char(i+65);
                print(node->getChild(i), prefix, j+1);
            }
        }
    }

    void checkEmpty() {
        if(numWords > 0){
            std::cout<<"empty 0"<<std::endl;
            return;
        }
        std::cout<<"empty 1"<<std::endl;
        return;
    }

    void checkNumWords(){
        std::cout<<"number of words is "<<numWords<<std::endl;
    }

    void deleteDriver(std::string word) {
        if(numWords == 0) {
            std::cout<<"failure"<<std::endl;
            return;
        }
        Node* current = root;
        for(int i{0}; i<word.length(); i++) {
            int charNum = int(word[i]-65);
            if(current->getChild(charNum)==nullptr){
                std::cout<<"failure"<<std::endl;
                return;
            }
            current=current->getChild(charNum);
        }
        if(current->getTerminal() == false){
            std::cout<<"failure"<<std::endl;
            return;
        }
        if(hasChildren(current) == true) {
            current->setTerminal(false);
            numWords--;
            std::cout<<"success"<<std::endl;
            return;
        }
        else{
            current->setTerminal(false);
            deleteRec(current, word);
        }
    }

    void deleteRec(Node* node, std::string word) {
        Node* current = node;
        if(hasChildren(current) == true || current->getTerminal() == true || current==root) {
            numWords--;
            std::cout<<"success"<<std::endl;
            return;
        }
        Node* parent = current->getParent();
        char currentChar = word.back();
        int charNum = int(currentChar)-65;
        word.pop_back();
        delete parent->getChild(charNum);
        parent->setChild(charNum, nullptr);
        deleteRec(parent, word);
    }

    void countDriver(std::string prefix){
        Node* node = root;
        if(numWords == 0) {
            std::cout<<"not found"<<std::endl;
            return;
        }
        for(int i{0}; i<prefix.size(); i++) {
            int charNum = int(prefix[i])-65;
            if(node->getChild(charNum)==nullptr){
                std::cout<<"not found"<<std::endl;
                return;  
            }
        node = node->getChild(charNum);
        }
        count = 0;
        countRec(node);
        std::cout<<"count is "<<count<<std::endl;
    }

    void countRec(Node* node){
        for(int i{0}; i<26; i++){
            if(node->getChild(i)!=nullptr) {
                countRec(node->getChild(i));
            }
        }
        if((node->getTerminal()) == true){
            count++;
            return;
        }
    }

    void clearDriver() {
        if(numWords==0){
            std::cout<<"success"<<std::endl;
            return;
        }
        clear(root);
        numWords = 0;
        std::cout<<"success"<<std::endl;
        return;
    }

    void clear(Node* node) {
        for(int i{0}; i<26; i++) {
            if(node->getChild(i) != nullptr){
                clear(node->getChild(i));
                node->setChild(i, nullptr);
            }
        }
        if(node!=root) {
            delete node;
        }
    }

    void spellCheck(std::string word){
        Node* current = root;
        int check{0};
        std::string copy = "";
        for(int i{0}; i<word.size(); i++){
            int charNum = int(word[i])-65;
            if(current->getChild(charNum) == nullptr){
                if(current!=root){
                    std::string prefix = "";
                    spellCheckPrint(current, prefix, 0, copy);
                    std::cout<<std::endl;
                    return;
                }
                else{
                    std::cout<<std::endl;
                    return;
                }
            }
            current=current->getChild(charNum);
            copy+=word[i];
        }
        if(current->getTerminal()== true) {
            std::cout<<"correct"<<std::endl;
            return;
        }
        std::string prefix = "";
        spellCheckPrint(current, prefix, 0, word);
        std::cout<<std::endl;
        return;
    }

     void spellCheckPrint(Node* node, std::string prefix, int j, std::string extra){
        prefix+= " ";
        if(node->getTerminal() == true){
            std::string outputString = prefix.substr(0, j);
            std::cout<<extra<<outputString<<" ";
        }
        for(int i{0}; i < 26; i++) {
            if(node->getChild(i) != nullptr) {
                prefix[j] = char(i+65);
                spellCheckPrint(node->getChild(i), prefix, j+1, extra);
            }
        }
    }

    private:
    Node* root;
    int numWords;
    int count;
};