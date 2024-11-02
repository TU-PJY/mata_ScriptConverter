#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "tinyxml/tinyxml.h"
#include "cryptopp/aes.h" 
#include "cryptopp/filters.h"
#include "cryptopp/modes.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <filesystem>
#include <string>
#include <cctype>
using namespace CryptoPP;

extern bool EscapeState;
extern std::string CMD, Opt;
extern std::string LoadedFileName;
extern std::string Extension;

extern TiXmlDocument PasswdDoc;
extern TiXmlElement* PasswdRoot;
extern TiXmlElement* CatAES, * CatIV;

extern TiXmlDocument Doc;
extern TiXmlElement* Root;

extern unsigned char AES_KEY[16];
extern unsigned char IV_KEY[16];

std::string Encrypt(const std::string& PlainText, const byte Key[], const byte IV[]);
std::string Decrypt(const std::string& CipherText, const byte Key[], const byte IV[]);
void ConvertToSecurityFile(const char* FileName);
void ConvertToNormalFile(const char* FileName);
void LoadSecurityKey(std::string FileDir);
