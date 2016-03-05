string to_postfix(string expression)
{
    int i, j, top = 0;
    char stack[LIMIT];
    char token;
    string output;
    for (i = 0; i < expression.length(); i++) {
        token = expression[i];
        if (isdigit(token)) {
            output += token;
        } else if (token == '(') {
            stack[top++] = '(';
        } else if (token == ')') {
            while (stack[top - 1] != '(') {
                output += stack[--top];
            }

            top--;
        } else if (strchr("+-*/^", token) != NULL) {
            while (precedence(token) <= precedence(stack[top - 1])) {
                output += stack[--top];
            }

            stack[top++] = token;
        }
    }

    while (top > 0) {
        output += stack[--top];
    }

    return output;
}
