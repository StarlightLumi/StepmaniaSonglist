// StepmaniaSonglist.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// TO GET THE SONGLIST THIS FILE USES, OPEN UP YOUR \Stepmania 5\Songs\ folder in the command prompt and run:
// dir /s /b *.sm > songlist.txt
// this program assumes you've already got a songlist.txt ready to go.
// lets get it!

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <cstdlib>
using namespace std;

int main()
{
    //set locale
    locale::global(locale(""));


    const int MAXTOREAD = 255;
    ifstream chartToRead; //wifstream expects wide characters
    ifstream songlist;
    
    //open output stream
    ofstream csvoutput;
    csvoutput.open("songlist.csv");

    //get the songlist
    cout << "Songlist file name please \n";
    char songlistfilename[MAXTOREAD];
    cin.getline(songlistfilename, MAXTOREAD);
    songlist.open(songlistfilename);
    if (!songlist.is_open()) {
        exit(EXIT_FAILURE);
    }

    char filename[MAXTOREAD];
    string data;

    //looping through songlist.txt
    while (songlist.good()) {
        //get file name
        songlist.getline(filename, MAXTOREAD);

        //open file
        chartToRead.open(filename);
        if (!chartToRead.is_open()) {
            exit(EXIT_FAILURE);
        }

        //extract packname from the folder it is in
        string packname;
        string filenamestr = filename;
        int pos;
        pos = filenamestr.rfind('\\'); // find the last slash
        filenamestr = filenamestr.substr(0, pos); //exclude that slash
        pos = filenamestr.rfind('\\'); //find the next to last slash
        filenamestr = filenamestr.substr(0, pos); //exclude it again
        pos = filenamestr.rfind('\\'); //find the 3rd to last slash
        packname = filenamestr.substr(pos+1, filenamestr.npos); // this is the pack name, hopefully!


        //extract info from file
        string line;
        string artist;
        string title;
        bool artistnotfound = true;
        bool titlenotfound = true;
        while (chartToRead.good() && (artistnotfound || titlenotfound)) {

            getline(chartToRead, line);
            if (line.rfind("#ARTIST:", 0) == 0) {
                artist = line.substr(8, line.npos);
                artistnotfound = false;
            }
            if (line.rfind("#TITLE:", 0) == 0) {
                title = line.substr(7, line.npos);
                titlenotfound = false;
            }
        }

        //housekeeping to get rid of ending ;'s
        int len;
        len = artist.size();
        artist = artist.substr(0, len - 1);
        len = title.size();
        title = title.substr(0, len - 1);

        //print info from file
        csvoutput << artist << "," << title << " (" << packname << ")\n";
        chartToRead.close();
    }
    csvoutput.close();
    //cin.getline(path, MAXTOREAD);
  
    //  ask user for a filename (testing purposes)
    //cin.getline(filename, MAXTOREAD);



    

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
