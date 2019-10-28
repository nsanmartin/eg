#include <variant>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <map>

class StateMachine {
protected:
    std::ifstream mIfstream;

public:
    StateMachine(const std::string& filename) : mIfstream{filename} {
        if (!mIfstream) {
            throw std::runtime_error (
                "cannot open file " + filename + "\n");
        }
        std::cout << "Reading " << filename << '\n';
    }

    void read_file() {
        char c;
        while (mIfstream.get(c)) { read_char(c); }
        std::cout << "accepted string\n";
    }

    void error(char c) {
        std::cout << "not bin string, read char '" << c << "'\n";
        std::exit(0);
    }

    virtual void read_char(char c) = 0;
    

    

};

//
///
//
class MachineHierarchy : public StateMachine {
    
    struct State {
        virtual void read_char (MachineHierarchy& m,char c) = 0;
    };

    std::unique_ptr<State> mState;

public:
    template<typename StateType>
    void Goto() { mState = std::make_unique<StateType>(); }

private:

    using TableType = const std::unordered_map<
        char,
        std::function<void(MachineHierarchy& m)>> ;

    struct Q0;
    struct Q1;
    
    struct Q0 : public State {
        static const TableType table;
        
        void read_char(MachineHierarchy& m, char c) override {
            auto char_fun = table.find(c);
            if (char_fun != table.end()) { char_fun->second(m); }
            else { m.error(c); }
        }
    };

    struct Q1 : public State {
        static const  TableType table;
        
        void read_char(MachineHierarchy& m, char c) override {
            auto char_fun = table.find(c);
            if (char_fun != table.end()) { char_fun->second(m); }
            else { m.error(c); }
        }

    };

public:
    MachineHierarchy(const std::string& filename)
        : StateMachine{filename},
          mState{std::make_unique<Q0>()} {
              read_file();
          }

    void read_char(char c) { mState->read_char(*this,c); }
};

//
//
//
//
struct MachineVariant : public StateMachine {
    using TableType = const std::unordered_map<
        char,
        std::function<void(MachineVariant& m)>> ;

 
    struct Q0 {
        static const TableType table;

        void read_char(MachineVariant& m, char c)  {
            auto char_fun = table.find(c);
            if (char_fun != table.end()) { char_fun->second(m); }
            else { m.error(c); }

            // if (c == '0') { m.Goto<Q0>(); }
            // else if ( c != '1') { m.error(c); }
        }
    };

    struct Q1 {
        static const TableType table;
        
        void read_char(MachineVariant& m, char c)  {
            auto char_fun = table.find(c);
            if (char_fun != table.end()) { char_fun->second(m); }
            else { m.error(c); }

            // if (c == '0') { m.Goto<Q1>(); }
            // else if ( c != '1') { m.error(c); }
        }
    };
    
    struct Q2 {
        static const TableType table;
        
        void read_char(MachineVariant& m, char c)  {
            auto char_fun = table.find(c);
            if (char_fun != table.end()) { char_fun->second(m); }
            else { m.error(c); }

            // if (c == '0') { m.Goto<Q1>(); }
            // else if ( c != '1') { m.error(c); }
        }

    };


    using StateUnion = std::variant<Q0, Q1, Q2>;

    StateUnion mState;
    std::ifstream mIfstream;
public:
    MachineVariant(const std::string& filename)
        : StateMachine{filename}, mState{Q0{}} { read_file(); }


    template<typename StateType>
    void Goto() { mState = StateType{}; }

    void read_char(char c) {
        std::visit([&c, this](auto&& arg) {
                       arg.read_char(*this, c);
                   }, mState);
    }
};
