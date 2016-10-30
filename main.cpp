// RDownloader.cpp : Defines the entry point for the console application.
//
//The headers

#include "common.h"

using namespace std;
string VERSION = "0.5";

#include "rdownloader.h"
#include "freeuser.h"
#include "PremiumUser.h"

using namespace std;
void print_usage() {
    cout << "Usage rdownloader [-f] [-u username] [-p password] [-d destination] [-l link to download]" << endl
            << "Example: rdownloader -f -l http://rapidshare.com/files/1234567/test.txt" << endl;
    exit(1);
} //! function which prints usage and example of this test interface

#ifdef _WIN32

void echo(bool on = true) {
    DWORD mode;
    HANDLE hConIn = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hConIn, &mode);
    mode = on
            ? (mode | ENABLE_ECHO_INPUT)
            : (mode & ~(ENABLE_ECHO_INPUT));
    SetConsoleMode(hConIn, mode);
}
#else

void echo(bool on = true) {
    struct termios settings;
    tcgetattr(STDIN_FILENO, &settings);
    settings.c_lflag = on
            ? (settings.c_lflag | ECHO)
            : (settings.c_lflag & ~(ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}
#endif

int main(int argc, char* argv[]) {

    cout << " ____________________________________" << endl
            << "|                                    |" << endl
            << "|           RDownloader  " << VERSION << "         |" << endl
            << "|    Author: Vaclav Jirovsky 2011    |" << endl
            << "|____________________________________|" << endl << endl;
    if (DEBUG) {
        cout << endl << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl
                << "!                                  !" << endl
                << "!  Starting program in debug mode  !" << endl
                << "!                                  !" << endl
                << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl << endl;
    }
    string username = "", pass = "", link = "", destination = ""; // reseting


    int c;

    bool free_user = 0, premium_user = 0;

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"user", 1, 0, 0},
            {"free", 0, 0, 0},
            {"pass", 1, 0, 0},
            {"destination", 1, 0, 0},
            {"link", 1, 0, 0},
            {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "u:d:fp:l:", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            case 'f':
                if (DEBUG)
                    cout << "Free usermode activated " << endl;

                free_user = 1;
                break;

            case 'u':
                if (DEBUG)
                    cout << "uses login with value ='" << optarg << "'" << endl;
                premium_user = 1;
                username = optarg;
                break;

            case 'l':
                link = optarg;
                if (DEBUG)
                    cout << "link url with value ='" << optarg << "'" << endl;

                break;
            case 'p':
                if (DEBUG)
                    cout << "pass login with value='" << optarg << "'" << endl;
                pass = optarg;
                break;
            case 'd':
                if (DEBUG)
                    cout << "destination with value='" << optarg << "'" << endl;
                destination = optarg;
                break;

            case '?':
            default:
                print_usage();
                break;

        }
    }

    if (optind < argc) {
        cout << "not-recognized arguments: ";
        while (optind < argc)
            cout << argv[optind++];
        cout << endl;
    }

    if ((!free_user && !premium_user) || link == "") {
        print_usage();
    }


    // Everything is ok

    if (premium_user && pass == "") {
        cout << "Type your password:";

        echo(false);
        getline(cin, pass);
        echo(true);
        cout << endl;

    }
    if (premium_user) {
        PremiumUser Download = PremiumUser(link, destination, username, pass);
        return Download.Download();

    } else {
        FreeUser Download = FreeUser(link, destination);
        return Download.Download();

    }

    return 1;
}
