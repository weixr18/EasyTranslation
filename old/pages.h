#ifndef PAGES_H
#define PAGES_H
#include <vector>
#include "CTP.h"
#include "missioninfo.h"
#include "userinfo.h"

#define KEY_PAGE std::pair<std::string, PageType>

class Pages
{
public:
    Pages();
    ~Pages();

public:

    enum PageType{USERPAGE, MISSIONPAGE};

public:


private:
    static std::vector<KEY_PAGE> openPages;



};

#endif // PAGES_H
