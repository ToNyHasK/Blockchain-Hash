#include "header.h"


int main(int argc, char *argv[]) {
    //pradedam laiko matavima
    std::string data;
    int x = 0;
    std::cout << "do you wanna test random character? Type 1 for YES \n"
    << "do you wanna test similar characters? Type 2 for Yes \n"
    << "do you wanna just run the program? Type 0 for yes" << "\n";
    std::cin >> x;
    if (x == 1){
        testRandomWords();
    }else if (x == 0){
        if (argc > 1) {
            for (int i = 1; i <= 2; i++ ) {
            read(data, argv[i]);
            }
        }
    }else if (x == 2) {
        testSimilar();
    }

    return 0;
}