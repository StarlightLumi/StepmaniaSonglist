// Code by Todd Oakes, 10/22/2020
// Free to use and improve, so long as Todd Oakes is credited as well.

// It's essentially a fancy file reader.
// Since .sm files use # tags, finding the info we need is easy.
// The file doesnt show right in Excel
//  tell microsoft to fix their shit, my program works just fine.

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <cstdlib>
#include <vector>
#include <windows.h>
using namespace std;

wstring utf8toUtf16(const string& str)
{
    if (str.empty())
        return wstring();

    size_t charsNeeded = ::MultiByteToWideChar(CP_UTF8, 0,
        str.data(), (int)str.size(), NULL, 0);
    if (charsNeeded == 0)
        throw runtime_error("Failed converting UTF-8 string to UTF-16");

    vector<wchar_t> buffer(charsNeeded);
    int charsConverted = ::MultiByteToWideChar(CP_UTF8, 0,
        str.data(), (int)str.size(), &buffer[0], buffer.size());
    if (charsConverted == 0)
        throw runtime_error("Failed converting UTF-8 string to UTF-16");

    return wstring(&buffer[0], charsConverted);
}

int main()
{
    //set locale  ja_JP.UTF-8 / en_US.UTF-8
    setlocale(LC_ALL, "en_US.UTF-8");


    const int MAXTOREAD = 255;
    wifstream chartToRead; //wifstream expects wide characters
    ifstream songlist;

    //open output stream
    wofstream csvoutput;
    csvoutput.open("songlist.csv");

    //get the songlist
    cout << "Input number of columns desired (1, 2, or 3)\n";
    string option;
    getline(cin, option);
    int numcolumns = stoi(option);

    //write first line to file
    if (numcolumns == 1) {
        csvoutput << "Title\n";
    }
    else if (numcolumns == 2) {
        csvoutput << "Artist,Title\n";
    }
    else if (numcolumns == 3) {
        csvoutput << "Artist,Title,Pack\n";
    }
    else { //its just gonna write a blank file, might as well exit now.
        cout << "Really dude?\n";
        system("PAUSE");
        exit(EXIT_SUCCESS);
    }

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
        string packnamestr;
        string filenamestr = filename;
        int pos;
        pos = filenamestr.rfind('\\'); // find the last slash
        filenamestr = filenamestr.substr(0, pos); //exclude that slash
        pos = filenamestr.rfind('\\'); //find the next to last slash
        filenamestr = filenamestr.substr(0, pos); //exclude it again
        pos = filenamestr.rfind('\\'); //find the 3rd to last slash
        packnamestr = filenamestr.substr(pos + 1, filenamestr.npos); // this is the pack name, hopefully!

        wstring packname = utf8toUtf16(packnamestr);


        //extract info from file
        wstring line;
        const wstring atext = utf8toUtf16("#ARTIST:");
        const wstring ttext = utf8toUtf16("#TITLE:");
        wstring artist;
        wstring title;
        bool artistnotfound = true;
        bool titlenotfound = true;
        //int findingcounter = 0;//debug

        while (chartToRead.good() && (artistnotfound || titlenotfound)) {

            getline(chartToRead, line);
            if (line.rfind(atext, 0) == 0) {
                artist = line.substr(8, line.npos);
                artistnotfound = false;
            }
            if (line.rfind(ttext, 0) == 0) {
                title = line.substr(7, line.npos);
                titlenotfound = false;
            }
            
            /*       //DEBUG 
            if (findingcounter == 0)
            {
                wcout << line << '\n';
            }
            wcout << atext << ttext;
            findingcounter++;
            */
        }

        //housekeeping to get rid of ending ;'s
        int alen, tlen;
        alen = artist.size();
        artist = artist.substr(0, alen - 1);
        tlen = title.size();
        title = title.substr(0, tlen - 1);

        //title errors can be handled by grabbing the name of the file
        if (tlen == 0) {
            wstring titlebackup = utf8toUtf16(filename);
            int tpos = titlebackup.rfind('\\'); //find the last slash
            int dotpos = titlebackup.rfind('.'); //find the extension
            title = titlebackup.substr(tpos+1, dotpos-tpos-1);
         }

        /*     //DEBUG

        if (alen <= 1 || tlen <= 1)
        {
            wcout << "Empty artist or title\n" << artist << " - " << title << " (" << packname << ")\n" << "Counter: "<< findingcounter;
            system("PAUSE");
        }
        */

        //print info from file
        if (numcolumns == 1) {
            csvoutput << artist << " - " << title << " (" << packname << ")\n";
        }
        else if (numcolumns == 2) {
            csvoutput << artist << "," << title << " (" << packname << ")\n";
        }
        else if (numcolumns == 3) {
            csvoutput << artist << "," << title << "," << packname << "\n";
        }
        //wcout << artist << " - " << title << " (" << packname << ")\n";  //debug (printing slows program down)
        chartToRead.close();
    }
    csvoutput.close();


    return 0;
}

/*MIT License

Copyright(c) 2020 Todd Oakes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
