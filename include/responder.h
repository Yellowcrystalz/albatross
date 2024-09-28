#ifndef RESPONDER_H
#define RESPONDER_H

#include "albatross.h"

int findFile(HttpResponse* httpRes);
void httpHeaderBuilder(HttpResponse* httpRes);

#endif // !RESPONDER_H
