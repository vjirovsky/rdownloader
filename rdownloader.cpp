/* 
 * File:   rdownloader.cpp
 * Author: Václav Jirovský
 * 
 * Created on 10. květen 2011, 9:34
 */

#include "rdownloader.h"
#define REG_EXP "^http(s)?\://(www.|r[0-9]{1,2}.)?rapidshare.com\/files\/[0-9]{1,20}/"   //! regexp for rapidshare links

string& str_replace(const string &search, const string &replace, string &subject) {
    string buffer;

    int sealeng = search.length();
    int strleng = subject.length();

    if (sealeng == 0)
        return subject; //no change

    for (int i = 0, j = 0; i < strleng; j = 0) {
        while (i + j < strleng && j < sealeng && subject[i + j] == search[j])
            j++;
        if (j == sealeng)//found 'search'
        {
            buffer.append(replace);
            i += sealeng;
        } else {
            buffer.append(&subject[i++], 1);
        }
    }
    subject = buffer;
    return subject;
}

rdownloader::rdownloader(string& insert_link, string& insert_destination) {
    link = insert_link;
    destination = insert_destination;
    if (!this->checkSyntaxLink()) {
        cout << "Bad syntax of file. Download aborted." << endl;
        exit(1);

    }

    if (destination == "") {
        if (DEBUG)
            cout << "Empty destination - destination reseted to directory of program." << endl;

        char cCurrentPath[FILENAME_MAX];

        if (!GetCurrentDir(cCurrentPath, sizeof (cCurrentPath))) {
            cout << "internal problem with path of program." << endl;
            exit(1);
        }

        cCurrentPath[(sizeof (cCurrentPath) - 1)] = '/0';

        destination = cCurrentPath; //empty path
        destination = str_replace("\\", "/", destination);
        user_agent = "rDownloader/0.5";
    }
}

string rdownloader::getActualLink(void) {
    return link;
    //! @return returns string of remote link on RS
}

string rdownloader::getDestination(void) {
    return destination;
    //! @return returns string of destination on local disk
}

string rdownloader::getFilename(void) {
    char delimiter[] = "/";
    char *token;
    string filename, temp_link;
    temp_link = link; //! temp link because strtok will damage original link
    token = strtok(&temp_link[0], delimiter);
    int i = 0, j = 0;


    while (token != NULL) {
        /* in link http://rapidshare.com/file/ID/FILENAME is 4. by delimiter /*/
        switch (i) {
            default:
                break;
            case 4:
                filename = token;

                return filename;
                break;
        }
        token = strtok(NULL, delimiter);
        i++;

    }
    return "ERROR";
    //! @return returns string of name of file from link on RS
}

string rdownloader::getFileID(void) {
    char delimiter[] = "/";
    char *token;

    string fileid, temp_link;
    temp_link = link; //! temp link because strtok will damage original link
    token = strtok(&temp_link[0], delimiter);
    int i = 0;


    while (token != NULL) {
        /* Do your thing */
        switch (i) {
            default:
                break;
            case 3:
                fileid = token;
                return fileid;
                break;
        }
        token = strtok(NULL, delimiter);
        i++;

    }
    return "ERROR";
    //! @return returns string of fileid from link on RS
}

bool rdownloader::checkSyntaxLink(void) {
    pcre* regexp_handle;
    const char* regexp_err;
    int regexp_err_offset;

    regexp_handle = pcre_compile(REG_EXP, 0, &regexp_err, &regexp_err_offset, NULL); // predkompilace regexpu
    if (!regexp_handle) {
        cout << "ERROR: " << regexp_err << endl;
        exit(1);
    }


    int rc;
    int ovector[1];
    rc = pcre_exec(regexp_handle, NULL, link.c_str(), strlen(link.c_str()), 0, 0, ovector, 1);

    pcre_free(regexp_handle);
    if (rc < 0) {
        return 0;
    }
    return 1;
    //! @return bool, if link is ok
}

rdownloader::~rdownloader() {
}

