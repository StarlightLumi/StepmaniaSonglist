# StepmaniaSonglist
Takes a songlist.txt file generated in command line, and spits out a nice .csv.

Issues: Some songs with foreign text appear as blank in the spreadsheet.  Some how up fine.  I don't know how to fix that.

To use:
First, download StepmaniaSonglist.exe, and place it in your \Stepmania 5\Songs\ folder.
1. Open up command prompt as adminitrator.  Open the start menu, type in "cmd", and right click on "Command Prompt" to run as adminitrator.
2. Navigate to your \Stepmania 5\Songs\ folder. Use `  cd.. ` to go up one level and `  cd <foldername> ` to navigate into a folder.  To navigate to another drive, type in ` D:` (or whatever letter the drive is)
3. Type in the following: 

`  dir /s /b *.sm > songlist.txt `

4. Open up StepmaniaSonglist.exe in your \Songs\ folder, where there should now be a songlist.txt
5. Select 1, 2, or 3 column mode.
6. Type in "songlist.txt" in the command prompt that opens.
7. Expected runtime: 2-5 minutes depending on amount of songs.

It looks terrible in Excel.  Check it in Notepad to make sure all the foreign text came through, and then bug Microsoft to fix their spreadsheet software.

1 column mode is intended for printing/PDF's.  Rename the .csv to .txt for printing.

2 column mode is intended for upload to streamersonglist.com, since it only accepts Artist and Title fields.

3 column mode is fancy, but idk where you'd use that yet.  
