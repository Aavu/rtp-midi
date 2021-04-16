//
// Created by Raghavasimhan Sankaranarayanan on 4/14/21.
//

#include <iostream>
#include <csignal>
#include "rtpmidi.h"
#include "EventCallback.h"

static bool exiting = false;

#define ROBOT_NAME "Your Robot"
#define MIDI_CHANNEL 0
#define PORT 5004

class EventHandler : public EventCallback {
public:
    explicit EventHandler(int midiChannel) : EventCallback(midiChannel) {}

    ~EventHandler() = default;

    void cc(uint8_t key, uint8_t value) override {
        // Handle CC Messages
        std::cout << "CC\t" << m_iChannel << "\t" << (int)key << "\t" << (int)value << std::endl;
    }

    void noteOn(uint8_t note, uint8_t velocity) override {
        // Handle Note On
        std::cout << "Note On\t" << m_iChannel << "\t" << (int)note << "\t" << (int)velocity << std::endl;
    }

    void noteOff(uint8_t note, uint8_t velocity) override {
        // Handle Note Off
        std::cout << "Note Off\t" << m_iChannel << "\t" << (int)note << "\t" << (int)velocity << std::endl;
    }

    void channelPressure(uint8_t pressure) override {
        // Handle Channel Pressure
        std::cout << "pressure\t" << m_iChannel << "\t" << (int)pressure << std::endl;
    }

    void peerConnected(int port, const std::shared_ptr<::rtpmidid::rtppeer>& peer) override {
        // Handle peer connection
        std::cout << "Remote client connects to local server at port " << port << ". Name: " << peer->remote_name << std::endl;
    }

    void peerDisconnected(rtpmidid::rtppeer::disconnect_reason_e reason) override {
        // Handle peer disconnection
        std::cout << "Disconnected" << reason << std::endl;
    }
};

void sigint_f(int) {
    if (exiting) {
        exit(1);
    }
    exiting = true;
    INFO("SIGINT received. Closing.");

}

int main(int argc, char* argv[]) {
    signal(SIGINT, sigint_f);
    signal(SIGTERM, sigint_f);

    int ch = MIDI_CHANNEL;
    if (argc == 2) {
        ch = strtol(argv[1], nullptr, 10);
    }

    EventHandler handler(ch);
    RtpMidi rtpMidi(ROBOT_NAME, handler, PORT);
    if (rtpMidi.init() != 0) {
        return 1;
    }

    rtpMidi.run();

    return 0;
}