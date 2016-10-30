/* 
 * File:   freeuser.h
 * Author: Václav Jirovský
 *
 * Created on 20. květen 2011, 9:37
 */

#ifndef FREEUSER_H
#define	FREEUSER_H



#include "rdownloader.h"
//! class implements downloading as free user
class FreeUser : public rdownloader {
public:
    FreeUser(string& link, string& destination); //! constructor of premiumuser, only uses constructor of rdownload, makes 2 connections: first gets auth. string and second is downloading
    bool Download(void); //! Main function which starts communication with RS 
    static int WriteDataToMemory(char *data, size_t size, size_t nmemb, std::string *buffer); //! writes to memory response data from rapidshare
    static size_t WriteDataToFile(void *ptr, size_t size, size_t nmemb, FILE *stream); //! writes to file data from curl
    static int Progress_func(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded); //! show progressbar about downloading as free user
    virtual ~FreeUser(); //! empty, we don't have any dynamic allocated memory

private:
    // freeuser doesnt need any private or protected data    

};

#endif	/* FREEUSER_H */

