#include "Word.h"

#include <istream>
// void Word::MatchWord(const std::string& CheckingWord, EMatchType OutMatchReport[5])
// {
//     for (int i=0; i <5; i++)
//     {
//         if(CheckingWord[i] == _word[i])
//             OutMatchReport[i] = EMatchType::Correct;
//         else if(_word.find(CheckingWord[i]) != std::string::npos)
//             OutMatchReport[i] = EMatchType::WrongSpot;
//         else
//             OutMatchReport[i] = EMatchType::NotCorrect;
//     }
// }

std::string Word::GetWord()
{
    return _word;
}

std::ostream& operator<<(std::ostream& o, const Word& w)
{
    o << w._word;
    return o;
}
