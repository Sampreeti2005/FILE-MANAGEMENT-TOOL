#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;

// Function to define operator precedence
int precedence(char op) {
    if(op == '+'|| op == '-') return 1;
    if(op == '*'|| op == '/') return 2;
    return 0;
}

// Apply arithmetic operation
int applyOp(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0;
        default: return 0;
    }
}

// Function to evaluate an expression string
int evaluateExpression(const string& expr) {
    stack<int> values;     // For numbers
    stack<char> ops;       // For operators

    for(int i = 0; i < expr.length(); i++) {
        // Skip spaces
        if(expr[i] == ' ')
            continue;

        // If number, push to values
        else if(isdigit(expr[i])) {
            int val = 0;
            // Handle multi-digit numbers
            while(i < expr.length() && isdigit(expr[i])) {
                val = (val*10) + (expr[i]-'0');
                i++;
            }
            values.push(val);
            i--; // adjust position
        }

        // If opening bracket
        else if(expr[i] == '(') {
            ops.push(expr[i]);
        }

        // If closing bracket
        else if(expr[i] == ')') {
            while(!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.pop(); // remove '('
        }

        // If operator
        else {
            while(!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expr[i]);
        }
    }

    // Final calculation
    while(!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression (e.g. 3 + 5 * (2 - 1)):\n";
    getline(cin, expression);

    int result = evaluateExpression(expression);

    cout << "\n Parsed and evaluated result: " << result << endl;

    return 0;
}
