#include <iostream>
#include <string>

using namespace std;

// Function to guess the password
void guess_password(int n) {
    string password = "";
    for (int i = 0; i < n; ++i) {
        // Query for '0' at current position
        cout << "? " << password + "0" << endl;
        fflush(stdout);
        int response_zero;
        cin >> response_zero;

        // Query for '1' at current position
        cout << "? " << password + "1" << endl;
        fflush(stdout);
        int response_one;
        cin >> response_one;

        // Append the correct bit to the password
        if (response_zero) {
            password += "0";
        } else if (response_one) {
            password += "1";
        }
    }

    // Output the guessed password
    cout << "! " << password << endl;
    fflush(stdout);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        guess_password(n);
    }
    return 0;
}
