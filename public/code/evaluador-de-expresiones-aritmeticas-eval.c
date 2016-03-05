double eval(string expression)
{
    int i, j, top = 0;
    double a, b, c;
    double stack[LIMIT];

    for (i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            stack[top++] = (double)(expression[i] - '0');
        } else { // Operator
            b = stack[--top];
            a = stack[--top];

            switch (expression[i]) {
            case '+':
                c = a + b;
                break;
            case '-':
                c = a - b;
                break;
            case '*':
                c = a * b;
                break;
            case '/':
                c = a / b;
                break;
            case '%':
                c = (int)a % (int)b;
                break;
            case '^':
                c = pow(a, b);
                break;
            }

            stack[top++] = c;
        }
    }

    return stack[top - 1];
}
