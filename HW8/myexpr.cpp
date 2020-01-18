#include <iostream>
#include <string>
#include <cstring>

// #define DEBUG

using namespace std;

class expr {
    public:
        expr(){}; // empty constructor
        virtual ~expr(){};
        virtual long compute() const = 0; // abstract method
};

class literal : public expr {
    const long value;
    public:
        literal(long value);
        ~literal(){};

        long compute() const; // implicitly virtual
};

literal::literal(long newValue) : value(newValue) {}

long literal::compute() const {
    return value;
}

class variable : public expr {
    long &value;
    public:
        variable(long &newVar);
        ~variable(){};

        long compute() const; // implicitly virtual
};

variable::variable(long &newVar) : value(newVar) {}

long variable::compute() const {
    return value;
}

class binary_op : public expr {
    expr* left;
    expr* right;
    char op;
    public:
        binary_op(expr* givenLeft, expr* givenRight, char givenOp);
        ~binary_op();
        long plus_op() const;
        long minus_op() const;
        long multi_op() const;
        long divide_op() const;
        long mod_op() const;

        long compute() const; // implicitly virtual
};

binary_op::binary_op(expr *givenLeft, expr *givenRight, char givenOp) {
    left = givenLeft;
    right = givenRight;
    op = givenOp;
}

binary_op::~binary_op() {
    delete(left);
    delete(right);
}

long binary_op::compute() const {
    switch(op){
        case '+':
            return plus_op();
        case '-':
            return minus_op();
        case '*':
            return multi_op();
        case '/':
            return divide_op();
        case '%':
            return mod_op();
        default:
            throw "Invalid binary_op op value\n";
    }
}

long binary_op::plus_op() const {
    return left->compute() + right->compute();
}

long binary_op::minus_op() const {
    return left->compute() - right->compute();
}

long binary_op::multi_op() const {
    return left->compute() * right->compute();
}

long binary_op::divide_op() const {
    if (right->compute() == 0){
        throw "Can't divide by 0";
    }
    return left->compute() / right->compute();
}

long binary_op::mod_op() const {
    if (right->compute() == 0){
        throw "Can't mod by 0";
    }
    return left->compute() % right->compute();
}

/* stack class to implement postfix calculator
 * More or less copied from HW7 with value changed to expr* instaed of int
 */
class exprStack {
    void operator=(const exprStack &A) {};
    exprStack(const exprStack &A) {};

    struct Node {
        expr* value;
        Node *next;
    public:
        Node();
        ~Node();
    };

    size_t size;
    Node* head;

public:
        exprStack();
        ~exprStack();

        void push(expr*);
        expr* pop();
        void printStack(ostream &s) const;

        operator bool() const {
            return head;
        }

        inline size_t getSize() const {
            return size;
        };

};

exprStack::Node::Node(){
    value = nullptr;
    next = nullptr;
}

exprStack::Node::~Node(){
    delete(next);
}

exprStack::exprStack() {
    head = nullptr;
    size = 0;
}

exprStack::~exprStack() {
    if (size != 0) {
        while (size != 0) {
            delete(pop());
        }
    }
    delete(head);
}

expr* exprStack::pop() {
    if (!head) {
        throw "Can't pop. Stack is empty";
    }
    expr* value = head->value;
    Node *temp = head;
    head = head->next;
    temp->next = nullptr;
    delete(temp);
    size--;
    return value;
}

void exprStack::push(expr* value) {
    Node *newNode = new Node();
    newNode->value = value;
    newNode->next = head;
    head = newNode;
    size++;
}

// used to debug output
void exprStack::printStack(ostream &s) const {
    Node *current = head;
    while (current) {
        cout << current->value->compute() << " ";
        current = current->next;
    }
    cout << "\n";
}


int main(int argc, char *argv[]) {
    char* currentChar;
    int min;
    int max;
    long x;
    expr* right;
    expr* left;

    exprStack* stack = new exprStack();

    binary_op* newValue;
    variable* varX;
    literal* lit;

    try {
        for(int i = 1; i < argc; i++) {
            currentChar = argv[i];
            // handle first 4 args passed through command-line
            switch (i){
                // min
                case 1:
                    if(!isdigit(*currentChar) && currentChar[0] != '-'){
#ifdef DEBUG
                        cerr << "First arg must be an integer\n";
#endif
                        return 0;
                    }
                    min = stol(currentChar);
#ifdef DEBUG
                    cerr << "Min: " << min << '\n';
#endif
                    continue;
                // separator
                case 2:
                    if(strcmp(currentChar, "..") != 0){
                        cerr << "Second arg must be `..`\n";
                        return 0;
                    }
                    continue;
                // max
                case 3:
                    if(!isdigit(*currentChar)){
                        cerr << "Third arg must be an integer\n";
                        return 0;
                    }
                    max = stol(currentChar);
#ifdef DEBUG
                    cerr << "Max: " << max << '\n';
#endif
                    if(min > max){
                        cerr << "Max (third arg) must be larger than min (first arg)\n";
                        return 0;
                    }
                    continue;
                // separator
                case 4:
                    if(strcmp(currentChar, ":") != 0){
                        cerr << "Fourth arg must be a `:`\n";
                        return 0;
                    }
                    continue;
            }
            // operand = create a binary_op object by popping left and right
            if(strlen(currentChar) == 1 && (*currentChar == '+' || *currentChar == '-' || *currentChar == '*' || *currentChar == '/' || *currentChar == '%')) {
#ifdef DEBUG
                cerr << "New Operator: " << *currentChar << "\n";
#endif
                right = stack->pop();
#ifdef DEBUG
                cerr << "Right: " << right->compute() << "\n";
#endif
                left = stack->pop();
#ifdef DEBUG
                cerr << "Left: " << left->compute() << "\n";
#endif
                newValue = new binary_op(left, right, *currentChar);
#ifdef DEBUG
                cerr << "New Binary Op: " << newValue->compute() << "\n";
#endif
                stack->push(newValue);
            }
            else {
                // handle variable x value
                if(*currentChar == 'x'){
                    varX = new variable(x);
#ifdef DEBUG
                    cerr << "New Variable: " << varX->compute() << '\n';
#endif
                    stack->push(varX);
                    continue;
                }
                // handle invalid input
                else if (currentChar[0] != '-' && !isdigit(*currentChar)) {
                    cerr << "Invalid Input: Must be an int, x, or operator (+ - * / %)\n";
                    return 0;
                }
                // defaults to creating a literal and adding to stack
                long value = stol(currentChar);
                lit = new literal(value);
#ifdef DEBUG
                cerr << "New Literal: " << lit->compute() << "\n";
#endif
                stack->push(lit);
            }
#ifdef DEBUG
            stack->printStack(cout);
#endif
        }
    }
    // error handling
    catch (const char* error){
        cerr << "Error: " << error << endl;
    }
#ifdef DEBUG
    cerr << "Final Stack: ";
    stack->printStack(cout);;
#endif
    // handle more than 1 value left in stack
    if(stack->getSize() != 1){
        cerr << "Error: Stack is empty or has more than 1 item left\n";
    }
    else {
        // print requested output replacing var x with values btw min/max range
        expr* finalExpr = stack->pop();
        for(x = min; x <= max; x++){
            cout << x << " : " << finalExpr->compute() << "\n";
        }
    }
    // tear down stack
    delete(stack);
    return 0;
}