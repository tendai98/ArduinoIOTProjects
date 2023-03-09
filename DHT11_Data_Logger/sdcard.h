#include "FS.h" 
#include "SD_MMC.h" 

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){

    File root = fs.open(dirname);
    if(!root){
        return;
    }
    if(!root.isDirectory()){
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        }
        file = root.openNextFile();
    }
}

//Create a dir in SD card
void createDir(fs::FS &fs, const char * path){
    fs.mkdir(path);
}

//delete a dir in SD card
void removeDir(fs::FS &fs, const char * path){
    fs.rmdir(path);
}

//Read a file in SD card
void readFile(fs::FS &fs, const char * path){
    
    File file = fs.open(path);
    if(!file){
        return;
    }

    while(file.available()){
        Serial.write(file.read());
    }
}

//Write a file in SD card
void writeFile(fs::FS &fs, const char * path, const char * message){
    
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        return;
    }
   
 
    file.print(message);
}

//Append to the end of file in SD card
bool appendFile(fs::FS &fs, const char * path, const char * message){
    
    File file = fs.open(path, FILE_APPEND);
    if(!file){
        return false;
    }
    return file.print(message);
}

//Rename a file in SD card
void renameFile(fs::FS &fs, const char * path1, const char * path2){
    fs.rename(path1, path2);
}

//Delete a file in SD card
void deleteFile(fs::FS &fs, const char * path){
    fs.remove(path);
}

//Test read and write speed using test.txt file
void testFileIO(fs::FS &fs, const char * path){
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }


    file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}

void initSDM_MMC(){  

   if(!SD_MMC.begin()){
        return;
    }
    uint8_t cardType = SD_MMC.cardType();

    if(cardType == CARD_NONE){
        return;
    }
    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
}
