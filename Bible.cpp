#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

map<string, int> books = {
    {"Genesis", 1},
    {"Exodus", 2},
    {"Leviticus", 3},
    {"Numbers", 4},
    {"Deuteronomy", 5},
    // Add additional book names and their corresponding book number
};

int main()
{
    string bookName;
    int chapter, startVerse, endVerse;

    cout << "Enter the name of the book: ";
    cin >> bookName;

    if (books.count(bookName) == 0)
    {
        cout << "Error: invalid book name" << endl;
        return 1;
    }

    cout << "Enter the chapter number (0 for full book, -1 for full chapter): ";
    cin >> chapter;
    if (chapter >= 0)
    {
        cout << "Enter the starting verse number: ";
        cin >> startVerse;
        cout << "Enter the ending verse number (0 for full chapter): ";
        cin >> endVerse;
    }

    // Open the file for reading
    string filename = bookName + ".txt";
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: unable to open file" << endl;
        return 1;
    }

    // Read the file line by line
    string line;
    while (getline(file, line))
    {
        // Check if the line starts with the desired book, chapter, and verse
        stringstream ss(line);
        int currBook, currChapter, currVerse;
        ss >> currBook >> currChapter >> currVerse;

        if (currBook == books[bookName] && (chapter == -1 || currChapter == chapter))
        {
            if (chapter == 0 || (startVerse == 0 && endVerse == 0) || (currVerse >= startVerse && currVerse <= endVerse))
            {
                // Print the line if the book, chapter, and verse match the criteria
                cout << line << endl;
                if (endVerse > 0 && currVerse == endVerse)
                {
                    // Stop reading if the end verse has been reached
                    break;
                }
            }
        }
    }

    // Close the file
    file.close();

    return 0;
}
