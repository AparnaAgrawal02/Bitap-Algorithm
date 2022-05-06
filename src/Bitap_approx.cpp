#include "utils.h"
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

    // output final entry
    // but ONLY if id actually contains something
    // if (!id.empty())
    //     std::cout << id << " : " << text << std::endl;

    // cin >> text;
    // cin >> pattern;
    // text = argv[1];
    // pattern = argv[2];
    // cout << text << pattern;
    // if (pattern.length() == 0)
    // {
    //     return 0;
    // }
    // cout << pattern.length();

    // vector<vector<int>> pattern_bitmask(4, vector<int>(pattern.length() + 1, 0));   //0 th vector is A,1 th C,2 -G,3 -T
    int error =  atoi(argv[3]);
    //cout<<error;
    vector<unsigned long long> Table(error, ~0);
    vector<unsigned long long> OldTable(error+1, ~0);
    vector<unsigned long long> pattern_bitmask(4, ~0);
    unsigned long long deletion;
    unsigned long long insertion;
    unsigned long long substitution;
    unsigned long long match;

    std::map<char, int> link;
    link['A'] = 0;
    link['C'] = 1;
    link['G'] = 2;
    link['T'] = 3;

    // set 0 for match

    for (long long i = 0; i < pattern.length(); i++)

    {
        pattern_bitmask[link[pattern[i]]] &= ~(1 << i); // reverse
    }

    for (long long j = 0; j < text.length(); j++)
    {   
        OldTable =Table;
        Table[0] = (OldTable[0] << 1) | pattern_bitmask[link[text[j]]];
        
        for (long x = 1; x < error+1; x++)
        {
            deletion = OldTable[x- 1];           //we ovserve 0s at different places(suppos 0 is at 4th postion that means 4/5 are match at any place so deleteing a character says though you have shofted but 4/5 mathc is still there
            substitution = OldTable[x- 1] << 1; //basically we observe 0s at different places(suppos 0 is at 4th postion that means 4/5 are match)  so left shift make 4 to 5 that is a substitution will do 
                                                //since it oocurs in every loop we get substitution at any place 
            insertion = Table[x - 1] << 1;      //can insert 1 more element at any place //shifting adds a element(need all letters hence current Table)

            match = (OldTable[x] << 1) |pattern_bitmask[link[text[j]]];

            Table[x] = deletion & substitution & insertion & match;
            //cout<<R[x];
        }

        if (0 == ((Table[error] >> (pattern.length())) & 1)) // this means whole pattern is there at j-m+2 pos
            cout << "{" << j - pattern.length() + 2 << "}";
        //cout << "[" <<j<< R[error] << "]";
    }

    return 0;
}