#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#define WORDS_FILE "positive-words.txt"
#define DEFAULT_VAL -1
#define FALSE 0
#define TRUE 1

string textShorteneder(string inputText);
vector<string> stringSplitter(string text, char splitter);
int isFirstDateNewer(string date1, string date2);

// main funcs
string show_day(vector<string> memmories, vector<string> dates, string date);
int show_the_longest_day(vector<string> memmories, vector<string> dates);
int show_the_best_day(vector<string> memmories, vector<string> dates);

int main()
{
    // base lists
    vector<string> memmories;
    vector<string> dates;

    string line, command, inputedDate;
    int vectorsIndex = DEFAULT_VAL, i;

    // recieve first word of every line until user presses ^D
    while (getline(cin, line))
    {
        command = stringSplitter(line, ' ')[0];
        if (command == "start_day")
        {
            inputedDate = stringSplitter(line, ' ')[1];
            // Go through dates vector to reach a date older than the input date
            for (i = 0; i < dates.size() && isFirstDateNewer(dates[i], inputedDate); i++)
            {
                ;
            }
            vectorsIndex = i;

            // Insert date in found location of dates memmory(passed argument is date)
            dates.insert(dates.begin() + vectorsIndex, inputedDate);

            // allocate memmory in vector for next lines
            memmories.insert(memmories.begin() + vectorsIndex, "");
        }
        else if (command == "show_day")
        {
            // Last argument is memmory's date
            cout << show_day(memmories, dates, stringSplitter(line, ' ')[1]);
        }
        else if (command == "show_the_longest_day")
        {
            show_the_longest_day(memmories, dates);
        }
        else if (command == "show_the_best_day")
        {
            show_the_best_day(memmories, dates);
        }
        else // if recieved line be part of a memmory
        {
            // add new line to last memmory if start_day command entered before
            if (vectorsIndex == DEFAULT_VAL)
            {
                cout << "You should enter start_day command then write your memmory!\n";
            }
            else
            {
                memmories[vectorsIndex] += (line + "\n");
            }
        }
    }
    return 0;
}

string show_day(vector<string> memmories, vector<string> dates, string date)
{
    for (int i = 0; i < dates.size(); i++)
    {
        if (dates[i] == date)
        {
            return memmories[i];
        }
    }
    return "We couldn't find any memmory for inputed date!\n";
}
int show_the_longest_day(vector<string> memmories, vector<string> dates)
{
    int maxSize = 0;
    string longestDayMemmory, longestDaydate;
    for (int i = 0; i < memmories.size(); i++)
    {
        if (memmories[i].size() >= maxSize)
        {
            longestDaydate = dates[i];
            longestDayMemmory = memmories[i];

            maxSize = memmories[i].size();
        }
    }

    cout << longestDaydate << '\n'
         << textShorteneder(longestDayMemmory); // briefing the text if its size is more than 20

    return 0;
}
int show_the_best_day(vector<string> memmories, vector<string> dates)
{
    ifstream wordsFile(WORDS_FILE);
    vector<string> positiveWords;
    string positiveWord, bestDayMemmory, bestDayDate;
    int maxPositives = 0;

    // At first, we put all words in positive words file in a vector
    while (wordsFile >> positiveWord)
    {
        positiveWords.push_back(positiveWord);
    }

    // Cout every positive words of all memmories one by one
    for (int i = 0; i < memmories.size(); i++)
    {
        int positiveCount = 0;
        // For every positive word, we check all memmory words
        for (string positiveWord : positiveWords)
        {
            for (string word : stringSplitter(memmories[i], ' '))
            {
                if (word == positiveWord)
                {
                    positiveCount++;
                }
            }
        }

        if (positiveCount >= maxPositives)
        {
            maxPositives = positiveCount;
            bestDayDate = dates[i];
            bestDayMemmory = memmories[i];
        }
    }
    wordsFile.close();

    cout << bestDayDate << '\n'
         << textShorteneder(bestDayMemmory);

    return 0;
}

string textShorteneder(string inputText)
{
    // cut 20 first letters of string
    string result = inputText.substr(0, 20);

    // if inputed string's size is more than or equal to 20, we add ... at the end of it
    if (result.size() == 20)
    {
        result += "...";
    }

    return result + '\n';
}
vector<string> stringSplitter(string text, char splitter)
{
    string word = "";
    vector<string> words;

    for (int i = 0; i <= text.size(); i++)
    {
        // If we reach the end of the word, push word to the vector
        if (text[i] == splitter || text[i] == '\0' || text[i] == '\n')
        {
            words.push_back(word);
            word = "";
        }
        else
        {
            word += text[i];
        }
    }
    return words;
}
int isFirstDateNewer(string date1, string date2)
{
    int d1Day = stoi(stringSplitter(date1, '/')[0]);
    int d2Day = stoi(stringSplitter(date2, '/')[0]);
    int d1Month = stoi(stringSplitter(date1, '/')[1]);
    int d2Month = stoi(stringSplitter(date2, '/')[1]);
    int d1Year = stoi(stringSplitter(date1, '/')[2]);
    int d2Year = stoi(stringSplitter(date2, '/')[2]);

    if (d1Year > d2Year)
    {
        return TRUE;
    }
    else if (d1Year == d2Year)
    {
        if (d1Month > d2Month)
        {
            return TRUE;
        }
        else if (d1Month == d2Month)
        {
            if (d1Day > d2Day)
            {
                return TRUE;
            }
            else if (d1Day == d2Day)
            {
                cerr << "duplicated date! (if you write something, you can't see it with show_day command)\n";
                return -1;
            }
        }
    }
    return FALSE;
}
