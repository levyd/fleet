#include <iostream>
#define BEGINTEST(name) \
    { \
        std::cout << "Test " << name << "..... "; \
    }
#define ASSERT(conditional) \
    if(! (conditional)) {\
        std::cout << "Failed:" << std::endl; \
        std::cout << "On assert: " << #conditional << std::endl; \
        std::cout << "At " << __FILE__ << ":" << __LINE__ << std::endl; \
        exit(1); \
    }
#define TESTSUCCEED \
    { \
        std::cout << "Succeeded." << std::endl; \
        exit(0); \
    }
