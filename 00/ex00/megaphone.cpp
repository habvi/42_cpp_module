#include <cstdlib>
#include <iostream>
#include <string>

class Megaphone {
  public:
	// default constructor
	Megaphone();
	// constructor with argument
	Megaphone(const size_t size, const std::string *voice);
	// copy constructor
	Megaphone(const Megaphone &m);
	// destructor
	~Megaphone();
	// copy assignment operator
	Megaphone &operator=(const Megaphone &m);

  public:
	void print_voice();

  private:
	void copy_voice_(const std::string *voice);
	void convert_voice_to_uppercase_();
	void destroy_voice_();

  private:
	size_t       size_;
	std::string *voice_;
};

Megaphone::Megaphone() {
	size_  = 0;
	voice_ = NULL;
	// std::cerr << "(call default constructor)" << std::endl;
}

Megaphone::Megaphone(const size_t size, const std::string *voice) {
	size_ = size;
	copy_voice_(voice);
	convert_voice_to_uppercase_();
	// std::cerr << "(call constructor with argument)" << std::endl;
}

Megaphone::Megaphone(const Megaphone &m) {
	size_ = m.size_;
	if (m.voice_ == NULL) {
		voice_ = NULL;
	} else {
		copy_voice_(m.voice_);
	}
	// std::cerr << "(call copy constructor)" << std::endl;
}

Megaphone::~Megaphone() {
	destroy_voice_();
	// std::cerr << "(call destructor)" << std::endl;
}

Megaphone &Megaphone::operator=(const Megaphone &m) {
	// prevent self-assignment
	if (this != &m) {
		destroy_voice_();

		size_ = m.size_;
		if (m.voice_ == NULL) {
			voice_ = NULL;
		} else {
			copy_voice_(m.voice_);
		}
	}
	// std::cerr << "(call copy assignment operator)" << std::endl;
	return *this;
}

void Megaphone::print_voice() {
	if (voice_ == NULL) {
		return;
	}
	for (size_t i = 0; i < size_; i++) {
		std::cout << voice_[i] << " ";
	}
	std::cout << std::endl;
}

void Megaphone::copy_voice_(const std::string *src) {
	voice_ = new std::string[size_];
	for (size_t i = 0; i < size_; i++) {
		voice_[i] = src[i];
	}
}

void Megaphone::convert_voice_to_uppercase_() {
	for (size_t i = 0; i < size_; i++) {
		for (size_t j = 0; j < voice_[i].size(); j++) {
			voice_[i][j] = std::toupper(voice_[i][j]);
		}
	}
}

void Megaphone::destroy_voice_() {
	delete[] voice_;
	voice_ = NULL;
}

static std::string *convert_args(const size_t size, const char **argv) {
	std::string *voice = new std::string[size];
	for (size_t i = 0; i < size; i++) {
		voice[i] = argv[i];
	}
	return voice;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cerr << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return EXIT_FAILURE;
	}

	std::string *voice = convert_args(argc - 1, (const char **)&argv[1]);

	// std::cout << "-------------" << std::endl;
	// {
	//     Megaphone m1;
	//     m1.print_voice();
	// }
	// std::cout << "-------------" << std::endl;
	{

		Megaphone m2(argc - 1, voice);
		m2.print_voice();
	}
	// std::cout << "-------------" << std::endl;
	// {
	//     Megaphone m3, m4(argc - 1, voice);
	//     m3 = m4;
	//     m3.print_voice();
	//     m4.print_voice();

	//     Megaphone m5 = m3;
	//     m5.print_voice();
	// }
	// std::cout << "-------------" << std::endl;

	delete[] voice;
	return EXIT_SUCCESS;
}
