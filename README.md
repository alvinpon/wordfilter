# Word Filter
## Development
### Data Structures
- Array:
    - std::array
    - std::vector
- Hash Table:
    - std::set
- Queue
    - std::queue

### Algorithms

### Time and Space Complexity
The explanation for time complexity is within function definition of filter_expletives member function.

## Test
### Unit Test:
You can create a word_filter object to test add_expletive, remove_expletive and filter_expletive.
### Integration Test:
I use 200k sentences which contains at least 100 words generated randomly by uniform distribution. After executing the program,
you can see how many expletives are filtered out in the result.txt and the execution time on your screen.
## Run
All you need to do is to use `make` command to create a wordfilter, and then use the `./wordfilter`.

![result](https://github.com/alvinpon/wordfilter/blob/master/result.png)
