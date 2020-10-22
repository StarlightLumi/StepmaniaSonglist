// Code by Todd Oakes, 10/22/2020
// Free to use and improve, so long as Todd Oakes is credited as well.

// It's essentially a fancy file reader.
// Since .sm files use # tags, finding the info we need is easy.
// However, the "Locale" doesnt work.
// Sometimes UTF characters get dropped.
//  but not always?  And usually only from titles?

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
 
    return 0;
}
