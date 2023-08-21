#ifndef     _CSVPARSER_HPP_
# define    _CSVPARSER_HPP_

# include <stdexcept>
# include <string>
# include <vector>
# include <list>
# include <sstream>

namespace csv {
    class Error : public runtime_error {

    public:
        explicit Error(const string &msg) : runtime_error(std::string("CSVparser : ").append(msg)) {}
    };

    class Parser {

    public:
        Parser(const string&, char);
        vector<vector<string>> getContent();

    protected:
        void parseContent();

    private:
        char _separator;
        string _file;
        vector<string> _lines;
        vector<vector<string>> _content;
    };
}

#endif /*!_CSVPARSER_HPP_*/
