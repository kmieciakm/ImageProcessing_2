#include <iostream>
#include "CImg/CImg.h"
#include "myLib/headers/converter.h"
#include "myLib/headers/proc.h"
#include "myLib/headers/parser.h"

using namespace cimg_library;

int main(int argc, char *argv[]) {

    if(argc == 2 && (std::string)argv[1]=="--help")
        DisplayHelpInformations();
    
    CImg<unsigned char> loadedPicture(argv[1]);
    //std::string command = (std::string)argv[2];
    std::string fileName = ExtractFilenameFromPath((std::string)argv[1]);

    Photo myPicture(loadedPicture.width(), loadedPicture.height(), loadedPicture.spectrum(), fileName);
    CopyCImgToPhotoObject(loadedPicture,myPicture);

    CImg<unsigned char> img(myPicture.GetWidth(), myPicture.GetHeight(), 1, myPicture.GetChannelAmount());
    CopyPhotoObjectToCImg(img, myPicture);
    
    DisplayImage(img);

    std::string savePath = "./output/" + myPicture.GetFilename();
    img.save(savePath.c_str());
    
    return 1;
}