bool check(string expression)
{
    int i;
    int top = 0;
    char stack[LIMIT];
    for (i = 0; i < expression.length(); i++) {
        if (expression[i] == '(') {
            stack[top++] = '(';
        } else if (expression[i] == ')') {
            cout << "top = " << top << endl;
            cout << stack[top - 1] << endl << endl;

            if (top == 0) {
                return false;
            }

            if (stack[top - 1] != '(') {
                return false;
            }

            top--; //pop()
        }
    }

    return top == 0;
}
