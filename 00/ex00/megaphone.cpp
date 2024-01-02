#include <cstdlib>
#include <cstring>
#include <iostream>

class Megaphone {
    public:
        // default constructor
        Megaphone();
        // constructor with argument
        Megaphone(const int size, const char **voice);
        // copy constructor
        Megaphone(const Megaphone& m);
        // destructor
        ~Megaphone(void);
        // copy assignment operator
        const Megaphone& operator=(const Megaphone& m);

    public:
        void print_voice();

    private:
        void copy_voice_(const char **voice);
        void convert_voice_to_uppercase_();
        void destroy_voice_();

    private:
        int size_;
        char **voice_;
};

Megaphone::Megaphone() {
    size_ = 0;
    voice_ = NULL;
    std::cerr << "(call default constructor)" << std::endl;
}

Megaphone::Megaphone(const int size, const char **voice) {
    size_ = size;
    copy_voice_(voice);
    convert_voice_to_uppercase_();
    std::cerr << "(call constructor with argument)" << std::endl;
}

Megaphone::Megaphone(const Megaphone& m) {
    size_ = m.size_;
    if (m.voice_ == NULL) {
        voice_ = NULL;
    } else {
        copy_voice_((const char **)m.voice_);
    }
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

        size_ = m.size_;
        if (m.voice_ == NULL) {
            voice_ = NULL;
        } else {
            copy_voice_((const char **)m.voice_);
        }
    }
    std::cerr << "(call copy assignment operator)" << std::endl;
    return *this;
}

void Megaphone::print_voice() {
    if (voice_ == NULL) {
        return ;
    }
    for (int i = 0; i < size_; i++) {
        std::cout << voice_[i] << " ";
    }
    std::cout << std::endl;
}

void Megaphone::copy_voice_(const char **src) {
    voice_ = new char*[size_];
    for (int i = 0; i < size_; i++) {
        voice_[i] = new char[strlen(src[i]) + 1];
        strcpy(voice_[i], src[i]);
    }
}

void Megaphone::convert_voice_to_uppercase_() {
    for (int i = 0; i < size_; i++) {
        char *s = voice_[i];
        while (*s) {
            *s = toupper(*s);
            s++;
        }
    }
}

void Megaphone::destroy_voice_() {
    for (int i = 0; i < size_; i++) {
        delete[] voice_[i];
    }
    delete[] voice_;
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
        Megaphone m2(argc - 1, (const char **)&argv[1]);
        m2.print_voice();
    }
    std::cout << "-------------" << std::endl;
    {
        Megaphone m3, m4(argc - 1, (const char **)&argv[1]);
        m3 = m4;
        m3.print_voice();
        m4.print_voice();

        Megaphone m5 = m3;
        m5.print_voice();
    }
    std::cout << "-------------" << std::endl;
    return EXIT_SUCCESS;
}
