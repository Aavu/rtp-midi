//
// Created by Raghavasimhan Sankaranarayanan on 4/14/21.
//

#ifndef RTPMIDIPEEREXAMPLE_RTPMIDI_H
#define RTPMIDIPEEREXAMPLE_RTPMIDI_H

#include <iostream>
#include <string>
#include <functional>

#include "rtpmidid/rtppeer.hpp"
#include "rtpmidid/iobytes.hpp"
#include <rtpmidid/rtpserver.hpp>
#include "rtpmidid/poller.hpp"

#include "EventCallback.h"
#include "avahiClient.cpp"

using namespace std;

class RtpMidi {
public:
    explicit RtpMidi(const string& robotName, EventCallback& callback, int port=5004);
    int init();

    ~RtpMidi();

    int run() const;

    void callbackHandler(rtpmidid::io_bytes_reader &data);
    static void client_callback(AvahiClient *c, AvahiClientState state, AVAHI_GCC_UNUSED void * userdata);

private:
    const char *m_robotName;
    int m_iPort;
    EventCallback& m_callback;
    rtpmidid::rtpserver m_server;

    AvahiClient *m_pAvahiClient;
    AvahiSimplePoll* m_pPoll;
    bool m_bInitialized;
};


#endif //RTPMIDIPEEREXAMPLE_RTPMIDI_H
