/* 
 * File:   rdownloader.h
 * Author: Václav Jirovský
 *
 * Created on 10. květen 2011, 9:34
 */

#ifndef RDOWNLOADER_H
#define	RDOWNLOADER_H
#include "common.h"

using namespace std;

//
//! big class, contains data for both free and premium user

class rdownloader {
public:
    rdownloader(string& link, string& destination);

    virtual ~rdownloader();
    bool checkSyntaxLink(void); //! checks link if is ok (only syntax, not availability of file 
    string getActualLink(void); //! gives string of actual link
    string getFilename(void); //! gives only filename from link
    string getFileID(void); //! gives only fileid from link   
    string getDestination(void); //! gives only destination
protected:
    string link; //! stored link of remote file
    string destination; //! stored local destination to save file
    string user_agent; //! user agent of this program
};

#endif	/* RDOWNLOADER_H */

