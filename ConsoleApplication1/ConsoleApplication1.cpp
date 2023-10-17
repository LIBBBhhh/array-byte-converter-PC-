//all open code

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdexcept>

#include <ctime>
#include <iomanip>

std::string convertToHexString(const char* data, size_t size) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    for (size_t i = 0; i < size; ++i) {
        oss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(data[i]));
    }

    return oss.str();
}

void generateByteArrayHeader(const std::string& filename, const std::string& arrayName) {
    std::ifstream inputFile(filename, std::ios::binary);

    if (!inputFile) {
        throw std::runtime_error("Failed to open input file.");
    }

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(inputFile), {});

    std::ofstream outputFile("converted_arry.h");

    if (!outputFile) {
        throw std::runtime_error("Failed to create output file.");
    }
    outputFile << "// Made by Aray-Size-converter\n";
    outputFile << "// Dev: n1kryyy\n";
    std::time_t currentTime = std::time(nullptr);
    struct std::tm localTime;
    localtime_s(&localTime, &currentTime);
    outputFile << "// Time: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "\n";

    outputFile << "unsigned char " << arrayName << "[] = { \n";

    for (size_t i = 0; i < buffer.size(); ++i) {
        outputFile << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(buffer[i]) << ", ";

        if ((i + 1) % 16 == 0) {
            outputFile << "\n";
        }
    }

    outputFile << "};" << std::endl;

    // ...

    
    inputFile.close();
    outputFile.close();
}
//outputFile
int main() {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    std::string arrayName;
    std::cout << "unsigned name: ";
    std::cin >> arrayName;

    

    

    try {
        generateByteArrayHeader(filename, arrayName);
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}