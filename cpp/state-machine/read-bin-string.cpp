#include <string>
#include <vector>
#include <variant>
#include <iostream>
#include <functional>

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "include/machines.hpp"

static struct option long_opts[] = {
    {"hierarchy", no_argument, 0, 'h'},
    {"variant", no_argument, 0, 'v'},
    {"switch",  no_argument, 0, 's'},
    {0, 0, 0, 0}
};



enum class Implementation { Hierarchy, Variant, Switch };

MachineHierarchy::TableType
MachineHierarchy::Q0::table = {
    {'0', [](MachineHierarchy& m) { }},
    {'1', [](MachineHierarchy& m) { m.Goto<Q1>();}}
};

MachineHierarchy::TableType
MachineHierarchy::Q1::table = {
    {'0', [](MachineHierarchy& m) { m.Goto<Q0>();}},
    {'1', [](MachineHierarchy& m) { }}
};


MachineVariant::TableType
MachineVariant::Q0::table = {
    {'0', [](MachineVariant& m) { }},
    {'1', [](MachineVariant& m) { m.Goto<Q1>();}},
    {'2', [](MachineVariant& m) { m.Goto<Q2>();}}

};

MachineVariant::TableType
MachineVariant::Q1::table = {
    {'0', [](MachineVariant& m) { m.Goto<Q0>();}},
    {'1', [](MachineVariant& m) { }},
    {'2', [](MachineVariant& m) { m.Goto<Q2>();}}
};

MachineVariant::TableType
MachineVariant::Q2::table = {
    {'0', [](MachineVariant& m) { m.Goto<Q0>();}},
    {'1', [](MachineVariant& m) { m.Goto<Q1>();}},
    {'2', [](MachineVariant& m) {}}
};


int main (int argc, char* argv[]) {

    Implementation impl{Implementation::Hierarchy};
    char c;
    
    while ((c = getopt_long (argc, argv, "hvs", long_opts, nullptr))
           != -1)
        switch (c) {
        case 'h':
            impl = Implementation::Hierarchy;
        break;
        case 'v':
            impl = Implementation::Variant;
        break;
      case 's':
          impl = Implementation::Switch;
        break;
      case '?':
          if (isprint (optopt))
              std::cerr << "Unknown option `" << optopt << '\n';
          else
              std::cerr << "Unknown option character `\\x"
                        << optopt << '\n';
          return 1;
        default:
            abort ();
      }


    if (optind == argc) {
        std::cout << "usage: " << argv[0] << " FILENAME\n";
    }
    
    try {
        std::function<void(const char*)> fun;
        switch (impl) {
            
        case Implementation::Hierarchy: {
            std::cout << "Implementation::Hierarchy:\n";
            fun = [](const char * fname) {
                           MachineHierarchy m(fname);
                       };
        }
            break;
        case Implementation::Variant: {
            std::cout << "Implementation::Variant:\n";
            fun = [](const char * fname) {
                           MachineVariant m(fname);
                               };
        }
            break;
        case Implementation::Switch: {
            std::cout << "Implementation::Switch:\n";
            std::cout << "Not implemented yet\n";
            std::exit(1);
        }
        }
        
        for (int i = optind; i < argc; ++i) {
            fun(argv[i]);
        }
    } catch (std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
    }
}
