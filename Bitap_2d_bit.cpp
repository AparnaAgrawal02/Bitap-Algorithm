#include "utils.h"
#include "Timer.h"

#define L 23011546
#define M 3147092
#define S 10037

int main(int argc, char **argv)
{
    cout << "Start";
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
    // const auto sz = pattern.length() + 2;
    // std::bitset <sz> bset[text.length() + 1];

    // vector<vector<int>> R(pattern.length() + 2, vector<int>(text.length() + 1, 0));

    cout << "Start";
    std::bitset<L> llset[L];
    std::bitset<L> lmset[M];
    std::bitset<L> lsset[S];
    std::bitset<M> mmset[M];
    std::bitset<M> msset[S];

    // cout<<pattern<<"|"<<text<< std::endl << "Matches at: ";
    // cout << R[1][51] << std::endl;
    double tm;
    auto timer = Timer();
    timer.Start();
    // #pragma omp parallel for
    for (long long i = 0; i < pattern.length() + 1; i++)
    {
        for (long long j = 0; j < text.length() + 1; j++)
        {
            if (j == 0 && i != 0)
            {
                continue;
            }

            else if (i == 0 || (llset[i - 1][j - 1] && pattern[i - 1] == text[j - 1]))
            {
                llset[i][j] = 1;
            }
            if (llset[pattern.length()][j] == 1)
            {
                cout << "{" << j - pattern.length() + 1 << "}"; // indexing start from 1 // where you find the patern
            }
            // cout << "R[" << i << "][" << j << "]" << R[i][j];
        }

        // }
        tm = timer.Stop();
        cout << std::endl
             << "Time: " << tm << std::endl;
        // cout << pattern.length() << " " << text.length() << std::endl;
    }
    return 0;
}