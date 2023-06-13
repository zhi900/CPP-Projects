#include <iostream>
#include <string>
#include <algorithm>

enum class CardType {
    INVALID,
    VISA,
    MASTERCARD,
    AMERICAN_EXPRESS,
    DISCOVER
};

std::pair<bool, CardType> validateCreditCard(const std::string& cardNumber) {
    std::string sanitizedNumber = cardNumber;

    // Remove any non-digit characters
    sanitizedNumber.erase(
        std::remove_if(
            sanitizedNumber.begin(),
            sanitizedNumber.end(),
            [](char c) {
                return !std::isdigit(c);
            }
        ),
        sanitizedNumber.end()
    );

    // Check if the card number is empty or less than 16 digits
    if (sanitizedNumber.empty() || sanitizedNumber.length() < 16) {
        return std::make_pair(false, CardType::INVALID);
    }

    // Reverse the card number
    std::reverse(sanitizedNumber.begin(), sanitizedNumber.end());

    int sum = 0;
    bool alternate = false;
    CardType cardType = CardType::INVALID;

    for (size_t i = 0; i < sanitizedNumber.length(); ++i) {
        int digit = sanitizedNumber[i] - '0';

        if (i == sanitizedNumber.length() - 1) {
            // Determine the card type based on the first digit(s)
            if (digit == 4) {
                cardType = CardType::VISA;
            } else if (digit == 5) {
                cardType = CardType::MASTERCARD;
            } else if (digit == 3) {
                cardType = CardType::AMERICAN_EXPRESS;
            } else if (digit == 6) {
                cardType = CardType::DISCOVER;
            }
        }

        if (alternate) {
            digit *= 2;
            if (digit > 9) {
                digit = digit % 10 + digit / 10;
            }
        }

        sum += digit;
        alternate = !alternate;
    }

    bool isValid = sum % 10 == 0;
    return std::make_pair(isValid, cardType);
}

std::string getCardTypeName(CardType cardType) {
    switch (cardType) {
        case CardType::VISA:
            return "Visa";
        case CardType::MASTERCARD:
            return "Mastercard";
        case CardType::AMERICAN_EXPRESS:
            return "American Express";
        case CardType::DISCOVER:
            return "Discover";
        default:
            return "Unknown";
    }
}

int main() {
    std::cout << "Credit Card Validator" << std::endl;

    std::string cardNumber;
    std::cout << "Enter the credit card number: ";
    std::getline(std::cin, cardNumber);

    std::pair<bool, CardType> validationResult = validateCreditCard(cardNumber);
    bool isValid = validationResult.first;
    CardType cardType = validationResult.second;

    if (isValid) {
        std::cout << "The credit card number is valid." << std::endl;
        std::cout << "Card Type: " << getCardTypeName(cardType) << std::endl;
    } else {
        std::cout << "The credit card number is invalid." << std::endl;
    }

    return 0;
}