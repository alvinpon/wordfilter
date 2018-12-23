wordfilter: main.cpp sentence_generator.cpp sentence_generator.hpp word_filter.cpp word_filter.hpp
	g++ -o wordfilter -std=c++11 main.cpp sentence_generator.cpp word_filter.cpp
