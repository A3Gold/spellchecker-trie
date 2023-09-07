class Node {
    public:
    Node() {
        for(int i{0}; i < 26; i++) {
            this->children[i] = nullptr;
        }
        this->isTerminal = false;
        this->parent = nullptr;
        }

    bool getTerminal(){
        return this->isTerminal;
    }

    void setTerminal(bool isTerminal){
        this->isTerminal = isTerminal;
    }

    Node* getChild(int i){
        return this->children[i];
    }

    void setChild(int i, Node* child){
        this->children[i] = child;
    }

     Node* getParent(){
        return this->parent;
    }

    void setParent(Node* parent){
        this->parent = parent;
    }

    private:
    Node *children[26];
    bool isTerminal;
    Node *parent;
};