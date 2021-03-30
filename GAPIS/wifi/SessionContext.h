//
// Created by Angelo DeLuca on 3/22/21.
//

#ifndef GOOGLEWIFIDESKTOPCLIENT_SESSIONCONTEXT_H
#define GOOGLEWIFIDESKTOPCLIENT_SESSIONCONTEXT_H

#endif //GOOGLEWIFIDESKTOPCLIENT_SESSIONCONTEXT_H

#include <QString>
#include <QtNetwork>

class SessionContext{

public:

    struct Token{
        QString content;
        int expires;
    };

    static QString at_content;
    static QString ft_content;

    static int at_exp;
    static int ft_exp;

};
