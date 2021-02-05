/* invalid_input.h (S3438653 Christine Huynh 2017)
 */
#include <string>
#include <exception>

/* User enter value that is out of bounds*/
class out_of_bounds : public std::out_of_range {
    public:
        out_of_bounds(std::string const& message) : std::out_of_range("Out of Bounds:" + message)
    {}
    virtual ~out_of_bounds(void){}
};

/* User selects a token that doesnt exist*/
class missing_token : public std::invalid_argument {
    public:
    missing_token(std::string const& message) : std::invalid_argument("Missing Token: " + message)
    {}
    virtual ~missing_token(void){}
};

/* User selects token that belongs to the opponent*/
class incorrect_token : public std::invalid_argument {
    public:
    incorrect_token(std::string const& message) : std::invalid_argument("Incorrect Token: " + message)
    {}
    virtual ~incorrect_token(void){}
};

/* User enters an end postion that contains a token*/
class blocked_token : public std::invalid_argument {
    public:
    blocked_token(std::string const& message) : std::invalid_argument("Blocked Position: " + message)
    {}
    virtual ~blocked_token(void){}
};

/* User attempts to make an invalid move*/
class invalid_move : public std::invalid_argument {
    public:
    invalid_move(std::string const& message) : std::invalid_argument("Invalid Move: " + message)
    {}
    virtual ~invalid_move(void){}
};

/* User enters invalid input */
class invalid_input : public std::invalid_argument {
    public:
    invalid_input(std::string const& message) : std::invalid_argument("Invalid Input: " + message)
    {}
    virtual ~invalid_input(void){}
};

