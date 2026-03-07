#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cctype>
#include <sstream>

using namespace std;

// ================= TOKEN =================

enum TokenType {
    NUMBER,
    VARIABLE,
    OPERATOR,
    LPAREN,
    RPAREN
};

struct Token {
    TokenType type;
    string value;
};

// ================= TREE NODE =================

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

// ================= FUNCTION DECLARATIONS =================

vector<Token> tokenize(const string& expr);
bool isOperator(char c);
int precedence(const string& op);
vector<Token> infixToPostfix(const vector<Token>& tokens);
Node* buildTree(const vector<Token>& postfix);
double evaluate(Node* root, map<string,double>& variables);
void inputVariables(const vector<Token>& tokens, map<string,double>& variables);
void deleteTree(Node* root);
void printInorder(Node* root);

// ================= TOKENIZE =================

vector<Token> tokenize(const string& expr) {
    vector<Token> tokens;
    for (size_t i = 0; i < expr.length();) {

        if (isspace(expr[i])) {
            i++;
        }

        else if (isdigit(expr[i])) {
            string number;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                number += expr[i++];
            }
            tokens.push_back({NUMBER, number});
        }

        else if (isalpha(expr[i])) {
            string var;
            while (i < expr.length() && isalpha(expr[i])) {
                var += expr[i++];
            }
            tokens.push_back({VARIABLE, var});
        }

        else if (isOperator(expr[i])) {
            tokens.push_back({OPERATOR, string(1, expr[i])});
            i++;
        }

        else if (expr[i] == '(') {
            tokens.push_back({LPAREN, "("});
            i++;
        }

        else if (expr[i] == ')') {
            tokens.push_back({RPAREN, ")"});
            i++;
        }

        else {
            cout << "Invalid character!\n";
            exit(1);
        }
    }
    return tokens;
}

// ================= HELPERS =================

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

// ================= INFIX TO POSTFIX =================

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    stack<Token> operators;

    for (const Token& token : tokens) {

        if (token.type == NUMBER || token.type == VARIABLE) {
            output.push_back(token);
        }

        else if (token.type == OPERATOR) {
            while (!operators.empty() &&
                   operators.top().type == OPERATOR &&
                   precedence(operators.top().value) >= precedence(token.value)) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }

        else if (token.type == LPAREN) {
            operators.push(token);
        }

        else if (token.type == RPAREN) {
            while (!operators.empty() && operators.top().type != LPAREN) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.pop(); // remove '('
        }
    }

    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}

// ================= BUILD TREE =================

Node* buildTree(const vector<Token>& postfix) {
    stack<Node*> st;

    for (const Token& token : postfix) {

        if (token.type == NUMBER || token.type == VARIABLE) {
            st.push(new Node(token.value));
        }

        else if (token.type == OPERATOR) {
            Node* right = st.top(); st.pop();
            Node* left = st.top(); st.pop();

            Node* newNode = new Node(token.value);
            newNode->left = left;
            newNode->right = right;

            st.push(newNode);
        }
    }

    return st.top();
}

// ================= INPUT VARIABLES =================

void inputVariables(const vector<Token>& tokens, map<string,double>& variables) {

    for (const Token& token : tokens) {
        if (token.type == VARIABLE) {
            if (variables.find(token.value) == variables.end()) {
                cout << "Enter value for " << token.value << ": ";
                cin >> variables[token.value];
            }
        }
    }
}

// ================= EVALUATE =================

double evaluate(Node* root, map<string,double>& variables) {

    if (!root->left && !root->right) {

        if (isdigit(root->value[0]))
            return stod(root->value);
        else
            return variables[root->value];
    }

    double left = evaluate(root->left, variables);
    double right = evaluate(root->right, variables);

    if (root->value == "+") return left + right;
    if (root->value == "-") return left - right;
    if (root->value == "*") return left * right;
    if (root->value == "/") return left / right;

    return 0;
}

// ================= DELETE TREE =================

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// ================= PRINT TREE (OPTIONAL) =================

void printInorder(Node* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->value << " ";
    printInorder(root->right);
}

// ================= MAIN =================

int main() {

    string expression;

    cout << "Enter expression: ";
    getline(cin, expression);

    vector<Token> tokens = tokenize(expression);

    vector<Token> postfix = infixToPostfix(tokens);

    Node* root = buildTree(postfix);

    map<string,double> variables;

    inputVariables(tokens, variables);

    double result = evaluate(root, variables);

    cout << "\nResult: " << result << endl;

    deleteTree(root);

    return 0;
}