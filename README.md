# Word Filter
## Development
### Data Structures
- Array: std::vector.
- Hash Table: std::map & std::set.
### Algorithm
- Sort: std::sort.
- Search: std::binary_search.
### Time and Space Complexity
I write time and space complexity in the comments of the code.
## Test
### Unit Test:
You can create a word filter object to test add_expletive, remove_expletive and filter_expletive.
### Integration Test:
I use 200k sentences which contains at least 100 words that include expletives. After executing the program,
You can see the original expletives and sentence, and filtered expletive and sentence in result.txt. Moreover,
 you can see individual accuracy in result.txt, and integration accuracy in analysis.txt.
## Run
All you need to do is to use make command to create a wordfilter, and then use the wordfilter.
```
make
./wordfilter
```
