# Input
- Read input from user interactively
- Or read from file
- Input looks like "4 3 5 9 1"
- std::vector<int> getInput();
# Replacement algorithms
- One of FIFO, LRU, LFU, MFU, OPT
- struct TraceResult {
    int hits;
    int misses;
  };
- class ReplacementAlgorithm {
  public:
    const std::string name;
    virtual auto run(const std::vector<int>& input) -> TraceResult = 0;
  protected:
    int pageTableSize;
    ReplacementAlgorithm(int pageTableSize);
  };

  ReplacementAlgorithm(int pageTableSize): pageTableSize(pageTableSize) {}
- class FirstInFirstOut : public ReplacementAlgorithm {
     const auto name = "First In First Out"s;
     override TraceResult run(const std::vector<int>& input);
  };

  auto FirstInFirstOut::run(const std::vector<int>& input) -> TraceResult {
     std::queue<int> pageTable{-1, pageTableSize};
     for (const auto& pageNumber : input) {
        if (std::find(pageTable.cbegin(), pageTable.cend(), pageNumber) == pageTable.cend()) {
            pageTable.pop();
            pageTable.push_back(pageNumber);
        }
     }
  }
# Algorithm
- Start with no pages loaded
    - using PageTable = std::array<int, 4>;
- for (const auto& algorithm : replacementAlgorithms) {
        const auto result =replacementAlgorithm.run(pageTable, input);
        std::cout << "Algorithm: " << algorithm.name << '\n';
        std::cout << "\tHits: " << result.hits << '\n';
        std::cout << "\tMisses: " << result.misses << "\n\n";
  }
-
