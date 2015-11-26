/**
 *  @file Vision.hpp
 *  Computer vision class using YUYV.
 *
 *  @authors Ants-Oskar Mäesalu
 *  @version 0.1
 *  @date 26 November 2015
 */

#ifndef RTX_VISION_VISION_H
#define RTX_VISION_VISION_H

#include <vector>

#include "rtxhal.hpp"
#include "Feature.hpp"
#include "Blob.hpp"


namespace rtx {

  namespace Vision {

    typedef std::vector<Blob*> BlobSet;
    typedef std::vector<Feature> LineSet;
    typedef std::vector<Feature> CornerSet;

    extern BlobSet blobs;
    extern BlobSet blobsBuffer;

    extern LineSet lines;
    extern LineSet linesBuffer;

    extern CornerSet corners;
    extern CornerSet cornersBuffer;

    extern bool editingBlobs;
    extern bool editingLines;
    extern bool editingCorners;

    void setup();
    void process(const Frame&, const std::string&);
    void processCheckerboard(const Frame&, const std::string&);

    bool isColored(const Frame&, const std::string&, const unsigned int&, const unsigned int&, const unsigned int&, const unsigned int&);
    bool isColored(const Frame&, const std::string&, const unsigned int&, const unsigned int&);

    BlobSet getBlobs();
    LineSet getLines();
    CornerSet getCorners();

    //void blobDetection(const Frame&, const std::string&, const std::vector<unsigned int>&); // TODO: Remove temporary commented method
    void blobDetection(const Frame&, const std::string&, const std::vector<unsigned int>&, const std::vector<std::vector<std::pair<unsigned int, unsigned int>>>&);

    void lineDetection(const Frame&, const std::string&);
    void lineDetection(const Frame&, const std::string&, const std::vector<Point2D>&);

    void cornerDetection(const Frame&, const std::string&);
    void cornerDetection(const Frame&, const std::string&, const std::vector<Point2D>&);

  };

}

#endif // RTX_VISION_VISION_H
