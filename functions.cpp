//
// Created by Tomas on 10/3/2019.
//
#include "header.h"



bool checkStream(const std::ifstream& file) {
    // Check if you can open the file
    if (!file.is_open()) {
        std::cout << "Error while opening a file" << std::endl;
        return false;
    }
    return true;
}

std::string hashFunc(std::string text = "") {
    unsigned int sum = 2;
    if (text == "") {
        text += std::to_string(sum);
    }
    for (auto i : text) {
            unsigned int val = int(i);
            sum += val * val;
            sum += (~val % ~sum);
            //sum *= val;
            sum +=  sum << 1;
            sum %= (sum & val) - (val + 13) * (val / 2);
    }
    sum = sum >> 1;
    std::stringstream ss;
    ss << std::hex << sum;
    std::string rez = (ss.str());
    std::string newHex = "";
    while (rez.length() != 20) {
        for (unsigned int ch : rez) {
            ch = (ch +~ rez.length()) * sum >> 2;
            ch += sum | ch;
            ch += ch >> 2;
            ss.str("");
            ss << std::hex << ch;
            rez += ss.str();
        }
        if (rez.length() > 20) {
            rez = rez.substr(0, 20);
        }
    }
    //std::ofstream of("rezultatas.txt");
    //of << rez << "\n";
    std::cout << rez << "\n";
    return rez;
}

void read(std::string &text, char *string) {

    std::ifstream file(string);
    bool hasFileBeenRead = false;
    if (!checkStream(file)) {

        hashFunc(string);

    } else { Timer t;
        while (std::getline(file, text)) {
            //std::cout << text << '\n';
            //std::string file_content {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
            hasFileBeenRead = true;
            hashFunc(text);

        }

        std::cout << "Elapsed time(HashFunc): " << t.elapsed() << " s\n";
        t.reset();
        if (!hasFileBeenRead) {
            hashFunc("");
        }
    }
}
// kodas pasiskolintas is https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string randomString(const int length) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string result("", length);

    for (int i = 0; i < length; ++i) {
        result[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return result;
}

void testRandomWords() {
    unsigned int collisions = 0;

    std::cout << "Random words collision test" << "\n";

    for (int i = 0; i < RANDOM_COUNT; i++) {
        std::string word1 = randomString(RANDOM_LENGTH);
        std::string word2 = randomString(RANDOM_LENGTH);

        if (hashFunc(word1) == hashFunc(word2)) {
            collisions++;
        }
    }
    std::cout << "Collisions found in word test: " << collisions << "\n";
}
// Toliau einantis kodas yra Emilio Baliukonio, labai dekoju jam
std::string binary(std::string word) {
    std::string binaryS = "";
    for (char& _char : word ) {
        binaryS += std::bitset<8>(_char).to_string();
    }
    return binaryS;
}

double compare (std::string in1, std::string in2) {
    const size_t length = std::min(in1.length(), in2.length());
    unsigned int identical = 0;

    for (int i = 0; i < length; i++) {
        if (in1[i] == in2[i]) {
            identical++;
        }
    }
    return 1.0 - (double)identical / length;
}

void testSimilar() {
    unsigned int collisions = 0;
    double minDif = 1.0;
    double totalDif = 0;
    double maxDif = 0;

    std::cout << "Similar words collision test" << "\n";

    for (int i = 0; i < SIMILAR_COUNT; i++) {
        const std::string word1=randomString(SIMILAR_LENGHT);
        std::string word2;

        do {
            const unsigned int letterToChange = rand() % SIMILAR_LENGHT;
            const std::string newLetter = randomString(1);
            word2 = word1;
            word2[letterToChange] = newLetter[0];
        } while (word1 == word2);

        const std::string hash1 = hashFunc(word1);
        const std::string hash2 = hashFunc(word2);

        if (hash1 == hash2) {
            collisions++;
        }

        const std::string binary1 = binary(hash1);
        const std::string binary2 = binary(hash2);

        const double difference = compare(binary1, binary2);
        totalDif += difference;

        if (difference < minDif) {
            minDif = difference;
        } else if (difference > maxDif) {
            maxDif = difference;
        }
    }

    std::cout << "Collisions: " << collisions << "\n";
    std::cout << "Minimum difference: " << minDif * 100 << "\n";
    std::cout << "Maximum difference: " << maxDif * 100 << "\n";
    std::cout << "Average difference: " << (totalDif / SIMILAR_COUNT) * 100 << "\n";

}


