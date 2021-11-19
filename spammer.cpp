#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>
#include "httplib.h"
#pragma comment(lib, "libcrypto")
#pragma comment(lib, "libssl")
using namespace std;

// --> Linux <--
// Needs cpp-httplib fom yhirose to work 

string escape_json(const string &s) {
    ostringstream o;
    for (auto c = s.cbegin(); c != s.cend(); c++) {
        switch (*c) {
        case '"': o << "\\\""; break;
        case '\\': o << "\\\\"; break;
        case '\b': o << "\\b"; break;
        case '\f': o << "\\f"; break;
        case '\n': o << "\\n"; break;
        case '\r': o << "\\r"; break;
        case '\t': o << "\\t"; break;
        default:
            if ('\x00' <= *c && *c <= '\x1f') {
                o << "\\u"
                  << hex << setw(4) << setfill('0') << (int)*c;
            } else {
                o << *c;
            }
        }
    }
    return o.str();
}

void initflood(string wb = "") {
    using namespace httplib;
    if (wb == "") return;
    string msg, endpoint, message;
    cout << "\nNow enter the message that will be sended: ";
    cin >> msg;
    cout << "\nBeginning Flood...";
    endpoint = wb;
    message = "{\"content\":\""+ escape_json(msg) +"\"}";
    try {
        Client req("https://discord.com");
        while (true) {
            auto r = req.Post(endpoint.c_str(), message.c_str(), message.length(), "application/json");
            if (r) {
                cout << "[" << r->status << "] Succesfully Sended, Response: => \n" << r->body << "\n\n";
            } else {
                cerr << "Error at requesting.\n" << r.error();
                return;
            }
        }
    } catch (...) {
        cerr << "Error at requesting.";
        return;
    }
}

int main() {
    string w;
    cout << "Enter the Webhook: ";
    cin >> w;
    // REGEX/Format: /api/webhooks/\d+/\w-
    initflood(w);
    return 0;
}
