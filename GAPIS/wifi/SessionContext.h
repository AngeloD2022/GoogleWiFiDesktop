//
// Created by Angelo DeLuca on 3/22/21.
//

#ifndef GOOGLEWIFIDESKTOPCLIENT_SESSIONCONTEXT_H
#define GOOGLEWIFIDESKTOPCLIENT_SESSIONCONTEXT_H

#endif //GOOGLEWIFIDESKTOPCLIENT_SESSIONCONTEXT_H

#pragma once

#include <QString>
#include <QtNetwork>

class SessionContext{

public:

    struct Token{
        QString content;
        int expires;
    };

    static QString at_content;
    static int at_exp;

    static QString ft_content;
    static int ft_exp;

    static QString systemId;
};
