#pragma once

#include <iostream>
#include "clipp.h"

template<typename CLI>
void parse(CLI &&cli, int argc, char **argv, bool exit_at_error=true){
    auto res = clipp::parse(argc, argv, cli);
    auto docfmt = clipp::doc_formatting{}.last_column(INT32_MAX);
    if(res.any_error()) {
        std::cout << "Command line parse error\n";
        for(const auto& m : res.missing()) { 
            std::cout << "Missing " << m.param()->label() << " after index " << m.after_index() << '\n';
        }
        for(const auto& m : res) {
            std::cout << m.index() << ": " << m.arg() << " -> " << m.param()->label();
            std::cout << " repeat #" << m.repeat();
            if(m.blocked()) std::cout << " blocked";
            if(m.conflict()) std::cout << " conflict";
            std::cout << '\n';
        }
        std::cout << "\nUsage:\n" << clipp::usage_lines(cli, argv[0], docfmt) << "\n\n"
             << "Parameters:\n" << clipp::documentation(cli, docfmt) << '\n';
        if(exit_at_error){
            exit(1);
        }
    }
}
