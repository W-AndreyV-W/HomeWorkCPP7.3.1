#include <iostream>
#include <fstream>
#include <windows.h>

class LogCommand {

public:

    virtual ~LogCommand() = default;

    virtual void print(const std::string& message) = 0;
};

class LogPrintConsole : public LogCommand {

public:

    void print(const std::string& message) noexcept override {

        std::cout << message << std::endl;
    }
};

class LogPrintFile : public LogCommand {

public:

    explicit LogPrintFile(std::ostream& _out) : out(_out) {}

    void print(const std::string& message) noexcept override {

        out << message << std::endl;
    }

private:

    std::ostream& out;
};

void oid_print(LogCommand& lc,const std::string& text) {

    lc.print(text);
}

int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string text("Hello World!");
    std::fstream file("out.txt", std::ios::app);

    LogPrintConsole log_print_console;
    oid_print(log_print_console, text);

    if (file.is_open()) {

        LogPrintFile log_print_file(file);
        oid_print(log_print_file, text);
    }
    else {

        std::cout << "Ошибка открытия файла" << std::endl;
    }
}