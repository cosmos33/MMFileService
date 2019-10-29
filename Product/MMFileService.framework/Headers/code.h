#ifndef BASE_TOOL_SECURITY_CODE_H
#define BASE_TOOL_SECURITY_CODE_H

#include "auto_buffer.h"

namespace base_tool{

    class Code {
    public:
        static void Md5Sum(const void * ptr, size_t length, char buf[33]);
        static int Md5Sum(const char *file, char buf[33]);
        static int Base64Enc(const void *inBytes, size_t inByteSize, base_tool::AutoBuffer &out);
        static int Base64Dec(const char *inBase64String, base_tool::AutoBuffer &out);
        static int UrlEnc(const char * in, AutoBuffer &out);
        static int UrlDec(const char * in, AutoBuffer &out);
        static void AddSaltKey(base_tool::AutoBuffer &key, int salt_case);
        static int GenSecretKey(int version, int scenario, base_tool::AutoBuffer &share_key, base_tool::AutoBuffer &client_publick_key); 
        static int EncryptData(const void *inBytes, size_t inByteSize, const void *password, size_t passwordSize, base_tool::AutoBuffer &out);
        static int DecryptData(const void *inBytes, size_t inByteSize, const void *password, size_t passwordSize, base_tool::AutoBuffer &out);
        static int SignAndBase64(const void *inBytes, size_t inByteSize, const void *password, size_t passwordSize, base_tool::AutoBuffer &out);
        static int BaseToolAesEnc128(void *src, size_t src_size, AutoBuffer &dst, const unsigned char key[16], const unsigned char iv[16]);
        static int BaseToolAesDec128(void *src, size_t src_size, AutoBuffer &dst, unsigned char key[16], unsigned char iv[16]);
    private:
    //    char client_pubkey_md5sum_[33];
    };

}
#endif //BASE_TOOL_SECURITY_CODE_H
