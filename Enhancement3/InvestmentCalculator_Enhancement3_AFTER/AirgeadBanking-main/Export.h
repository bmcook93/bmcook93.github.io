/************************************************************
** Name: Export.h                                          **
** Author: Brandon Cook                                    **
*************************************************************/

#pragma once
#ifndef EXPORT_H
#define EXPORT_H

#include "Investment.h"

class Export {
public:
    static void run(Investment& userInvestment); // one method to export
};

#endif