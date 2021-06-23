#include <iostream>
#include "cmd.hpp"

using namespace std;

// Brute force it for now
void cmd_runner( char *cmdstr )
{
    string cmd(cmdstr);

    if ( cmd == "snap" ) {
        cout << "CMD snap " << endl;
    } else if ( cmd == "record" ) {
        cout << "CMD record " << endl;            
    } else if ( cmd == "pause" ) {
        cout << "CMD pause " << endl;
    } else if ( cmd == "play" ) {
        cout << "CMD play " << endl;
    } else {
        cerr << "Error unsupported command: " << cmd << endl;
    }
}
