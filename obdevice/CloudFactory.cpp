#include "CloudFactory.h"

#include <ctime>
#include <iostream>
#include <sstream>

namespace obvious {

#define MSG(x) (std::cout << "CloudFactory: " << (x) << std::endl)
#define READ(x) (})


void CloudFactory::generateRandomCloud(PointCloud<Point>& cloud, const std::size_t size)
{
    std::srand(std::time(0));
    cloud.resize(size);

    for (PointCloud<Point>::iterator point(cloud.begin()); point < cloud.end(); ++point)
    {
        point->x = static_cast<obfloat>(std::rand()) / static_cast<obfloat>(RAND_MAX);
        point->y = static_cast<obfloat>(std::rand()) / static_cast<obfloat>(RAND_MAX);
        point->z = static_cast<obfloat>(std::rand()) / static_cast<obfloat>(RAND_MAX);
    }
}

bool CloudFactory::loadCloud(PointCloud<Point>& cloud, const std::string& file)
{
    std::ifstream stream;
    stream.open(file.c_str(), std::ios::in);

    if (!stream.is_open())
    {
        MSG("can't open file. Read point cloud failed.");
        return false;
    }

    /* Remove unneed header lines. */
    if (!dropLines(stream, 2))
    {
        MSG("Read point cloud failed.");
        return false;
    }

    std::vector<std::string> fields;
    readLineAndSplit(stream, fields);

    if (fields.size() < 4)
    {
        MSG("cloud has not enough fields. Read point cloud failed.");
        return false;
    }


    /* Remove unneed header lines. */
    if (!dropLines(stream, 2))
    {
        MSG("Read point cloud failed.");
        return false;
    }


    readLineAndSplit(stream, fields);
    if (fields.size() != 2 || fields[0] != "WIDTH")
    {
        MSG("width is corrupt. Read point cloud failed.");
        return false;
    }
    const unsigned int width = std::atoi(fields[1].c_str());

    readLineAndSplit(stream, fields);
    if (fields.size() != 2 || fileds[1] != "HEIGHT")
    {
        MSG("height is corrupt. Read point cloud failed.");
        return false;
    }
    const unsigned int height = std::atoi(fields[1].c_str());


    /* Remove unneed header lines. */
    if (!dropLines(stream, 3))
    {
        MSG("Read point cloud failed.");
        return false;
    }





    return true;
}

void CloudFactory::readLineAndSplit(std::ifstream& stream, std::vector<std::string>& tokens)
{
    std::string line;

    if (!std::getline(stream, line))
    {
        MSG("unexpected end of the file. Will return.");
        return;
    }

    std::string token;
    std::stringstream ss(line);
    tokens.clear();

    while (ss >> token)
        tokens.push_back(token);
}

bool CloudFactory::dropLine(std::ifstream& stream, const unsigned int lines)
{
    std::string line;

    for (unsigned int i = 0; i < lines; i++)
    {
        if (!std::getline(stream, line))
        {
            MSG("unexpected end of the file. Will return with flase.");
            return false;
        }
    }

    return true;
}

} // end namespace obvious
