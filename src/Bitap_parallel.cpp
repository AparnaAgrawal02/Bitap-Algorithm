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

    auto timer = Timer();
    std::unordered_set<uint32_t> indexes;

#pragma omp parallel
    // vector<vector<int>> pattern_bitmask(4, vector<int>(pattern.length() + 1, 0));   //0 th vector is A,1 th C,2 -G,3 -T
    {
        unsigned long long R;
        vector<unsigned long long> pattern_bitmask(4, ~0);
        std::map<char, int> link;
        link['A'] = 0;
        link['C'] = 1;
        link['G'] = 2;
        link['T'] = 3;
        int m = pattern.length();
        // set 0 for match

        for (long long i = 0; i < m; i++)

        {
            pattern_bitmask[link[pattern[i]]] &= ~(1 << i); // reverse
        }

        // R = 2 ^ pattern.length() - 1;

        timer.Start();

        int wordSize = 32;
        int start = 0, end = 0;

#pragma omp parallel for
        for (long long r = 0; r < (text.length() / wordSize) + 1; r += 1)
        { // cout<<r;
            R = 2 ^ m - 1;
            // cout<< text.length() / wordSize + 1;
            start = r * wordSize;
            if (r * wordSize + wordSize + m <= text.length())
            {
                end = r * wordSize + wordSize + m;
            }
            else
            {
                end = text.length();
            }
            
            
            for (long long j = start; j < end; j++)
            {
                // to set 1st bit cause 0&1 ==0 and 1&1 =1 and left shift adds 0
                R = R | pattern_bitmask[link[text[j]]]; // ita j-1 th column shifted 1 bit and bitmask of character at jth index
                R <<= 1;                                // shift

                if (0 == ((R >> (m)) & 1)) // this means whole pattern is there at j-m+1 pos
#pragma omp critical
                {
                
                    indexes.insert(j - m + 1);
                }
            }
        }
    }
    auto time = timer.Stop();
    cout << "Time: " << time << " ms" << std::endl;
    cout << indexes.size() << "\n";
    /* for (auto i = indexes.begin(); i != indexes.end(); ++i)
    {
        cout << *i << " ";
    } */
    return 0;
}