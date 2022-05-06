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
    std::unordered_set<uint32_t> indexes;
    string line, id, text, pattern;//string can contain2^32 characters
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
    
    //vector<vector<int>> pattern_bitmask(4, vector<int>(pattern.length() + 1, 0));   //0 th vector is A,1 th C,2 -G,3 -T 
    unsigned long long R =0;
    vector<unsigned long long> pattern_bitmask(4,0);
    std::map<char, int>link;
    link['A'] = 0;
    link['C'] =1;
    link['G'] =2;
    link['T'] =3;
    auto timer = Timer();
    //set 1 for match
    for (long long i = 0; i < pattern.length() ; i++)
    {     pattern_bitmask[link[pattern[i]]]|= 1<< i ;  //reverse 

    }
    /* for(long long i = 0; i < 4; i++){
        cout<<pattern_bitmask[i];
    } */
    timer.Start();
    
    for (long long j = 0; j < text.length(); j++){
        R|=1;                                                   //to set 1st bit cause 0&1 ==0 and 1&1 =1 and left shift adds 0 
         R= R & pattern_bitmask[link[text[j]]];                 //ita j-1 th column shifted 1 bit and bitmask of character of jth text character
         R <<= 1;                                               //shift
        
        if (1 == (( R>> ( pattern.length())) & 1))              //this means whole pattern is there at j-m+1 pos
                indexes.insert( j - pattern.length() + 2 );
        //cout<< "["<<R<<"]";

    }
    auto time = timer.Stop();
    cout << "\n Time :" << time << std::endl;
    cout << indexes.size() << "\n";
    /* for (auto i = indexes.begin(); i != indexes.end(); ++i)
    {
        cout << *i << " ";
    } */

    return 0;
}