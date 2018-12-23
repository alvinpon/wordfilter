# Word Filter
## Development
### Data Structures
- Array: std::vector.
- Hash Table: std::map & std::set.
### Algorithms
- Sort: std::sort.
- Search: std::binary_search.
### Time and Space Complexity
I write time and space complexity in the comments of the code.
## Test
### Unit Test:
You can create a word filter object to test add_expletive, remove_expletive and filter_expletive.
```
int main(int argc, const char * argv[]) {
    std::size_t option;
    std::string expletive;
    message message1, message2;
    sentence_generator sentence_generator;
    word_filter word_filter;

    message1 = sentence_generator.generate_sentence();

    do {
        std::cout << "Select an option: \n"
                  << "0. Exit\n"
                  << "1. Add expletive\n"
                  << "2. Remove expletive\n"
                  << "3. Filter expletive\n";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (1 <= option and option <= 3) {
            if (option == 1) {
                std::cin >> expletive;
                std::cout << "added " << (word_filter.add_expletive(expletive) ? "successfully" : "unsuccessfully") << std::endl;
            } else if (option == 2) {
                std::cin >> expletive;
                std::cout << "removed " << (word_filter.remove_expletive(expletive) ? "successfully" : "unsuccessfully") << std::endl;
            } else {
                message2 = word_filter.filter_expletive(message1);
                std::cout << message2.expletive_count << " expletives have been filtered.\n"
                          << message2.sentence << std::endl;
            }
        }
    } while(option not_eq 0);

    return 0;
}
```
### Integration Test:
I use 200k sentences which contains at least 100 words that include expletives. After executing the program,
You can see the original expletives and sentence, and filtered expletive and sentence in result.txt. Moreover,
 you can see individual accuracy in result.txt, and integration accuracy in analysis.txt.
```
int main(int argc, const char * argv[]) {
    std::size_t total_expletives = 0, total_filtered_expletives = 0;

    auto start = std::chrono::system_clock::now();
    std::cout << "expletives are being filtered." << std::endl;
    filter(total_expletives, total_filtered_expletives);
    std::cout << "expletives have been filtered." << std::endl;
    auto end = std::chrono::system_clock::now();

    calculate_time(start, end);
    write_analysis(total_expletives, total_filtered_expletives);
    return 0;
}
```
## Run
All you need to do is to use `make` command to create a wordfilter, and then use the `./wordfilter`.
