/* 
 * File:   freeuser.cpp
 * Author: Václav Jirovský
 * 
 * Created on 20. květen 2011, 9:37
 */

#include "freeuser.h"



#ifdef _WIN32

void sleep(long d) {
    clock_t start = clock();

    while (clock() - start < d);
} //! for windows replace of sleep()

#else 
#include <unistd.h>
#endif

static char errorBuffer[CURL_ERROR_SIZE];
static string buffer;

int FreeUser::WriteDataToMemory(char *data, size_t size, size_t nmemb, std::string *buffer) { //! this function writes to memory, beucase we need to take authorization string from response from rapidshare

    int result = 0;

    if (buffer != NULL) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }

    return result;
}

string global_free_destination = ""; //! has to be global because libcurl doesn't full support class, this is used only for writing to file

string global_free_filename = ""; //! has to be global because libcurl doesn't full support class, this is used only for writing to file

size_t FreeUser::WriteDataToFile(void *ptr, size_t size, size_t nmemb, FILE *stream) {  
    static int first_time = 1;
    string outfilename = global_free_destination + "/" + global_free_filename;
    static FILE *outfile;
    size_t written;
    if (first_time) {
        first_time = 0;
        outfile = fopen(outfilename.c_str(), "wb");
        if (outfile == NULL)
            return -1;
    }
    written = fwrite(ptr, size, nmemb, outfile);
    return written;
}

FreeUser::FreeUser(string& insert_link, string& insert_destination) : rdownloader(insert_link, insert_destination) {
    if (DEBUG)
        cout << "I am downloading as free user link '" << insert_link << "' to destination '" << destination << "'" << endl;

}

int FreeUser::Progress_func(void* ptr, double TotalToDownload, double NowDownloaded,
        double TotalToUpload, double NowUploaded) {

    int wide_stars = 40; //! number of "width"
    double fractiondownloaded = NowDownloaded / TotalToDownload; //! 0.4 done
    int dotz = round(fractiondownloaded * wide_stars); //! round, 1.3 star cannot be :-)

    int j;
    printf("%3.0f%% [", fractiondownloaded * 100);

    for (j = 0; j < dotz; j++) {// print done stars
        cout << "=";
    }
    if (j <= wide_stars - 1)
        cout << ">"; // end of done stars

    for (; j < wide_stars - 1; j++) { // reaming stars
        cout << " ";
    }
    printf("]\r");
    fflush(stdout);
}

bool FreeUser::Download() {
    CURL *curl;
    CURLcode result;

    FILE *fp;
    // Create our curl handle  
    curl = curl_easy_init();
    
    string api_url = "https://api.rapidshare.com/cgi-bin/rsapi.cgi?sub=download&fileid="
            + this->getFileID() + "&filename=" + this->getFilename();


    if (curl) {
        // Now set up all of the curl options  
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataToMemory);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        result = curl_easy_perform(curl); // response from rapidshare

        // Always cleanup  
        curl_easy_cleanup(curl);

        if (DEBUG)
            cout << "Response from API rapidshare:\"" << buffer << "\"" << endl;

        string dlauth, new_address, server, temp_countdown;
        int countdown;
        if (result != CURLE_OK) {
            cout << endl << "ERROR: Communication with server problem. Downloading aborted." << endl;
            exit(1);
        }
        char delimiter[] = ",";
        char *token;

        token = strtok(&buffer[0], delimiter);
        int i = 0;
        if (strstr(buffer.c_str(), "ERROR:")) {
            cout << buffer.substr(0, buffer.find("\n")) << endl << "Downloading aborted." << endl;
            exit(1);
        }

        while (token != NULL) {

            switch (i) {
                case 0:
                    server = token;
                    server = server.erase(0, 3);
                    break;
                case 1:
                    if (DEBUG)
                        cout << "Dlauth token:" << token << endl;
                    dlauth = token;
                    break;
                case 2:
                    temp_countdown = token;
                    countdown = atoi(temp_countdown.c_str());
                    break;
            }

            token = strtok(NULL, delimiter);
            i++;

        }

        if (DEBUG)
            cout << "Server:" << server << ";Delay:" << countdown << endl;
        if (countdown != 0)
            cout << "Rapidshare moved you into queue of free users (" << countdown << " seconds )" << endl;

        countdown = round(countdown / 5);
        for (int i = countdown - 1; i >= 0; i--) {
            sleep(5000); // seconds
            cout << (i * 5) << " seconds to start downloading" << endl;
        }
        curl = curl_easy_init();

        new_address = "http://" + server + "/cgi-bin/rsapi.cgi?sub=download&fileid=" + this->getFileID() + "&filename=" + this->getFilename() + "&dlauth=" + dlauth;

        global_free_destination = this->getDestination();
        global_free_filename = this->getFilename();
        if (DEBUG)
            cout << "New address: " << (char*) new_address.c_str() << endl;
        
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, (char*) new_address.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, (char*) user_agent.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataToFile);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, Progress_func);


        result = curl_easy_perform(curl); // response from rapidshare

        curl_easy_cleanup(curl); // cleanup

        cout << endl << "File '" << this->getFilename() << "'saved to " << destination << endl;
        exit(0);
    } else {
        cout << endl << "ERROR: [" << result << "] - " << errorBuffer;
        exit(-1);
    }

    return 1;
}

FreeUser::~FreeUser() {
}

