#ifndef PYTHONINTEGRATION_H
#define PYTHONINTEGRATION_H

#ifdef PYTHON_ENABLED

#include <string>
#include <vector>

/**
 * @brief Python integration layer for analytics and advanced processing
 * 
 * This optional module provides Python integration for:
 * - Text analytics (word count, reading time, sentiment analysis)
 * - Export functionality
 * - Custom processing scripts
 */
namespace PythonIntegration {

/**
 * @brief Initialize Python interpreter
 * @return true if successful, false otherwise
 */
bool initialize();

/**
 * @brief Shutdown Python interpreter
 */
void shutdown();

/**
 * @brief Analyze text content
 * @param content The text to analyze
 * @return A JSON string with analysis results
 */
std::string analyzeText(const std::string& content);

/**
 * @brief Calculate reading time estimate
 * @param content The text content
 * @return Estimated reading time in minutes
 */
int estimateReadingTime(const std::string& content);

/**
 * @brief Get word count
 * @param content The text content
 * @return Number of words
 */
int getWordCount(const std::string& content);

/**
 * @brief Export entries to various formats
 * @param entries Vector of entry file paths
 * @param outputPath Output file path
 * @param format Export format (pdf, html, epub)
 * @return true if successful, false otherwise
 */
bool exportEntries(const std::vector<std::string>& entries,
                   const std::string& outputPath,
                   const std::string& format);

} // namespace PythonIntegration

#endif // PYTHON_ENABLED

#endif // PYTHONINTEGRATION_H
