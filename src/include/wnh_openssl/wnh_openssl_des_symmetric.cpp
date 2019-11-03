#include "wnh_openssl.h"

string wnh_openssl::des_encrypt(const string &clearText, const string &key) // 加密 ecb模式, des对称加解密
{
    //WNHINFO("clearText=" << clearText);
    string cipherText; // 密文

    DES_cblock keyEncrypt;
    memset(keyEncrypt, 0, 8);

    // 构造补齐后的密钥
    if (key.length() <= 8)
        memcpy(keyEncrypt, key.c_str(), key.length());
    else
        memcpy(keyEncrypt, key.c_str(), 8);
    //WNHINFO("key=" << key);

    // 密钥置换
    DES_key_schedule keySchedule;
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);

    // 循环加密，每8字节一次
    const_DES_cblock inputText;
    DES_cblock outputText;
    std::vector<unsigned char> vecCiphertext;
    unsigned char tmp[8];

    for (unsigned int i = 0; i < clearText.length() / 8; i++)
    {
        memcpy(inputText, clearText.c_str() + i * 8, 8);
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCiphertext.push_back(tmp[j]);
    }

    if (clearText.length() % 8 != 0)
    {
        int tmp1 = clearText.length() / 8 * 8;
        int tmp2 = clearText.length() - tmp1;
        memset(inputText, 0, 8);
        memcpy(inputText, clearText.c_str() + tmp1, tmp2);
        // 加密函数
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_ENCRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCiphertext.push_back(tmp[j]);
    }

    cipherText.clear();
    cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());

    return cipherText;
}

string wnh_openssl::des_decrypt(const string &cipherText, const string &key) // 解密 ecb模式, des对称加解密
{
    string clearText; // 明文

    DES_cblock keyEncrypt;
    memset(keyEncrypt, 0, 8);

    if (key.length() <= 8)
        memcpy(keyEncrypt, key.c_str(), key.length());
    else
        memcpy(keyEncrypt, key.c_str(), 8);

    DES_key_schedule keySchedule;
    DES_set_key_unchecked(&keyEncrypt, &keySchedule);

    const_DES_cblock inputText;
    DES_cblock outputText;
    std::vector<unsigned char> vecCleartext;
    unsigned char tmp[8];

    for (unsigned int i = 0; i < cipherText.length() / 8; i++)
    {
        memcpy(inputText, cipherText.c_str() + i * 8, 8);
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCleartext.push_back(tmp[j]);
    }

    if (cipherText.length() % 8 != 0)
    {
        int tmp1 = cipherText.length() / 8 * 8;
        int tmp2 = cipherText.length() - tmp1;
        memset(inputText, 0, 8);
        memcpy(inputText, cipherText.c_str() + tmp1, tmp2);
        // 解密函数
        DES_ecb_encrypt(&inputText, &outputText, &keySchedule, DES_DECRYPT);
        memcpy(tmp, outputText, 8);

        for (int j = 0; j < 8; j++)
            vecCleartext.push_back(tmp[j]);
    }

    clearText.clear();
    clearText.assign(vecCleartext.begin(), vecCleartext.end());

    return clearText;
}
