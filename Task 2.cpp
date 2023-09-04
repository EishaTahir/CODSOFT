#include <iostream>
#include <string>
#include <vector>

// Function to get a response based on user input
std::string getResponse(const std::string& userInput) {
    // Define patterns and corresponding responses
    std::vector<std::pair<std::string, std::string>> rules = {
        {"hello", "Hello! How can I assist you today?"},
        {"how are you", "I'm just a computer program, but thanks for asking! How can I help you?"},
        {"what is your name", "I'm a simple chatbot. What can I do for you?"},
        {"bye", "Goodbye! Have a great day!"}
    };

    // Convert user input to lowercase for case-insensitive matching
    std::string lowercaseInput = userInput;
    for (char& c : lowercaseInput) {
        c = tolower(c);
    }

    // Check if the input matches any predefined patterns
    for (const auto& rule : rules) {
        if (lowercaseInput.find(rule.first) != std::string::npos) {
            return rule.second; // Return the corresponding response
        }
    }

    // If no matching pattern is found, provide a default response
    return "I'm not sure how to respond to that. Can you please rephrase your question?";
}

int main() {
    std::cout << "Simple Chatbot: Type 'bye' to exit." << std::endl;
    while (true) {
        std::string userInput;
        std::cout << "You: ";
        std::getline(std::cin, userInput);

        // Exit the chatbot if the user types 'bye'
        if (userInput == "bye") {
            std::cout << "Chatbot: Goodbye! Have a great day!" << std::endl;
            break;
        }

        std::string response = getResponse(userInput);
        std::cout << "Chatbot: " << response << std::endl;
    }

    return 0;
}
