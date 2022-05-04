#include "utils.h"
int main()
{
    string text, pattern;
    cin >> text;
    cin >> pattern;
    if (pattern.length() == 0)
    {
        return 0;
    }
    //cout << pattern.length();
    vector<vector<int>> R(pattern.length() + 2, vector<int>(text.length() + 1, 0));

    for (long long i = 0; i < pattern.length() + 1; i++)
    {
        for (long long j = 0; j < text.length() + 1; j++)
        {
            if (j == 0 && i != 0){
                continue;
            }

            else if (i == 0 || (R[i - 1][j - 1] && pattern[i - 1] == text[j - 1]))
            {
                R[i][j] = 1;
            }
            if (R[pattern.length()][j] == 1)
            {
                cout << "{" << j - pattern.length() + 1 << "}";
            }
            //cout << "R[" << i << "][" << j << "]" << R[i][j];
        }
    }

    return 0;
}