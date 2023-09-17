#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int byteCount = 256;

void PrintCharacter() {
    // Print characters on the x-axis
    cout << "|" << endl;
    for (int i = 0; i < byteCount; ++i)
    {
        char character = static_cast<char>(i);
        if (character > 32 && character < 127) 
        {
            cout << character;
        }
        else {
            cout << " ";
        }
    }
    cout << "|" << endl;
    cout << endl;
}

void printAllASCIICharacters() {
    int counter = 0;

    cout << "|" << endl;
    for (int i = 0; i <= 255; ++i) {
        // Calculate ASCII value digits
        int hundreds = i / 100;
        if (hundreds == 0) {
            cout << " ";
        }
        else {
            std::cout << hundreds;
        }

    }cout << "|" << endl; cout << endl;

    cout << "|" << endl;
    for (int i = 0; i <= 255; ++i) {
        // Calculate ASCII value digits
        int tens = (i / 10) % 10;

        // Print hundreds, tens, and ones vertically
        if (i < 10) {
            cout << " ";
        }
        else {
            std::cout << tens;
        }
    }cout << "|" << endl; cout << endl;

    cout << "|" << endl;
    for (int i = 0; i <= 255; ++i) {
        // Calculate ASCII value digits
        int ones = i % 10;

        // Print hundreds, tens, and ones vertically
        std::cout << ones;
        counter++;
    }cout << "|" << endl; cout << endl;

}

// Function to generate the histogram
void generateHistogram(const int byteFrequency[], int ratio, bool lflag, bool nflag, bool aflag) {
    int maxFrequency = 0;
    for (int i = 0; i < byteCount; ++i) {
        if (byteFrequency[i] > maxFrequency) {
            maxFrequency = byteFrequency[i];
        }
    }

    // Calculate the scaling factor
    double scale = (lflag) ? static_cast<double> ((log)(maxFrequency) / ratio) : static_cast<double> (maxFrequency / (ratio));

    // Print the top border
    cout << "+";
    for (int i = 0; i < byteCount * 2; ++i) {
        cout << "-";
    }
    cout << "+" << endl;

    for (int row = ratio; row > 0; --row) {
        cout << "|";
        for (int i = 0; i < byteCount; ++i) {
            int scaledValue = (lflag) ? static_cast<int>(ceil(log(byteFrequency[i]) / scale)) : static_cast<int>(ceil(byteFrequency[i] / scale));
            if (scaledValue >= row) {
                cout << "* ";
            }
            else {
                cout << "  ";
            }
        }
        cout << "|" << endl;
    }

    // Print the bottom border
    cout << "+";
    for (int i = 0; i < byteCount * 2; ++i) {
        cout << "-";
    }
    cout << "+" << endl;

    if (nflag)
    {
        PrintCharacter();
    }

    if (aflag)
    {
        printAllASCIICharacters();
    }

}


//void generateLogHistogram(const int byteFrequency[], int ratio) {
//    int maxFrequency = 0;
//    for (int i = 0; i < byteCount; ++i) {
//        if (byteFrequency[i] > maxFrequency) {
//            maxFrequency = byteFrequency[i];
//        }
//    }
//
//    // Calculate the maximum log frequency
//    double maxLogFrequency = 0.0;
//    for (int i = 0; i < byteCount; ++i) {
//        double logValue = log(static_cast<double>(byteFrequency[i]) + 1.0); // Adding 1 to avoid log(0)
//        if (logValue > maxLogFrequency) {
//            maxLogFrequency = logValue;
//        }
//    }
//
//    // Calculate the scaling factor based on the maximum log frequency
//    double scale = (maxLogFrequency > 0.0) ? static_cast<double>(ratio) / maxLogFrequency : 1.0;
//
//    // Print the top border
//    cout << "+";
//    for (int i = 0; i < byteCount * 2; ++i) {
//        cout << "-";
//    }
//    cout << "+" << endl;
//
//    for (int row = ratio; row > 0; --row) {
//        cout << "|";
//        for (int i = 0; i < byteCount; ++i) {
//            double logValue = log(static_cast<double>(byteFrequency[i]) + 1.0);
//            int scaledValue = static_cast<int>(logValue * scale);
//            if (scaledValue >= row) {
//                std::cout << "* ";
//            }
//            else {
//                cout << "  ";
//            }
//        }
//        cout << "|" << endl;
//    }
//
//    // Print the bottom border
//    cout << "+";
//    for (int i = 0; i < byteCount * 2; ++i) {
//        cout << "-";
//    }
//   cout << "+" << endl;
//}


int main(int argc, char* argv[]) {

    string filename = argv[argc - 1];

    bool nflag = false;
    bool aflag = false;
    bool gflag = false;
    bool rflag = false;
    bool lflag = false;
    int ratio = 20;


    for (int i = 1; i < argc; i++) {
        char r = '-r';
        char* arg = argv[i];
        char* result = strchr(arg, r);
        if (strcmp(argv[i], "-n") == 0) {
           nflag = true;
        }
        if (strcmp(argv[i], "-a") == 0) {
            aflag = true;          
        }
        if (strcmp(argv[i], "-g") == 0) {
            gflag = true;        
        }
        if (strcmp(argv[i], "-l") == 0) {
            lflag = true;
        }
        if (result) { //flag.substr(0, 2) == "-r"
            rflag = true; 
            char* intPart = arg + 2; // Skip the "-r" part
            ratio = atoi(intPart); // Convert the remaining part to an integer
        }

    }
  

    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return 1;
    }

    int byteFrequency[byteCount] = { 0 };
    char byte;
    while (file.get(byte)) {
        byteFrequency[static_cast<unsigned char>(byte)]++;
    }

    file.close();

    //if (lflag) {
    //    // Set the scale of histogram
    //    generateHistogram(byteFrequency, ratio, lflag);
    //}
    //else if (rflag) {
    //    generateHistogram(byteFrequency, ratio, lflag);
    //}
    //if (gflag) {
    //    // show no graph
    //    cout << "stat";
    //}
    //if (nflag) {
    //    // shows 0-255 along the X-axis (in three rows)
    //    printAllASCIICharacters();
    //}
    //if (aflag) {
    //    // shows ASCII characters (if printable) along the X-axis
    //    PrintCharacter();
    //}
    //cout << endl;

    if (gflag == false)
    {
        generateHistogram(byteFrequency, ratio, lflag, nflag, aflag);
    }

    int minFrequency = INT_MAX; // Initialize to a large value

    for (int i = 0; i < byteCount; ++i) {
        if (byteFrequency[i] > 0 && byteFrequency[i] < minFrequency) {
            minFrequency = byteFrequency[i];
        }
    }

    int maxFrequency = 0;
    char maxOccurringChar = '\0'; // Initialize to null character

    for (int i = 0; i < byteCount; ++i) {
        if (byteFrequency[i] > maxFrequency) {
            maxFrequency = byteFrequency[i];
            maxOccurringChar = static_cast<char>(i); // Convert index to character
        }
    }
    int sumFrequency = 0;

    for (int i = 0; i < byteCount; ++i) {
        sumFrequency += byteFrequency[i];
    }

    double averageValue = static_cast<double>(sumFrequency) / 256.0;


    cout << "MIN:" << minFrequency << " Max  (" << maxOccurringChar << "):" << maxFrequency << " AVG:" << averageValue << endl; //Min:NNNNNNNNN Max (CCC):NNNNNNNNN AVG:XXXXXXXXX DEV:XXXXXXXXX

    return 0;
}