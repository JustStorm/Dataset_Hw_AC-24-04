#pragma once
#ifndef SUBSTRING_SEARCHER_H
#define SUBSTRING_SEARCHER_H

#include <vector>
#include <string>
#include <functional>
#include <algorithm>

class SubstringSearcher {
private:
    static std::vector<int> computeLPS(const std::string& pattern);
    static int kmpSearch(const std::string& text, const std::string& pattern);

public:
    // Упрощенная версия без отдельного countSubstringOccurrences
    template<typename DatasetType>
    static std::vector<int> searchInCity(DatasetType& dataset, const std::string& pattern) {
        int size = dataset.get_size();
        std::vector<int> results(size, 0);

        for (int i = 0; i < size; i++) {
            const char* fieldValue = dataset.get_city(i);
            if (fieldValue != nullptr) {
                std::string text(fieldValue);
                std::string lowerText = text;
                std::string lowerPattern = pattern;
                std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
                std::transform(lowerPattern.begin(), lowerPattern.end(), lowerPattern.begin(), ::tolower);

                results[i] = kmpSearch(lowerText, lowerPattern);
            }
        }

        return results;
    }

    template<typename DatasetType>
    static std::vector<int> searchInCounty(DatasetType& dataset, const std::string& pattern) {
        int size = dataset.get_size();
        std::vector<int> results(size, 0);

        for (int i = 0; i < size; i++) {
            const char* fieldValue = dataset.get_county(i);
            if (fieldValue != nullptr) {
                std::string text(fieldValue);
                std::string lowerText = text;
                std::string lowerPattern = pattern;
                std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
                std::transform(lowerPattern.begin(), lowerPattern.end(), lowerPattern.begin(), ::tolower);

                results[i] = kmpSearch(lowerText, lowerPattern);
            }
        }

        return results;
    }

    template<typename DatasetType>
    static std::vector<int> searchInState(DatasetType& dataset, const std::string& pattern) {
        int size = dataset.get_size();
        std::vector<int> results(size, 0);

        for (int i = 0; i < size; i++) {
            const char* fieldValue = dataset.get_state(i);
            if (fieldValue != nullptr) {
                std::string text(fieldValue);
                std::string lowerText = text;
                std::string lowerPattern = pattern;
                std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
                std::transform(lowerPattern.begin(), lowerPattern.end(), lowerPattern.begin(), ::tolower);

                results[i] = kmpSearch(lowerText, lowerPattern);
            }
        }

        return results;
    }

    template<typename DatasetType>
    static std::vector<int> searchInWeatherCondition(DatasetType& dataset, const std::string& pattern) {
        int size = dataset.get_size();
        std::vector<int> results(size, 0);

        for (int i = 0; i < size; i++) {
            const char* fieldValue = dataset.get_weather_condition(i);
            if (fieldValue != nullptr) {
                std::string text(fieldValue);
                std::string lowerText = text;
                std::string lowerPattern = pattern;
                std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
                std::transform(lowerPattern.begin(), lowerPattern.end(), lowerPattern.begin(), ::tolower);

                results[i] = kmpSearch(lowerText, lowerPattern);
            }
        }

        return results;
    }

    template<typename DatasetType>
    static std::vector<int> searchInAllStringFields(DatasetType& dataset, const std::string& pattern) {
        int size = dataset.get_size();
        std::vector<int> totalResults(size, 0);

        // Получаем результаты для каждого поля
        std::vector<int> cityResults = searchInCity(dataset, pattern);
        std::vector<int> countyResults = searchInCounty(dataset, pattern);
        std::vector<int> stateResults = searchInState(dataset, pattern);
        std::vector<int> weatherResults = searchInWeatherCondition(dataset, pattern);

        // Суммируем результаты
        for (int i = 0; i < size; i++) {
            totalResults[i] = cityResults[i] + countyResults[i] + stateResults[i] + weatherResults[i];
        }

        return totalResults;
    }
};

#endif // SUBSTRING_SEARCHER_H