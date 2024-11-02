#include "Header.h"

int main() {
	while (!EscapeState) {
		std::cout << "[ Script Converter 1.0 ]\n";

		std::cout << "Enter security key script file directory.\n>> ";
		getline(std::cin, CMD);

		if (CMD.empty()) {
			system("CLS");
			continue;
		}

		LoadSecurityKey(CMD);
	}

	EscapeState = false;

	while (!EscapeState) {
		std::cout << "[ Script Converter 1.0 ]\nIf you need help, enter command \"man\".\n";

		std::cout << "Enter command.\n>> ";
		getline(std::cin, CMD);

		
		if (CMD.empty()) {
			system("CLS");
			std::cout << "[Message] You can't enter empty command.\n\n";
			continue;
		}

		// convert to security file
		if (CMD == "cnvt -s") {
			system("CLS");

			std::cout << "Enter XML File Name.\n>> ";
			getline(std::cin, Opt);

			system("CLS");
			if (Opt.empty()) {
				std::cout << "[Message] You can't enter empty command.\n\n";
				continue;
			}
			if (Opt == "cancel") continue;

			ConvertToSecurityFile(Opt.c_str());
		}

		// convert to normal file
		else if (CMD == "cnvt -n") {
			system("CLS");

			std::cout << "Enter security File Name.\n>> ";
			getline(std::cin, Opt);

			system("CLS");
			if (Opt.empty()) {
				std::cout << "[Message] You can't enter empty command.\n\n";
				continue;
			}
			if (Opt == "cancel") continue;

			ConvertToNormalFile(Opt.c_str());
		}

		else if (CMD == "man") {
			system("CLS");
			std::cout << "===================== [ Manual ] =====================\n";
			std::cout << "cnvt - Converts the script file type.\n";
			std::cout << "  -s    - Converts the script file to a secure file.\n";
			std::cout << "  -n    - Converts the script file to a xml file.\n";
			std::cout << "  (Parameter example: \"cnvt -s\")\n\n";
		}

		else {
			system("CLS");
			std::cout << "[Message] Unknown command.\n\n";
		}
	}
}