#ifndef BASE_TOOL_SECURITY_KEYINFO_H
#define BASE_TOOL_SECURITY_KEYINFO_H

#include "http_request.h"
#include "auto_buffer.h"
#include "cJSON.h"

namespace base_tool { 
 
class KeyInfo { 
    public: 
        int version_; 
        int scenario_; 
        int add_salt_aes_case_; 
        AutoBuffer default_passwd_; 
 
        base_tool::AutoBuffer   client_pubkey_; 
        base_tool::AutoBuffer   client_pubkey_base64enc_; 
        char                    client_pubkey_base64enc_md5sum_[33];         
        base_tool::AutoBuffer   client_pubkey_defenc_; 
        base_tool::AutoBuffer   client_pubkey_defenc_base64enc_; 
        base_tool::AutoBuffer   client_pubkey_defenc_base64enc_urlenc_; 
        base_tool::AutoBuffer   share_secret_; 
        base_tool::AutoBuffer   share_secret_base64enc_; 
        base_tool::AutoBuffer   share_secret_base64enc_addsalt_; 
 
        void SetKeyInfo(int version, int scenario, int add_salt_aes_case, const char * default_passwd); 
        void GenKey(); 
}; 
 
} 

#endif //BASE_TOOL_SECURITY_KEYINFO_H

