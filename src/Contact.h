/**
 * @file Contact.h
 * @brief Definition of the Contact data structure.
 */

#ifndef CONTACT_H
#define CONTACT_H

#include <string>
using namespace std;

struct Contact {
    int id;
    string name;
    string phone;
    string email;
};

#endif // CONTACT_H