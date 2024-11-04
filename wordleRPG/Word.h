#pragma once
#include <string>


class Word
{
    std::string _word;
    
public:
    Word(const std::string& MatchingWord)
    {
        _word = MatchingWord;
    }
    Word(std::istream& in)
    {
        in >> _word;
    }

    // void MatchWord(const std::string& CheckingWord, EMatchType OutMatchReport[5]);
    
    std::string GetWord();

    friend std::ostream& operator<<(std::ostream& o, const Word& w);
};
