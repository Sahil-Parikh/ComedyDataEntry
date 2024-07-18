#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>
using namespace std;

struct Comedian {
    string name;
    vector<string> notes;
    vector<string> date;
    vector<int> episode;
};


// Function to read comedians data from file into a vector
vector<Comedian> readComediansFromFile(const string& filename) {
    vector<Comedian> comedians;
    ifstream file(filename);
    if (file.is_open()) {
        Comedian comedian;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            ss >> comedian.name;
            string date;
            int episode;
            while (ss >> date >> episode) {
                comedian.date.push_back(date);
                comedian.episode.push_back(episode);
                if (ss.peek() == ',') ss.ignore();
            }
            if (getline(file, line)) {
                comedian.notes.push_back(line);
            }
            comedians.push_back(comedian);
        }
        /*
        while (file >> comedian.name >> comedian.date >> comedian.episode >> ws && getline(file, comedian.notes)) {
            comedians.push_back(comedian);
        }
        */
        file.close();
    }
    return comedians;
}

// Function to write comedians data to file
void writeComediansToFile(const vector<Comedian>& comedians, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& comedian : comedians) {
            file << setw(20) << left << comedian.name;  // Write the name
            for (size_t i = 0; i < comedian.date.size(); ++i) {  // Iterate through dates
                file << setw(10) << comedian.date[i] << "   " << setw(5) << comedian.episode[i];  // Write date and episode
            }
            file << "\n";  // New line
            for (const auto& note : comedian.notes) {  // Iterate through notes
                file << note << "\n";  // Write each note
            }
            file << "\n";  // New line
            /*
            file << setw(20) << left << comedian.name << setw(10) << comedian.date << "   " << setw(5) << comedian.episode << "\n" << comedian.notes << "\n\n";
            */
        }
        file.close();
    }
}

// Function to read comedians data from CSV file into a vector
vector<Comedian> readComediansFromCSV(const string& filename) {
    vector<Comedian> comedians;
    ifstream file(filename);
    if (file.is_open()) {
        string line;                // Temporary line for reading file content

        // Ignore the header line
        getline(file, line);

        while (getline(file, line)) {  // Read line by line
            stringstream ss(line);     
            string name, date, notes;  
            int episode;              

            getline(ss, name, ',');     
            getline(ss, date, ',');   
            ss >> episode;              
            ss.ignore();              
            getline(ss, notes, '"');  
            if (ss.peek() == '"') {     // Check if there's an opening quote for notes
                getline(ss, notes, '"'); // Read the notes until the closing quote
            } else {
                getline(ss, notes);     // else read the rest of the line
            }

            // Check if the comedian already exists in the vector
            bool found = false;
            for (auto& comedian : comedians) {
                if (comedian.name == name) {
                    // Add the new appearance data
                    comedian.date.push_back(date);
                    comedian.episode.push_back(episode);
                    comedian.notes.push_back(notes);
                    found = true;
                    break;
                }
            }

            // If the comedian doesn't exist, add a new entry
            if (!found) {
                Comedian comedian;
                comedian.name = name;
                comedian.date.push_back(date);
                comedian.episode.push_back(episode);
                comedian.notes.push_back(notes);
                comedians.push_back(comedian);
            }
        /*
        string line;
        while (getline(file, line)) {
            stringstream ss(line);     // string stream from the line
            Comedian comedian;         
            getline(ss, comedian.name, ',');  // Read the name until comma
            string date;                    
            int episode;                    
            while (getline(ss, date, ',') && ss >> episode) { 
                comedian.date.push_back(date); 
                comedian.episode.push_back(episode);  
                if (ss.peek() == ',') ss.ignore();  
            }
            if (getline(file, line)) {      
                comedian.notes.push_back(line);  
            }
            comedians.push_back(comedian);  
            */
            /*
            stringstream ss(line);
            string name, notes, date;
            int episode;
            getline(ss, name, ',');
            getline(ss, date, ',');
            ss >> episode;
            ss.ignore(); // Ignore the comma
            getline(ss, notes);
            comedians.push_back({name, notes, date, episode});
            */  
        }
        file.close();
    }
    return comedians;
}

// Function to write comedians data to CSV file
void writeComediansToCSV(const vector<Comedian>& comedians, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        // Write the header
        file << "COMEDIAN,DATE,EPISODE NUMBER,NOTES" << endl;
        for (const auto& comedian : comedians) {
            for (size_t i = 0; i < comedian.date.size(); ++i) {
                file << comedian.name << ","
                     << comedian.date[i] << ","
                     << comedian.episode[i] << ","
                     << "\"" << comedian.notes[i] << "\"" << endl;  // Enclose notes in quotes to handle commas
            }

        /*
        for (const auto& comedian : comedians) {
            file << comedian.name;  // Write the name
            for (size_t i = 0; i < comedian.date.size(); ++i) {  // Iterate through dates
                file << "," << comedian.date[i] << "," << comedian.episode[i];  // Write date and episode
            }
            file << ",";  // Comma separator
            for (const auto& note : comedian.notes) {  // Iterate through notes
                file << note << ";";  // Write each note
            }
            file << endl;  // New line
            */
            /*
            file << comedian.name << "," << comedian.date << "," << comedian.episode << "," << comedian.notes << endl;
            */
        }
        file.close();
    }
}



int main() {
    string filename = "comedians.csv";
    vector<Comedian> comedians = readComediansFromCSV(filename);

    string date;
    int episode;
    cout << "Enter date: ";
    cin >> date;
    cout << "Enter episode: ";
    cin >> episode;

    string name;
    cout << "Enter comedian's name (or 'quit' to exit): ";
    cin.ignore();
    getline(cin, name);

    string notes;
    while (name != "quit") {
        bool found = false;  // Flag if comedian is found
        for (auto& comedian : comedians) {  
            if (comedian.name == name) { 
                cout << "\nComedian found!\n";
                cout << "\nName: " << comedian.name; 
                for (size_t i = 0; i < comedian.date.size(); ++i) {  
                    cout << "\nDate: " << comedian.date[i] << "\nEpisode: " << comedian.episode[i] << "\nNotes: " << comedian.notes[i] << endl;  // Print comedian details
                }
                found = true;  // Set found flag to true
                cout << "Add more notes (y/n)? ";  // Prompt user to add more notes
                char choice;  
                cin >> choice;  
                if (choice == 'y') {  
                    cout << "Enter additional notes: ";  
                    cin.ignore();  
                    getline(cin, notes);  
                    comedian.date.push_back(date);  
                    comedian.episode.push_back(episode);  
                    comedian.notes.push_back(notes);  
                }
                break; 
            }
        }
        if (!found) {  
            cout << "Comedian not found. Adding new entry...\nEnter notes for " << name << ": "; 
            getline(cin, notes);  
            comedians.push_back({ name, {notes}, {date}, {episode} }); 
        }

        cout << "Enter comedian's name (or 'quit' to exit): ";  
        getline(cin, name);  
        /*
        bool found = false;
        bool temp = false;
        for (auto& comedian : comedians) {
            for (auto& comedian : comedians) {
                if (comedian.name == name) {
                    if (temp == false)
                    {
                        cout << "\nComedian found!\n";
                        temp = true;
                    }
                    cout << "\nName: " << comedian.name << "\nDate: " << comedian.date << "\nEpisode: " << comedian.episode << "\nNotes: \n" << comedian.notes << endl << endl;
                    found = true;
                }
            }
            if (comedian.name == name) {
                //found = true;
                //cout << "\nComedian found!\n\nName: " << comedian.name << "\nDate: " << comedian.date << "\nEpisode: " << comedian.episode << "\nNotes: \n" << comedian.notes << endl << endl;
                cout << "Add more notes (y/n)? ";
                char choice;
                cin >> choice;
                if (choice == 'y') {
                    cout << "Enter additional notes: ";
                    cin.ignore();
                    getline(cin, notes);
                    comedian.notes +=  "\n" + name + "," + date + "," + to_string(episode) + "," + notes;
                }
                break;
            }
        }
        if (!found) {
            cout << "Comedian not found. Adding new entry...\nEnter notes for " << name << ": ";
            // cin.ignore();
            getline(cin, notes);
            comedians.push_back({name, notes, date, episode});
        }

        cout << "Enter comedian's name (or 'quit' to exit): ";
      //  cin.ignore();
        getline(cin, name);
        if (name == "quit") {
            break;
        }
        */
    }

    writeComediansToCSV(comedians, filename);

    return 0;
}