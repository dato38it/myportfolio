#include "contactsreader.h"
namespace {
    const std::vector<Contact> mockData{
        {"Wylie", "Johns", "386756745353"},
        {"Ilric", "David", "4534543534534"},
        {"Tuart", "Staas", "6756765756755"},
        {"Tylie", "Johns", "5665746776756"},
        {"Wylie", "David", "4534543534534"},
        {"Tuart", "Staas", "3867567453533"},
        {"Ilric", "Johns", "6756765756755"},
        {"Wylie", "David", "4534543534534"},
        {"Tuart", "Staas", "3867567453353"},
        {"", "David", "6756765756755"}
    };
}
std::pair<bool, std::vector<Contact> > contactsreader::requestContactsBrowse()
{
    return std::make_pair(true, mockData);
}
