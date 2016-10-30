/* 
 * File:   PremiumUser.cpp
 * Author: Václav Jirovský
 * 
 * Created on 11. květen 2011, 18:19
 */

#include "PremiumUser.h"


using namespace std;
PremiumUser::PremiumUser(string& insert_link, string& insert_destination, string& insert_user, string& insert_password) : rdownloader(insert_link, insert_destination) {
    if (DEBUG)
        cout << "I am downloading as premium user link '" << insert_link << "' to destination '" << destination << "'" << endl;
    username = insert_user;
    password = insert_password;


}

static char errorBuffer[CURL_ERROR_SIZE];
static string buffer;


string global_premium_destination = ""; //! has to be global because libcurl doesn't full support class, this is used only for writing to file

string global_premium_filename = ""; //! has to be global because libcurl doesn't full support class, this is used only for writing to file

size_t PremiumUser::WriteDataToFile(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    static int first_time = 1;
    string outfilename = global_premium_destination + "/" + global_premium_filename;
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

int PremiumUser::WriteDataToMemory(char *data, size_t size, size_t nmemb, std::string *buffer) { //! this function writes to memory, beucase we need to process string from response from rapidshare

    int result = 0;

    if (buffer != NULL) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }

    return result;
}

int PremiumUser::Progress_func(void* ptr, double TotalToDownload, double NowDownloaded,
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

bool PremiumUser::Download() {
    CURL *curl;
    CURLcode result;


    FILE *fp;


    curl = curl_easy_init();
    
    string new_address, server, dlauth;
    string old_address = new_address = "/cgi-bin/rsapi.cgi?sub=download&fileid=" + this->getFileID() + "&login=" + username + "&password=" + password + "&filename=" + this->getFilename();

    old_address = "https://api.rapidshare.com" + old_address;

    old_address += "&try=1";

    if (curl) {
        if (DEBUG)
            cout << "API url is:" << old_address << endl;

        // Now set up all of the curl options  
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_URL, old_address.c_str());


        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataToMemory);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);


        result = curl_easy_perform(curl); // response from rapidshare

        // Always cleanup  
        curl_easy_cleanup(curl);
        if (result != CURLE_OK) {
            cout << endl << "ERROR: Communication with server problem. Downloading aborted." << endl;
            exit(1);
        }
        char delimiter[] = ",";
        char *token;

        token = strtok(&buffer[0], delimiter);
        if (strstr(buffer.c_str(), "ERROR:")) {
            cout << endl << buffer.substr(0, buffer.find("\n")) << endl << "Downloading aborted." << endl;
            exit(1);
        }
        int i = 0;
        while (token != NULL) {

            switch (i) {
                case 0:
                    server = token;
                    server = server.erase(0, 3);
                    new_address = "https://" + server + new_address;
                    break;
                case 1:
                    if (DEBUG)
                        cout << "Dlauth token:" << token << endl;
                    dlauth = token;
                    break;
            }

            token = strtok(NULL, delimiter);
            i++;

        }
        if (DEBUG)
            cout << "API response \"" << buffer << "\"" << endl;



        curl = curl_easy_init();



        global_premium_destination = this->getDestination();
        global_premium_filename = this->getFilename();
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
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, Progress_func);


        result = curl_easy_perform(curl); // response from rapidshare

        curl_easy_cleanup(curl); // cleanup      
        string tmp_err_buffer = "";
        tmp_err_buffer = errorBuffer;
        if (tmp_err_buffer != "") {
            cout << endl << "ERROR: " << errorBuffer << ". Downloading aborted." << endl;
            exit(1);
        }
        cout << endl << "File '" << this->getFilename() << "'saved to " << destination << endl;
        exit(0);
    } else {
        cout << endl << "ERROR: [" << result << "] - " << errorBuffer;
        exit(1);
    }
}

PremiumUser::~PremiumUser() {
}