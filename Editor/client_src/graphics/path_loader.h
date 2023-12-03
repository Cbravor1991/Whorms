
#ifndef PATH_LOADER_H
#define PATH_LOADER_H
#include <vector>
#include <string>

class PathLoader {

    private:

        std::vector<std::string> sprite_path;
        std::string background_path;
        std::string music_path;
   

    public:

    explicit PathLoader();

    std::vector<std::string>& getSpritePath();
    std::string& getBackgroundPath();
    std::string& getMusicPath();


    void loadSpritePath();

    void loadBackgroundPath();

    void loadMusicPath();

   
};

#endif