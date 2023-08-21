#include "CSVparser.hpp"

#include <fstream>
#include <sstream>

namespace csv {

    /**
     * Default constructor
     *
     * @param string data
     * @param char separator
     */
    Parser::Parser(const string &data, char separator) {
        string line;
        _file = data;
        _separator = separator;
        ifstream inFile(_file.c_str());
        if (inFile.is_open()) {
            while (inFile.good()) {
                getline(inFile, line);
                if (!line.empty()) {
                    _lines.push_back(line);
                }
            }
            inFile.close();

            if (_lines.empty()) {
                throw Error(string("No Data in ").append(_file));
            }

            parseContent();
        } else {
            throw Error(string("Failed to open ").append(_file));
        }
    }

    /**
     * Iterate over lines vector and build content, a 2 dimensional vector
     */
    void Parser::parseContent() {
        for (unsigned int lineIndex = 0; lineIndex < _lines.size(); ++lineIndex) {
            bool quoted = false;
            unsigned int tokenStart = 0;

            _content.emplace_back();

            for (unsigned int charIndex = 0; charIndex < _lines.at(lineIndex).length(); ++charIndex) {
                if (_lines.at(lineIndex)[charIndex] == '"') {
                    quoted = !(quoted);
                } else if (_lines.at(lineIndex)[charIndex] == _separator && !quoted) {
                    _content.at(lineIndex).push_back(_lines.at(lineIndex).substr(tokenStart, charIndex - tokenStart));
                    tokenStart = charIndex + 1;
                }
            }
            _content.at(lineIndex).push_back(_lines.at(lineIndex).substr(tokenStart, _lines.at(lineIndex).length() - tokenStart));
        }
    }

    /**
     * Get content, a 2 dimensional vector
     * @return vector<vector<string>>
     */
    vector<vector<string>> Parser::getContent() {
        return _content;
    }
}
