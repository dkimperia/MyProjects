#include <iostream>
#include <nlohmann/json.hpp>
#include <uwebsockets/App.h>

using namespace std;
using json = nlohmann::json;

const string COMMAND = "command";
const string USER_ID = "user_id";
const string MESSAGE = "message";
const string USER_FROM = "user_from";
const string PRIVATE_MSG = "private_msg";
const string SET_NAME = "set_name";

struct PerSocketData {
    /* Fill with user data */
    int user_id;
    string name;

};

typedef uWS::WebSocket<false, true, PerSocketData> UWEBSOCK;



void processMessage(UWEBSOCK* ws, std::string_view message) {
    PerSocketData* data = ws->getUserData();
    auto parsed = json::parse(message);

    string command = parsed[COMMAND];

    if (command == PRIVATE_MSG) {
        int user_id = parsed[USER_ID];
        string user_msg = parsed[MESSAGE];
        json response;
        response[COMMAND] = PRIVATE_MSG;
        response[USER_FROM] = data->user_id;
        response[MESSAGE] = user_msg;
        ws->publish("userN" + to_string(user_id), response.dump());

    }

    if (command == SET_NAME) {
        //..
    }

}


/* This is a simple WebSocket echo server example.
 * You may compile it with "WITH_OPENSSL=1 make" or with "make" */ 

int main() {
    /* ws->getUserData returns one of these */
  

    int latest_id = 10;

    /* Keep in mind that uWS::SSLApp({options}) is the same as uWS::App() when compiled without SSL support.
     * You may swap to using uWS:App() if you don't need SSL */
    uWS::App().ws<PerSocketData>("/*", {
            /* Settings */
            .idleTimeout = 9999,
            /* Handlers */
            .open = [&latest_id](auto* ws) {
         
                /* Open event here, you may access ws->getUserData() which points to a PerSocketData struct */
                PerSocketData *data = ws->getUserData();
                data->user_id = latest_id++; // Присваеваем каждому пользователю айди

                cout << "User #" << data->user_id << "connected" << endl;

                ws->subscribe("broadcast"); //broadcast - сообщ получ все пользователи
                ws->subscribe("userN" + to_string(data->user_id)); // личный канал

            },
            .message = [](auto* ws, std::string_view message, uWS::OpCode opCode) {
                PerSocketData* data = ws->getUserData();
                cout << "Message from User #" << data->user_id << " : " << message << endl;
                processMessage(ws, message);
            },
            .close = [](auto*/*ws*/, int /*code*/, std::string_view /*message*/) {
                cout << "CLOSE\n";
                /* You may access ws->getUserData() here */
            }
            }).listen(9001, [](auto* listen_socket) {
                if (listen_socket) {
                    std::cout << "Listening on port " << 9001 << std::endl;
                }
            }).run();
}

/*

1) Пользовтели имебт имена


Клиент:
{"command": "private_msg", "user_id": 12, "message": "Привет, двенадцатый!"}

Сервер вышлет сообщение клиенту
{"command": "private_msg", "user_from": 14, "message": "Привет, двенадцатый!"}



2) Пользователи умеют отправлять друг другу сообщения


*/