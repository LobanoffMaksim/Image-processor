add_executable(
    image_processor
    image_processor.cpp
        CmdLineParser.cpp
        CmdLineParser.h
        BMPImage.cpp
        BMPImage.h
        Filter.cpp
        Filter.h
        CropFilter.cpp
        CropFilter.h
        FilterFactory.h
        FilterFactory.cpp
        Controller.cpp
        Controller.h
        FilterFactory.cpp
        GrayscaleFilter.cpp
        GrayscaleFilter.h
        MatrixFilter.cpp
        MatrixFilter.h
        SharpFilter.cpp
        SharpFilter.h
        EdgeFilter.cpp
        EdgeFilter.h
        BlurFilter.cpp
        BlurFilter.h
        NegFilter.cpp
        NegFilter.h
        FolderFilter.cpp
        FolderFilter.h
        Numbers.cpp
        Numbers.h
)
