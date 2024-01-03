#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

class Megaphone {
    public:
        // default constructor
        Megaphone();
        // constructor with argument
        explicit Megaphone(const std::vector<std::string>& voice);
        // copy constructor
        Megaphone(const Megaphone& m);
        // destructor
        ~Megaphone(void);
        // copy assignment operator
        const Megaphone& operator=(const Megaphone& m);

    public:
        void print_voice();

    private:
        void copy_voice_(const std::vector<std::string>& voice);
        void convert_voice_to_uppercase_();
        void destroy_voice_();

    private:
        std::vector<std::string> voice_;
};

Megaphone::Megaphone() {
    std::cerr << "(call default constructor)" << std::endl;
}

Megaphone::Megaphone(const std::vector<std::string>& voice) {
    copy_voice_(voice);
    convert_voice_to_uppercase_();
    std::cerr << "(call constructor with argument)" << std::endl;
}

Megaphone::Megaphone(const Megaphone& m) {
    copy_voice_(m.voice_);
    std::cerr << "(call copy constructor)" << std::endl;
}

Megaphone::~Megaphone(void) {
    destroy_voice_();
    std::cerr << "(call destructor)" << std::endl;
}

const Megaphone& Megaphone::operator=(const Megaphone& m) {
    // prevent self-assignment
    if (this != &m) {
        destroy_voice_();
        copy_voice_(m.voice_);
    }
    std::cerr << "(call copy assignment operator)" << std::endl;
    return *this;
}

void Megaphone::print_voice() {
    if (voice_.empty()) {
        return ;
    }
    for (size_t i = 0; i < voice_.size(); i++) {
        std::cout << voice_[i] << " ";
    }
    std::cout << std::endl;
}

void Megaphone::copy_voice_(const std::vector<std::string>& src) {
    voice_ = src;
}

void Megaphone::convert_voice_to_uppercase_() {
    for (size_t i = 0; i < voice_.size(); i++) {
        for (size_t j = 0; j < voice_[i].size(); j++) {
            voice_[i][j] = std::toupper(voice_[i][j]);
        }
    }
}

void Megaphone::destroy_voice_() {
    voice_.clear();
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "-------------" << std::endl;
    {
        Megaphone m1;
        m1.print_voice();
    }
    std::cout << "-------------" << std::endl;
    {
        std::vector<std::string> args(argv + 1, argv + argc);
        Megaphone m2(args);
        m2.print_voice();
    }
    std::cout << "-------------" << std::endl;
    {
        std::vector<std::string> args;
        args.push_back("aaa");

        Megaphone m3, m4(args);
        m3 = m4;
        m3.print_voice();
        m4.print_voice();

        Megaphone m5 = m3;
        m5.print_voice();
    }
    std::cout << "-------------" << std::endl;
    return EXIT_SUCCESS;
}
