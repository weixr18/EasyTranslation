#ifndef TRANSLATEMISSION_H
#define TRANSLATEMISSION_H
#include <vector>
#include "managemission.h"

class Submission;

class TranslateMission :
        public ManageMission
{

public:
    TranslateMission(ManageMission& m);
    ~TranslateMission();


};

#endif // TRANSLATEMISSION_H
