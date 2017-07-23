#ifndef CUBOIDS_H
#define CUBOIDS_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum Algorithm
{
    LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY,
    LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY,
    MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS
};

class AbstractCuboid
{
  protected:
  unsigned short length;
  unsigned short width;
  unsigned short height;
  unsigned int volume;

  public:
  AbstractCuboid() {}
  AbstractCuboid(unsigned short length, unsigned short width, unsigned short height)
  {
    this->length = length;
    this->width = width;
    this->height = height;
    this->volume = length * width * height;
  }
};

class Cuboid : AbstractCuboid
{
  unsigned short x;
  unsigned short y;
  unsigned short z;
  unsigned short color;
  bool used;

public:

  Cuboid(unsigned short length, unsigned short width, unsigned short height,
         unsigned short x = 0, unsigned short y = 0, unsigned short z = 0, bool used = false)
    : AbstractCuboid(length, width, height)
  {
    //srand (time(NULL));
    this->x = x;
    this->y = y;
    this->z = z;
    this->used = used;
    this->color = rand() % 101;
  }

  bool equals(Cuboid& cuboid)
  {
    return this->length == cuboid.length && this->width == cuboid.width && this->height == cuboid.height
      && this->x == cuboid.x && this->y == cuboid.y && this->z == cuboid.z;
  }

  void setX(unsigned short x)
  {
    this->x = x;
  }

  unsigned short getX()
  {
    return this->x;
  }

  void setY(unsigned short y)
  {
    this->y = y;
  }

  unsigned short getY()
  {
    return this->y;
  }

  void setZ(unsigned short z)
  {
    this->z = z;
  }

  unsigned short getZ()
  {
    return this->z;
  }

  void setLength(unsigned short length)
  {
    this->length = length;
  }

  unsigned short getLength()
  {
    return this->length;
  }

  void setWidth(unsigned short width)
  {
    this->width = width;
  }

  unsigned short getWidth()
  {
    return this->width;
  }

  void setHeight(unsigned short height)
  {
    this->height = height;
  }

    unsigned short getHeight()
  {
    return this->height;
  }

  void setVolume(unsigned int volume)
  {
    this->volume = volume;
  }

  unsigned int getVolume()
  {
    return this->volume;
  }

  void setUsed(bool used)
  {
    this->used = used;
  }

  bool getUsed()
  {
    return this->used;
  }

  unsigned short getColor()
  {
    return this->color;
  }
};


class CuboidalSphere : AbstractCuboid
{
public:

  bool withArray;
  bool ***blockArray;

  CuboidalSphere(unsigned short length, unsigned short width, unsigned short height,
              bool withArray = false) : AbstractCuboid(length, width, height)
  {
    this->withArray = withArray;
    if(!this->withArray)
      return ;

    blockArray = new bool**[length];
    for(int i = 0; i < length; i++)
    {
      blockArray[i] = new bool*[width];
      for(int j = 0; j < width; j++)
        blockArray[i][j] = new bool[height];
    }

    for(int i = 0; i < length; i++)
      for(int j = 0; j < width; j++)
        for(int k = 0; k < height; k++)
          blockArray[i][j][k] = true; // jesli true to wolne pole, w przeciwnym razie false
  }

  ~CuboidalSphere()
  {
    if(!withArray)
      return ;

    for(int i = 0; i < length; i++)
      for(int j = 0; j < width; j++)
        free(blockArray[i][j]);

    for(int i = 0; i < length; i++)
      free(blockArray[i]);

    free(blockArray);
  }

  void setLength(unsigned short length)
  {
    this->length = length;
  }

  unsigned short getLength()
  {
    return this->length;
  }

  void setWidth(unsigned short width)
  {
    this->width = width;
  }

  unsigned short getWidth()
  {
    return this->width;
  }

  void setHeight(unsigned short height)
  {
    this->height = height;
  }

    unsigned short getHeight()
  {
    return this->height;
  }

  void setVolume(unsigned int volume)
  {
    this->volume = volume;
  }

  unsigned int getVolume()
  {
    return this->volume;
  }
};

class AbstractLayer
{
protected:

  unsigned short length;
  unsigned short width;
  unsigned int area;

  AbstractLayer(unsigned short length, unsigned short width)
  {
    this->length = length;
    this->width = width;
    this->area = length * width;
  }
};

class Layer : AbstractLayer
{
  unsigned short z;

  public:

  bool **blockArray;

  Layer(unsigned short length, unsigned short width, unsigned short z = 0)
        : AbstractLayer(length, width)
  {
    this->z = z;
    blockArray = new bool*[length];
    for(int i = 0; i < length; i++)
      blockArray[i] = new bool[width];

    for(int i = 0; i < length; i++)
      for(int j = 0; j < width; j++)
        blockArray[i][j] = true; // jesli true to wolne pole, w przeciwnym razie false
  }

  ~Layer()
  {
    for(int i = 0; i < length; i++)
      free(blockArray[i]);

    free(blockArray);
  }

  void setLength(unsigned short length)
  {
    this->length = length;
  }

  unsigned short getLength()
  {
    return this->length;
  }

  void setWidth(unsigned short width)
  {
    this->width = width;
  }

  unsigned short getWidth()
  {
    return this->width;
  }

  void setArea(unsigned int area)
  {
    this->area = area;
  }

  unsigned int getArea()
  {
    return this->area;
  }

  void setZ(unsigned short z)
  {
    this->z = z;
  }

  unsigned short getZ()
  {
    return this->z;
  }
};

class FreeLayer : AbstractLayer
{
  unsigned short x;
  unsigned short y;

public:

  FreeLayer(unsigned short length, unsigned short width,
            unsigned short x = 0, unsigned short y = 0)
    : AbstractLayer(length, width)
  {
    this->x = x;
    this->y = y;
  }

  bool equals(FreeLayer& freelayer)
  {
    return this->length == freelayer.length && this->width == freelayer.width &&
      this->x == freelayer.x && this->y == freelayer.y;
  }

  void setX(unsigned short x)
  {
    this->x = x;
  }

  unsigned short getX()
  {
    return this->x;
  }

  void setY(unsigned short y)
  {
    this->y = y;
  }

  unsigned short getY()
  {
    return this->y;
  }

  void setLength(unsigned short length)
  {
    this->length = length;
  }

  unsigned short getLength()
  {
    return this->length;
  }

  void setWidth(unsigned short width)
  {
    this->width = width;
  }

  unsigned short getWidth()
  {
    return this->width;
  }

  void setArea(unsigned int area)
  {
    this->area = area;
  }

  unsigned int getArea()
  {
    return this->area;
  }
};

class CuboidSerie
{
private:
    unsigned short sphereLength;
    unsigned short sphereWidth;
    unsigned short initialSphereHeight;
    unsigned int initialSphereVolume;
    unsigned short finalSphereHeightForAlgorithm1;
    unsigned int finalSphereVolumeForAlgorithm1;
    unsigned short finalSphereHeightForAlgorithm2;
    unsigned int finalSphereVolumeForAlgorithm2;
    unsigned short finalSphereHeightForAlgorithm3;
    unsigned int finalSphereVolumeForAlgorithm3;
    bool computedByAlgorithm1;
    bool computedByAlgorithm2;
    bool computedByAlgorithm3;
    unsigned int computationTimeForAlgorithm1; // czas w mikrosekundach
    unsigned int computationTimeForAlgorithm2; // czas w mikrosekundach
    unsigned int computationTimeForAlgorithm3; // czas w mikrosekundach

public:
  list<Cuboid> *cuboidListForAlgorithm1;
  list<Cuboid> *cuboidListForAlgorithm2;

 CuboidSerie()
 {
     cuboidListForAlgorithm1 = new list<Cuboid>();
     cuboidListForAlgorithm2 = new list<Cuboid>();
     this->sphereLength = 0;
     this->sphereWidth = 0;
     this->initialSphereHeight = 0;
     this->initialSphereVolume = 0;
     this->finalSphereHeightForAlgorithm1 = 0;
     this->finalSphereVolumeForAlgorithm1 = 0;
     this->finalSphereHeightForAlgorithm2 = 0;
     this->finalSphereVolumeForAlgorithm2 = 0;
     this->finalSphereHeightForAlgorithm3 = 0;
     this->finalSphereVolumeForAlgorithm3 = 0;
     this->computedByAlgorithm1 = false;
     this->computedByAlgorithm2 = false;
     this->computedByAlgorithm3 = false;
     this->computationTimeForAlgorithm1 = 0;
     this->computationTimeForAlgorithm2 = 0;
     this->computationTimeForAlgorithm3 = 0;
 }

 void setSphereLength(unsigned short sphereLength)
 {
   this->sphereLength = sphereLength;
 }

 unsigned short getSphereLength()
 {
   return this->sphereLength;
 }

 void setSphereWidth(unsigned short sphereWidth)
 {
   this->sphereWidth = sphereWidth;
 }

 unsigned short getSphereWidth()
 {
   return this->sphereWidth;
 }

 void setInitialSphereHeight(unsigned short initialSphereHeight)
 {
   this->initialSphereHeight = initialSphereHeight;
 }

 unsigned short getInitialSphereHeight()
 {
   return this->initialSphereHeight;
 }

 void setFinalSphereHeight(Algorithm algorithm, unsigned short finalSphereHeight)
 {
     switch(algorithm)
     {
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY:
         this->finalSphereHeightForAlgorithm1 = finalSphereHeight;
         break;
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY:
         this->finalSphereHeightForAlgorithm2 = finalSphereHeight;
         break;
        case MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS:
         this->finalSphereHeightForAlgorithm3 = finalSphereHeight;
         break;
     }
 }

 unsigned short getFinalSphereHeight(Algorithm algorithm)
 {
     switch(algorithm)
     {
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY:
         return this->finalSphereHeightForAlgorithm1;
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY:
         return this->finalSphereHeightForAlgorithm2;
        case MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS:
         return this->finalSphereHeightForAlgorithm3;
     }
     return 0;
 }

 void setInitialSphereVolume(unsigned int initialSphereVolume)
 {
   this->initialSphereVolume = initialSphereVolume;
 }

 unsigned int getInitialSphereVolume()
 {
   return this->initialSphereVolume;
 }

 void setFinalSphereVolume(Algorithm algorithm, unsigned int finalSphereVolume)
 {
     switch(algorithm)
     {
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY:
         this->finalSphereVolumeForAlgorithm1 = finalSphereVolume;
         break;
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY:
         this->finalSphereVolumeForAlgorithm2 = finalSphereVolume;
         break;
        case MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS:
         this->finalSphereVolumeForAlgorithm3 = finalSphereVolume;
         break;
     }
 }

 unsigned int getFinalSphereVolume(Algorithm algorithm)
 {
     switch(algorithm)
     {
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY:
         return this->finalSphereVolumeForAlgorithm1;
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY:
         return this->finalSphereVolumeForAlgorithm2;
        case MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS:
         return this->finalSphereVolumeForAlgorithm3;
     }
 }

 void setComputationTime(Algorithm algorithm, unsigned int computationTime)
 {
     switch(algorithm)
     {
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY:
         this->computationTimeForAlgorithm1 = computationTime;
         break;
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY:
         this->computationTimeForAlgorithm2 = computationTime;
         break;
        case MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS:
         this->computationTimeForAlgorithm3 = computationTime;
         break;
     }
 }

 unsigned int getComputationTime(Algorithm algorithm)
 {
     switch(algorithm)
     {
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY:
         return this->computationTimeForAlgorithm1;
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY:
         return this->computationTimeForAlgorithm2;
        case MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS:
         return this->computationTimeForAlgorithm3;
     }
     return 0;
 }

 void setComputedBy(Algorithm algorithm, bool computed)
 {
     switch(algorithm)
     {
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY:
         this->computedByAlgorithm1 = computed;
         break;
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY:
         this->computedByAlgorithm2 = computed;
         break;
        case MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS:
         this->computedByAlgorithm3 = computed;
         break;
     }
 }

 bool getComputedBy(Algorithm algorithm)
 {
     switch(algorithm)
     {
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITH_ARRAY:
         return this->computedByAlgorithm1;
        case LARGEST_CUBOIDS_IN_SMALLEST_AREAS_WITHOUT_ARRAY:
         return this->computedByAlgorithm2;
        case MOST_FLAT_CUBOIDS_IN_MOST_FLAT_AREAS:
         return this->computedByAlgorithm3;
     }
     return false;
 }
};

class CuboidManager
{
private:
    vector<CuboidSerie> *cuboidSeries;

public:

 CuboidManager()
 {
     cuboidSeries = new vector<CuboidSerie>();
 }
 vector<CuboidSerie> *getCuboidSeries();

};

void showBlockArray(Layer& layer);

void clearCuboids(list<Cuboid>& cuboidList);

unsigned short getHeightOfSphere(list<Cuboid>& inputCuboidList);

bool isEmptyBlock(list<Cuboid>& inputCuboidList, unsigned short x, unsigned short y, unsigned short z);

void NewFreeCuboidExpand(CuboidalSphere& cuboidalSphere, list<Cuboid>& inputCuboidsList, Cuboid *newFreeCuboid);

void NewFreeLayerExpand(Layer& layer, FreeLayer *newFreeLayer);

bool SmallerVolumeCompare(Cuboid& firstCuboid, Cuboid& secondCuboid);

bool LargerVolumeCompare(Cuboid& firstCuboid, Cuboid& secondCuboid);

bool LargerAreaCompare(FreeLayer& firstLayer, FreeLayer& secondLayer);

bool isCuboidInList(list<Cuboid>& freeCuboidsList, Cuboid& freeCuboid);

bool isLayerInList(list<FreeLayer>& freeLayersList, FreeLayer& freeLayer);

void FreeCuboidsSearch(CuboidalSphere& cuboidalSphere, list<Cuboid>& inputCuboidsList, list<Cuboid>& freeCuboidsList);

void FreeLayersSearch(Layer& layer, list<FreeLayer>& freeLayersList);

void RotateCuboid(Cuboid& cuboid, unsigned short sideA, unsigned short sideB, unsigned short sideC);

bool CuboidSideCheck(FreeLayer& freeLayer, Cuboid& cuboid, unsigned int& maximalArea,
  Cuboid **mostFlatCuboid, unsigned short& bestLength, unsigned short&  bestWidth, unsigned short&  bestHeight);

bool isFittingInFreeCuboid(Cuboid& inputCuboid, Cuboid& freeCuboid);

Cuboid* FindMostFlatCuboidFittingTheFreeLayer(list<Cuboid>& inputCuboidsList, FreeLayer& freeLayer,
        unsigned short& bestLength, unsigned short&  bestWidth, unsigned short&  bestHeight);

CuboidalSphere* AddNextLayer(CuboidalSphere *cuboidalSphere);

void SetNextLayer(Layer& layer, list<Cuboid>& inputCuboidsList);

unsigned short Algorithm_1(list<Cuboid>& inputCuboidsList, CuboidalSphere *cuboidalSphere);

unsigned short Algorithm_2(list<Cuboid>& inputCuboidsList, Layer& layer);

#endif // CUBOIDS_H

