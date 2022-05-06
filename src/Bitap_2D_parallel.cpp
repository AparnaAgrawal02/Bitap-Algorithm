#include "utils.h"
#include "Timer.h"
int main(int argc, char **argv)
{
    std::ifstream input(argv[1]);
    if (!input.good())
    {
        std::cerr << "Error opening: " << argv[1] << " . You have failed." << std::endl;
        return -1;
    }
    std::ifstream input1(argv[2]);
    if (!input1.good())
    {
        std::cerr << "Error opening: " << argv[2] << " . You have failed." << std::endl;
        return -1;
    }
    string line, id, text, pattern;
    while (std::getline(input, line))
    {

        if (line.empty())
            continue;

        if (line[0] == '>')
        {
            // output previous line before overwriting id
            // but ONLY if id actually contains something
            if (!id.empty())
                // std::cout << id << " : " << text << std::endl;

            id = line.substr(1);
            text.clear();
        }
        else
        { //  if (line[0] != '>'){ // not needed because implicit
            text += line;
        }
    }

    while (std::getline(input1, line))
    {

        if (line.empty())
            continue;

        if (line[0] == '>')
        {
            // output previous line before overwriting id
            // but ONLY if id actually contains something
            if (!id.empty())
                // std::cout << id << " : " << DNA_sequence << std::endl;

            id = line.substr(1);
            pattern.clear();
        }
        else
        { //  if (line[0] != '>'){ // not needed because implicit
            pattern += line;
        }
    }

    vector<vector<int>> R(pattern.length() + 2, vector<int>(text.length() + 1, 0));
    // cout<<pattern<<"|"<<text<< std::endl << "Matches at: ";
    double tm;
    auto timer = Timer();

    timer.Start();
    #pragma omp parallel for
    for (long long i = 0; i < pattern.length() + 1; i++)
    {
        for (long long j = 0; j < text.length() + 1; j++)
        {
            if (j == 0 && i != 0)
            {
                continue;
            }

            else if (i == 0 || (R[i - 1][j - 1] && pattern[i - 1] == text[j - 1]))
            {
                R[i][j] = 1;
            }
            if (R[pattern.length()][j] == 1)
            {
                cout << "{" << j - pattern.length() + 1 << "}";     // indexing start from 1 // where you find the patern
            }
            //cout << "R[" << i << "][" << j << "]" << R[i][j];
        }
     
    }
    tm = timer.Stop();
    cout << std::endl << "Time: " << tm << std::endl;
    return 0;
}