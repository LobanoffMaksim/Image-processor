#include "BMPImage.h"
#include "CmdLineParser.h"
#include "Controller.h"
#include "FilterFactory.h"

#include <iostream>
#include "stdexcept"

int main(int argc, char** argv) {

    CmdLineParser input;
    try {
        input = CmdLineParser(argc, argv);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        return 0;
    }
    BMPImage image;
    try {
        image.Open(input.GetInputFile());
        image.ReadBmp();
        image.Open(input.GetOutputFile());
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 2;
    } catch (...) {
        std::cerr << "Unknown error in opening/reading input file\n";
        return 3;
    }

    try {
        FilterFactory filter_factory;
    } catch (std::logic_error& e) {
        std::cerr << e.what() << '\n';
        return 4;
    } catch (...) {
        std::cerr << "Unknown error in building filters\n";
        return 3;
    }

    try {
        Controller controller(input);
        controller.ApplyFilters(image);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 2;
    } catch (std::logic_error& e) {
        std::cerr << e.what() << '\n';
        return 4;
    } catch (...) {
        std::cerr << "Unknown error in applying filters\n";
        return 3;
    }
    try {
        image.WriteBmp();
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 2;
    } catch (...) {
        std::cerr << "Unknown error in writing output file\n";
        return 3;
    }
}
