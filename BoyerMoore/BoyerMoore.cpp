#include <iostream>
#define ALPHABET 256 //alphabet of symbols
using namespace std;

void stopTable(string str, int size, int lastPosition[ALPHABET]) { //function for input of stop-symbols in table
    for (int i = 0; i < ALPHABET; i++) { //for every symbol
        lastPosition[i] = -1; //enter -1 value
    }
    for (int i = 0; i < size - 1; i++) { //if a symbol from the alphabet is in the template then enter there its last
        lastPosition[(int)str[i]] = i; //position in itexcept the last symbol in the template)
    }
}

void BoyerMoore(string text, string needle) {
    int n_size = needle.size();
    int t_size = text.size();
    int numOfOccur = 0;
    int stopSymbol[ALPHABET]; //array that contains any of possible symbols in the text
    stopTable(needle, n_size, stopSymbol); //build a table of stop-symbols
    int s = 0; //current shift
    while ((t_size - s) >= n_size) { //while the template is not out of text boundaries
        int j = n_size - 1; //position where is the last symbol of template 
        while (j >= 0 && needle[j] == text[s + j]) { //begin comparison from the end
            j--;
        }
        if (j < 0) {//if the shift coincided with the text
            cout << "Needle occurs at shift = " << s << endl;
            numOfOccur++;
            if (s + n_size <= t_size) { //if the template is still not out of text boundaries
                s += n_size - stopSymbol[text[s + n_size]]; //we start new check
            } // shift the pattern so that the next character in the text is aligned with its last occurrence in the pattern
            else { //if the template goes outside the text when the first condition is met
                s += 1; //we shift it only on 1 position
            }
        }

        else { //if we met a symbol that does not match
            if (j - stopSymbol[text[s + j]] > 0) { //if the stop character heuristic is performed
                s += j - stopSymbol[text[s + j]]; //we found the most possible displacement for the step
            }
            else { //if the heuristic turned out to be negative
                s += 1; //we need to move the template only on 1 position
            }
        }
    }
    if (numOfOccur == 0) { //if no matches are found
        cout << "There are no occurences of needle" << endl;
    }
}

int main()
{
    string text = "AGACCABCAACABCCFGJFDGJDJGBC";
    string needle = "ABC";
    cout << "Text: " << text << endl;
    cout << "Needle: " << needle << endl;
    BoyerMoore(text, needle);
    return 0;
}
