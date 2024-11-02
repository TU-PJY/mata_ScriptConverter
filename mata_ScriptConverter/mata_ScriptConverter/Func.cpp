#include "Header.h"

bool EscapeState;
std::string CMD, Opt;
std::string LoadedFileName;
std::string Extension = ".xml";

TiXmlDocument PasswdDoc;
TiXmlElement* PasswdRoot;
TiXmlElement* CatAES, * CatIV;

TiXmlDocument Doc;
TiXmlElement* Root;

unsigned char AES_KEY[16];
unsigned char IV_KEY[16];

std::string Encrypt(const std::string& PlainText, const byte Key[], const byte IV[]) {
	std::string CipherText;

	try {
		CBC_Mode<AES>::Encryption Encryption;
		Encryption.SetKeyWithIV(Key, AES::DEFAULT_KEYLENGTH, IV);
		StringSource(PlainText, true, new StreamTransformationFilter(Encryption, new StringSink(CipherText)));
	}
	catch (const Exception& E) {
		std::cerr << E.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	return CipherText;
}

std::string Decrypt(const std::string& CipherText, const byte Key[], const byte IV[]) {
	std::string PlainText;

	try {
		CBC_Mode<AES>::Decryption Decryption;
		Decryption.SetKeyWithIV(Key, AES::DEFAULT_KEYLENGTH, IV);
		StringSource(CipherText, true, new StreamTransformationFilter(Decryption, new StringSink(PlainText)));
	}
	catch (const Exception& E) {
		std::cerr << E.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	return PlainText;
}

void ConvertToSecurityFile(const char* FileName) {
	if (!Doc.LoadFile(FileName)) {
		std::cout << "[Message] Failed to load script file \"" << Opt.c_str() << "\".\n\n";
		return;
	}

	std::cout << "[Message] Loaded script file: \"" << FileName << "\".\n";
	LoadedFileName = FileName;

	size_t pos = LoadedFileName.find(Extension);
	if (pos != std::string::npos)
		LoadedFileName.erase(pos, Extension.length());

	TiXmlPrinter Printer;
	Doc.Accept(&Printer);

	std::string XML_String = Printer.CStr();
	std::string EncryptedXML = Encrypt(XML_String, AES_KEY, IV_KEY);

	std::ofstream ExportFile(LoadedFileName, std::ios::binary);
	ExportFile.write(EncryptedXML.c_str(), EncryptedXML.size());
	ExportFile.close();

	Doc.Clear();

	system("CLS");
	std::cout << "[Message] Conversion to a secure file has been completed.\n\n";
}

void ConvertToNormalFile(const char* FileName) {
	std::ifstream EncryptedFile(FileName, std::ios::binary);
	if (!EncryptedFile) {
		system("CLS");
		std::cout << "[Message] Failed to open security file: \"" << FileName << "\".\n\n";
		return;
	}
	LoadedFileName = FileName;
	LoadedFileName += Extension;

	std::string EncryptedContent((std::istreambuf_iterator<char>(EncryptedFile)), std::istreambuf_iterator<char>());
	EncryptedFile.close();

	std::string DecryptedXML = Decrypt(EncryptedContent, AES_KEY, IV_KEY);
	Doc.Parse(DecryptedXML.c_str());

	if (Doc.Error()) {
		system("CLS");
		std::cout << "[Message] Failed to parse security file: \"" << FileName << "\".\n\n";
		return;
	}

	Doc.SaveFile(LoadedFileName.c_str());
	Doc.Clear();

	system("CLS");
	std::cout << "[Message] Conversion to a normal file has been completed.\n\n";
}

void LoadSecurityKey(std::string FileDir) {
	if (!PasswdDoc.LoadFile(FileDir.c_str())) {
		system("CLS");
		std::cout << "[Message] Can not find \"" << FileDir << "\".\n\n";
		return;
	}

	PasswdRoot = PasswdDoc.RootElement();
	CatAES = PasswdRoot->FirstChildElement("AES");
	CatIV = PasswdRoot->FirstChildElement("IV");

	strcpy(reinterpret_cast<char*>(AES_KEY), CatAES->Attribute("string"));
	strcpy(reinterpret_cast<char*>(IV_KEY), CatIV->Attribute("string"));

	system("CLS");
	std::cout << "[Message] Security key script file loaded: \"" << FileDir << "\".\n\n";

	EscapeState = true;
}
