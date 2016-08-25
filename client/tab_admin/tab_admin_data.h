#ifndef __tab_admin_data_h
#define __tab_admin_data_h

#include <QString>

//! The structure to hold a users data.
struct UserData
{
    QString userName;
    QString passWord;
    QString tokaNr;
    QString usrNr;
    QString fname; //!< first name
    QString lname; //!< last name
    QString tlf;
    QString mobil;
    QString email;
    void clear() {
        userName.clear();
        passWord.clear();
        tokaNr.clear();
        usrNr.clear();
        fname.clear();
        lname.clear();
        tlf.clear();
        mobil.clear();
        email.clear();
    };
};
//! The structure of a Mail Rule.
/*!
    It contains all the fields required to
    make a mail rule.
*/
struct MailRule
{
    int id;       //!< the id of a current rule or 0 if a new rule.
    bool active;  //!< is it an active?
    QString type; //!< the type of rule.
    QString cond; //!< the condition type.
    QString test; //!< the value to be tested against.
    QString list; //!< the maillist to include if the test is true.
    //! a convenience function.
    /*!
        a convenient function to zero out all the fields of the mail rule.
    */
    void clear() {
        id=0;
        active = true;
        type.clear();
        cond.clear();
        test.clear();
        list.clear();
    };
};

#endif
