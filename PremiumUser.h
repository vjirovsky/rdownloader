/* 
 * File:   PremiumUser.h
 * Author: Václav Jirovský
 *
 * Created on 11. květen 2011, 18:19
 */

#ifndef PREMIUMUSER_H
#define	PREMIUMUSER_H

#include "rdownloader.h"
//! class implements downloading as premium user
class PremiumUser : public rdownloader {
public:
    PremiumUser(string& insert_link, string& insert_destination, string& insert_user, string& i_password); //! constructor of premiumuser, uses constructor of rdownload and adding some other stuff
    bool Download(); //! Main function which starts communication with RS 
    static size_t WriteDataToFile(void *ptr, size_t size, size_t nmemb, FILE *stream); //! writes data to file from curl as premium user
    static int WriteDataToMemory(char *data, size_t size, size_t nmemb, std::string *buffer); //! writes to memory response data from rapidshare
    static int Progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded); //! show progressbar about downloading as premium user
    virtual ~PremiumUser();

private:
    string username; //! username of account
    string password; //! password of account
    


};

#endif	/* PREMIUMUSER_H */

