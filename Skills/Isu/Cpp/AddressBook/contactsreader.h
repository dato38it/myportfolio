#pragma once
#include <utility>
#include <vector>
#include "contacts.h"
class contactsreader
{
public:
    std::pair<bool, std::vector<Contact>> requestContactsBrowse();
};
