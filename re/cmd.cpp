#include <iostream>

#include "cmd.hpp"
#include "player.hpp"

using namespace std;

// Brute force it for now
void cmd_runner( char *cmdstr )
{
    string cmd(cmdstr);

    if ( cmd == "snap" ) {

        cout << "CMD snap " << endl;
        player->command_request("snap");

    } else if ( cmd == "filter" ) {

        cout << "CMD filter " << endl;

    } else if ( cmd == "record" ) {
        cout << "CMD record " << endl;            
        player->command_request("record");
    } else if ( cmd == "pause" ) {
        cout << "CMD pause " << endl;
        player->command_request("pause");
    } else if ( cmd == "stop" ) {
        cout << "CMD stop " << endl;
        player->command_request("stop");

    } else if ( cmd == "stop" ) {
        cout << "CMD stop " << endl;
    } else {
        cerr << "Error unsupported command: " << cmd << endl;
    }
}
