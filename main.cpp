#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <string.h>
#include <unistd.h>
#include <string>
#include "rkllm.h"
#include <fstream>
#include <iostream>
#include <csignal>
#include <vector>

#define PROMPT_TEXT_PREFIX "<|im_start|>system You are a helpful assistant. <|im_end|> <|im_start|>user"
#define PROMPT_TEXT_POSTFIX "<|im_end|><|im_start|>assistant"

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;
LLMHandle llmHandle = nullptr;

struct RecvModelInfo{ // 用于数据的输出
    server *srv;
    websocketpp::connection_hdl *hdl;
};

void exit_handler(int signal)
{
    if (llmHandle != nullptr)
    {
        {
            std::cout << "程序即将退出" << std::endl;
            LLMHandle _tmp = llmHandle;
            llmHandle = nullptr;
            rkllm_destroy(_tmp);
        }
        exit(signal);
    }
}

// 模型回调
void callback(RKLLMResult *result, void *userdata, LLMCallState state){
    auto distInfo = static_cast<RecvModelInfo*>(userdata); 
    if(!distInfo){
        printf("distInfo is null \n");
        return ;
    }
    if (state == LLM_RUN_FINISH){
        printf("\n");
      
    }else if (state == LLM_RUN_ERROR){
        printf("\\run error\n");
    }else{
        printf("%s", result->text); 
        distInfo->srv->send(*distInfo->hdl,result->text,websocketpp::frame::opcode::text);    
    }
}

//  模型初始化
void initModel(){
    //设置参数及初始化
    RKLLMParam param = rkllm_createDefaultParam();
    param.model_path = "Qwen-1_8B-Chat.rkllm";
    param.num_npu_core = 2;
    param.top_k = 1;
    param.max_new_tokens = 256;
    param.max_context_len = 512;
    param.logprobs = false;
    param.top_logprobs = 5;
    param.use_gpu = false;
    rkllm_init(&llmHandle, param, callback);
    printf("rkllm init success\n");

}

// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;
    //  向大模型提问          
    printf("robot: ");
    RecvModelInfo minfo;
    minfo.srv = s;
    minfo.hdl = &hdl;
    rkllm_run(llmHandle, msg->get_payload().c_str(), &minfo);
    // check for a special command to instruct the server to stop listening so
    // it can be cleanly exited.
    if (msg->get_payload() == "stop-listening") {
        s->stop_listening();
        return;
    }

    try {
        // s->send(hdl, msg->get_payload(), msg->get_opcode());
    } catch (websocketpp::exception const & e) {
        std::cout << "Echo failed because: "
                  << "(" << e.what() << ")" << std::endl;
    }

    
}

int main() {
    // Create a server endpoint
    server echo_server;

    try {

        initModel();
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(bind(&on_message,&echo_server,::_1,::_2));

        // Listen on port 9002
        echo_server.listen(9002);

        // Start the server accept loop
        echo_server.start_accept();

        // Start the ASIO io_service run loop
        echo_server.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
}