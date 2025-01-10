#include <fstream>
#include "json.hpp" // Include nlohmann/json header
#include "teams.hpp" // Include nlohmann/json header

using json = nlohmann::json;

// Function to load students from a JSON file
vector<Member> setupJSON(const string& filePath) {
    vector<Member> students;

    // Open the file
    fstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filePath);
    }

    // Parse the JSON file
    json jsonData;
    file >> jsonData;

    // Read data into the list
    for (const auto& item : jsonData) {
        students.push_back(Member{item.at("name").get<string>()});
        NUMBER_OF_STUDENTS++;
    }

    return students;
}
