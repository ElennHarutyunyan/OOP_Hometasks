#include <iostream>
#include <stack>
#include <unordered_map>
#include <cctype>

using namespace std;

void applyTopOperator(stack<int>& numbers, stack<char>& operators) {
    int b = numbers.top(); numbers.pop();
    int a = numbers.top(); numbers.pop();
    char op = operators.top(); operators.pop();
    int result = 0;
    if(op=='*') result = a * b;
    else if(op=='/') result = a / b;
    else if(op=='+') result = a + b;
    else if(op=='-') result = a - b;
    numbers.push(result);
}

int precedence(char op) {
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;
}

int main() {
    string str;
    cout << "Enter your expression (use numbers and variables like x,y,z): ";
    cin >> str;

    // Map for variable values
    unordered_map<char,int> vars;
    cout << "Enter number of variables: ";
    int varCount; cin >> varCount;
    for(int i = 0; i < varCount; i++){
        char name; int value;
        cout << "Variable name (single char) and value: ";
        cin >> name >> value;
        vars[name] = value;
    }

    stack<int> numbers;
    stack<char> operators;

    for(int i = 0; i < str.length(); i++){
        if(isdigit(str[i])){
            int number = 0;
            while(i < str.length() && isdigit(str[i])){
                number = number * 10 + (str[i] - '0');
                i++;
            }
            i--;
            numbers.push(number);
        }
        else if(isalpha(str[i])) { 
            if(vars.find(str[i]) != vars.end())
                numbers.push(vars[str[i]]);
            else {
                cout << "Error: Undefined variable " << str[i] << endl;
                return 1;
            }
        }
        else if(str[i] == '('){
            operators.push(str[i]);
        }
        else if(str[i] == ')'){
            while(!operators.empty() && operators.top() != '('){
                applyTopOperator(numbers, operators);
            }
            if(!operators.empty() && operators.top() == '(')
                operators.pop(); // remove '('
        }
        else if(str[i]=='/' ||  str[i]=='*' ||  str[i]=='+' || str[i]=='-'){
            while(!operators.empty() && operators.top() != '(' &&
                  precedence(operators.top()) >= precedence(str[i])){
                applyTopOperator(numbers, operators);
            }
            operators.push(str[i]);
        }
    }

    while(!operators.empty()){
        applyTopOperator(numbers, operators);
    }

    cout << "Result: " << numbers.top() << endl;
    return 0;
}