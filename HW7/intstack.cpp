#include <iostream>
#include <string>
#include <cstring>

using namespace std;

//#define DEBUG

class intstack {
    private:
        // disallow assignments
        void operator=(const intstack &A) {};

        // disallow copying
        intstack(const intstack &A) {};

        // hidden inner class
        struct Node {
            int value;
            Node *next;
            public:
                Node();
                ~Node();
        };

        size_t size;
        Node *head;

    public:
        intstack(); // constructor
        ~intstack(); // destructor

        void push(int);
        int pop();
        void printStack(ostream &s) const;

        // true if not empty, ie. false if empty
        operator bool() const {
            return head;
        };

        inline size_t getSize() const {
            return size;
        };

};

intstack::Node::Node(){
    value = 0;
    next = nullptr;
}

intstack::Node::~Node(){
    free(next);
}

intstack::intstack() {
    size = 0;
    head = nullptr;
}

intstack::~intstack() {
    if (size != 0) {
        while (size != 0) {
            pop();
        }
    }
    free(head);
}

int intstack::pop() {
    if (!head) {
        throw "Can't pop. Stack is empty";
    }
    int value = head->value;
    Node *temp = head;
    head = head->next;
    temp->next = nullptr;
    delete(temp);
    size--;
    return value;
}

void intstack::push(int value) {
    Node *newNode = new Node();
    newNode->value = value;
    newNode->next = head;
    head = newNode;
    size++;
}

void intstack::printStack(ostream &s) const {
    Node *current = head;
    while (current) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    char* currentChar;
    int value;
    int left;
    int right;
    int newValue;
    intstack *stack = new intstack();

    try {
        for(int i = 1; i < argc; i++) {
#ifdef DEBUG_BOOL
            if(!*stack){
                clog << "Stack is empty\n";
            }
#endif
#ifdef DEBUG_ASSIGNMENTS
            intstack A, B;
            A = B;
#endif
#ifdef DEBUG_POP
            stack->pop();
#endif
            currentChar = argv[i];
            if(strlen(currentChar) == 1 && (*currentChar == '+' || *currentChar == '-' || *currentChar == '*' || *currentChar == '/' || *currentChar == '%')){
                right = stack->pop();
#ifdef DEBUG
                clog << "Right: " << right;
#endif
                left = stack->pop();
#ifdef DEBUG
                clog << " Left: " << left;
#endif

                switch (*currentChar) {
                    case '+':
                        newValue = left + right;
                        break;
                    case '-':
                        newValue = left - right;
                        break;
                    case '*':
                        newValue = left * right;
                        break;
                    case '/':
                        if(right == 0){
                            cerr << "Error: Can't divide by 0\n";
                            return 0;
                        }
                        newValue = left / right;
                        break;
                    case '%':
                        if(right == 0){
                            cerr << "Error: Can't mod by 0\n";
                            return 0;
                        }
                        newValue = left % right;
                        break;
                }
#ifdef DEBUG
                clog << " Result: " << newValue << "\n";
#endif
                stack->push(newValue);
            }
            else {
                if (currentChar[0] != '-' && !isdigit(*currentChar)) {
                    cerr << "Invalid Input: Must be an int or operator (+ - * / %)\n";
                    return 0;
                }
                value = stoi(currentChar);
#ifdef DEBUG
                clog << "Value to Push: " << value << "\n";
#endif
                stack->push(value);
            }
        }
    }
    catch (const char *error) {
        cerr << "Error: " << error << endl;
    }

    if(stack->getSize() != 1){
        cerr << "Error: Stack is empty or has more than 1 item left\n";
    }
    cout << "Stack: ";
    if(!*stack){
        cout << "empty\n";
    }
    else {
        stack->printStack(cout);
    }
    delete(stack);
    return 0;
}