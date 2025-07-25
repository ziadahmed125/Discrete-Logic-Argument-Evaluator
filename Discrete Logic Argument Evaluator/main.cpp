#include <iostream>
#include <string>

using namespace std;

// Function to get the truth value of a variable
bool getTruthValue(const char& variable, const bool& P, const bool& Q, const bool& R) {
    if (variable == 'P') return P;
    if (variable == 'Q') return Q;
    if (variable == 'R') return R;
    throw invalid_argument("Invalid variable in the expression");
}

int skipSpace(const char& c, int& i) {
    if (c == ' ') return ++i;
}

// Function to evaluate the expression
bool evaluateExpression(const string& expression, const bool& P, const bool& Q, const bool& R) {
    bool currentResult = true; // Stores the current result of evaluation
    int i = 0;

    // Check for initial '~' at the beginning
    if (expression[i] == '~') {
        i++; // Skip '~'
        skipSpace(expression[i], i);

        currentResult = !getTruthValue(expression[i], P, Q, R);
        i++; // Move to the next character;
        skipSpace(expression[i], i);
    }
    else {
        currentResult = getTruthValue(expression[i], P, Q, R);
        i++; // Move to the next character
        skipSpace(expression[i], i);
    }

    // Process the remaining expression
    while (i < expression.length()) {
        char op = expression[i]; // Current operator (&, |)
        i++; // Move to the operand
        skipSpace(expression[i], i);

        // Handle logical operators
        bool nextValue = (expression[i] == '~')
            ? (++i, skipSpace(expression[i], i), !getTruthValue(expression[i], P, Q, R)) // Skip '~' and evaluate
            : (skipSpace(expression[i], i), getTruthValue(expression[i], P, Q, R));
        i++; // Move to the next character
        skipSpace(expression[i], i);

        // Apply the operator
        if (op == '&') {
            currentResult = currentResult && nextValue;
        }
        else if (op == '|') {
            currentResult = currentResult || nextValue;
        }
    }

    return currentResult; // Return the final result
}

// Truth table generation
void generateTruthTable(const string& premise1, const string& premise2, const string& conclusion) {
    bool isValid = true; // To determine if the argument is valid
    bool isSatisfiable = false; // To determine if it's satisfiable

    // Header for the truth table
    cout << "\nTruth Table:\n";
    cout << "P | Q | R | Premise 1 | Premise 2 | Conclusion\n";
    cout << "-----------------------------------------------\n";

    for (int P = 1; P >= 0; P--) {
        for (int Q = 1; Q >= 0; Q--) {
            for (int R = 1; R >= 0; R--) {
                // Evaluate premises and conclusion
                bool p1 = evaluateExpression(premise1, P, Q, R);
                bool p2 = evaluateExpression(premise2, P, Q, R);
                bool concl = evaluateExpression(conclusion, P, Q, R);


                // Check satisfiability
                if (p1 && p2 && concl) { // Exists a critical row with T in the concl
                    isSatisfiable = true;
                }

                // Check validity
                if (p1 && p2 && !concl) { // Exists a critical row with F in the concl
                    isValid = false;
                }

                // Print the truth table row
                cout << (P ? 'T' : 'F') << " | " << (Q ? 'T' : 'F') << " | " << (R ? 'T' : 'F') << " |     "
                    << (p1 ? 'T' : 'F') << "     |     "
                    << (p2 ? 'T' : 'F') << "     |      "
                    << (concl ? 'T' : 'F') << '\n';
            }
        }
    }

    // Final output
    cout << "\nThe argument is " << (isSatisfiable ? "Satisfiable" : "not Satisfiable") << ".\n";
    cout << "The argument is " << (isValid ? "Valid" : "Falsifiable") << ".\n";
}

int main() {
    // Input instructions
    cout << "Please use variables like P, Q, R and operators like & for AND, | for OR, ~ for NOT; for the expression.\n\n";

    // Input: Logical expressions for premises and conclusion
    string premise1, premise2, conclusion;
    cout << "Enter Premise 1: "; getline(cin, premise1);
    cout << "Enter Premise 2: "; getline(cin, premise2);
    cout << "Enter Conclusion: "; getline(cin, conclusion);

    // Generate the truth table
    generateTruthTable(premise1, premise2, conclusion);

    return 0;
}