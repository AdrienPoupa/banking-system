//
// Created by Adrien on 24/05/2016.
//

#ifndef BANKING_SYSTEM_NOTIFICATION_H
#define BANKING_SYSTEM_NOTIFICATION_H

#include <stdio.h>
#include <set>
#include <iostream>

class Notification {
protected:
    unsigned int _id;
    std::string _message;
    unsigned int _userId;
    bool _read;

    static std::string _dbTable;
public:
    Notification();
    Notification(unsigned int id);
    Notification(std::string message, unsigned int userId);

    unsigned int getId();
    void setId(unsigned int id);

    std::string getMessage();
    void setMessage(std::string message);

    unsigned int getUserId();
    void setUserId(unsigned int userId);

    bool getRead();
    void setRead(bool read);

    bool save();

    bool remove();

    friend std::ostream& operator<< (std::ostream& stream, const Notification& notification);
    friend std::istream& operator>> (std::istream& stream, Notification& notification);
};


#endif //BANKING_SYSTEM_NOTIFICATION_H
