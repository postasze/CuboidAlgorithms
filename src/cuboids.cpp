#include "cuboids.h"

using namespace std;

vector<CuboidSerie>* CuboidManager::getCuboidSeries()
{
    return this->cuboidSeries;
}

void clearCuboids(list<Cuboid>& cuboidList)
{
    list<Cuboid>::iterator iter = cuboidList.begin();
    while (iter != cuboidList.end())
    {
        iter->setUsed(false);
        iter++;
    }
}

void showBlockArray(Layer& layer)
{
  cout << "block array" << endl;
  cout << "  ";
  for(int i = 1; i <= layer.getLength(); i++)
    cout << i % 10;

  cout << endl;

  for(int i = 0; i < layer.getLength(); i++)
  {
    cout << (i+1) % 10 << " ";
    for(int j = 0; j < layer.getWidth(); j++)
      cout << layer.blockArray[i][j];
    cout << endl;
  }
}

bool SmallerVolumeCompare(Cuboid& firstCuboid, Cuboid& secondCuboid)
{
  return firstCuboid.getVolume() < secondCuboid.getVolume();
}

bool LargerVolumeCompare(Cuboid& firstCuboid, Cuboid& secondCuboid)
{
  return firstCuboid.getVolume() > secondCuboid.getVolume();
}

bool LargerAreaCompare(FreeLayer& firstLayer, FreeLayer& secondLayer)
{
  return firstLayer.getArea() > secondLayer.getArea();
}

unsigned short getHeightOfSphere(list<Cuboid>& inputCuboidsList)
{
  list<Cuboid>::iterator iter = inputCuboidsList.begin();
  unsigned short maximalHeight = 0;
  while (iter != inputCuboidsList.end())
  {
    if(iter->getZ() + iter->getHeight() > maximalHeight)
      maximalHeight = iter->getZ() + iter->getHeight();
    ++iter;
  }
  return maximalHeight;
}

bool isEmptyBlock(list<Cuboid>& inputCuboidsList, unsigned short x, unsigned short y, unsigned short z)
{
  list<Cuboid>::iterator iter = inputCuboidsList.begin();
  while (iter != inputCuboidsList.end())
  {
    if(iter->getUsed() == true)
      if(iter->getX() <= x && x < iter->getX() + iter->getLength() &&
         iter->getY() <= y && y < iter->getY() + iter->getWidth() &&
         iter->getZ() <= z && z < iter->getZ() + iter->getHeight())
        return false;

    ++iter;
  }
  return true;
}

void NewFreeCuboidExpand(CuboidalSphere& cuboidalSphere, list<Cuboid>& inputCuboidsList, Cuboid *newFreeCuboid)
{
  bool canExpand;
  unsigned short i, j, k, x, y, z, length, width, height;

  while(1)
  {
    x = newFreeCuboid->getX();
    y = newFreeCuboid->getY();
    z = newFreeCuboid->getZ();
    length = newFreeCuboid->getLength();
    width = newFreeCuboid->getWidth();
    height = newFreeCuboid->getHeight();

    // probujemy powiekszyc prostopadloscian w kierunku +x
    if(x + length < cuboidalSphere.getLength())
    {
      canExpand = true;
      for(j = 0; j < width; j++)
      {
        if(!canExpand)
          break;
        for(k = 0; k < height; k++)
        {
          if((cuboidalSphere.withArray && cuboidalSphere.blockArray[x+length][y+j][z+k] == false) ||
             (!cuboidalSphere.withArray && isEmptyBlock(inputCuboidsList, x+length, y+j, z+k) == false))
          {
            canExpand = false;
            break;
          }
        }
      }
      if(canExpand)
      {
        newFreeCuboid->setLength(length + 1);
        continue;
      }
    }
    // probujemy powiekszyc prostopadloscian w kierunku -x
    if(x > 0)
    {
      canExpand = true;
      for(j = 0; j < width; j++)
      {
        if(!canExpand)
          break;
        for(k = 0; k < height; k++)
        {
          if((cuboidalSphere.withArray && cuboidalSphere.blockArray[x-1][y+j][z+k] == false) ||
             (!cuboidalSphere.withArray && isEmptyBlock(inputCuboidsList, x-1, y+j, z+k) == false))
          {
            canExpand = false;
            break;
          }
        }
      }
      if(canExpand)
      {
        newFreeCuboid->setLength(length + 1);
        newFreeCuboid->setX(x - 1);
        continue;
      }
    }
    // probujemy powiekszyc prostopadloscian w kierunku +y
    if(y + width < cuboidalSphere.getWidth())
    {
      canExpand = true;
      for(i = 0; i < length; i++)
      {
        if(!canExpand)
          break;
        for(k = 0; k < height; k++)
        {
          if((cuboidalSphere.withArray && cuboidalSphere.blockArray[x+i][y+width][z+k] == false) ||
             (!cuboidalSphere.withArray && isEmptyBlock(inputCuboidsList, x+i, y+width, z+k) == false))
          {
            canExpand = false;
            break;
          }
        }
      }
      if(canExpand)
      {
        newFreeCuboid->setWidth(width + 1);
        continue;
      }
    }
    // probujemy powiekszyc prostopadloscian w kierunku -y
    if(y > 0)
    {
      canExpand = true;
      for(i = 0; i < length; i++)
      {
        if(!canExpand)
          break;
        for(k = 0; k < height; k++)
        {
          if((cuboidalSphere.withArray && cuboidalSphere.blockArray[x+i][y-1][z+k] == false) ||
             (!cuboidalSphere.withArray && isEmptyBlock(inputCuboidsList, x+i, y-1, z+k) == false))
          {
            canExpand = false;
            break;
          }
        }
      }
      if(canExpand)
      {
        newFreeCuboid->setWidth(width + 1);
        newFreeCuboid->setY(y - 1);
        continue;
      }
    }
    // probujemy powiekszyc prostopadloscian w kierunku +z
    if(z + height < cuboidalSphere.getHeight())
    {
      canExpand = true;
      for(i = 0; i < length; i++)
      {
        if(!canExpand)
          break;
        for(j = 0; j < width; j++)
        {
          if((cuboidalSphere.withArray && cuboidalSphere.blockArray[x+i][y+j][z+height] == false) ||
             (!cuboidalSphere.withArray && isEmptyBlock(inputCuboidsList, x+i, y+j, z+height) == false))
          {
            canExpand = false;
            break;
          }
        }
      }
      if(canExpand)
      {
        newFreeCuboid->setHeight(height + 1);
        continue;
      }
    }
    // probujemy powiekszyc prostopadloscian w kierunku -z
    if(z > 0)
    {
      canExpand = true;
      for(i = 0; i < length; i++)
      {
        if(!canExpand)
          break;
        for(j = 0; j < width; j++)
        {
          if((cuboidalSphere.withArray && cuboidalSphere.blockArray[x+i][y+j][z-1] == false) ||
             (!cuboidalSphere.withArray && isEmptyBlock(inputCuboidsList, x+i, y+j, z-1) == false))
          {
            canExpand = false;
            break;
          }
        }
      }
      if(canExpand)
      {
        newFreeCuboid->setHeight(height + 1);
        newFreeCuboid->setZ(z - 1);
        continue;
      }
    }
    // tutaj dochodzimy tylko wtedy gdy juz niczego nie da sie powiekszyc
    return ;
  }
}

void NewFreeLayerExpand(Layer& layer, FreeLayer *newFreeLayer)
{
  bool canExpand;
  unsigned short i, x, y, length, width;

  while(1)
  {
    x = newFreeLayer->getX();
    y = newFreeLayer->getY();
    length = newFreeLayer->getLength();
    width = newFreeLayer->getWidth();

    // probujemy powiekszyc prostopadloscian w kierunku +x
    if(x + length < layer.getLength())
    {
      canExpand = true;
      for(i = 0; i < width; i++)
      {
        if(layer.blockArray[x+length][y+i] == false)
        {
          canExpand = false;
          break;
        }
      }
      if(canExpand)
      {
        newFreeLayer->setLength(length + 1);
        continue;
      }
    }
    // probujemy powiekszyc prostopadloscian w kierunku -x
    if(x > 0)
    {
      canExpand = true;
      for(i = 0; i < width; i++)
      {
        if(layer.blockArray[x-1][y+i] == false)
        {
          canExpand = false;
          break;
        }
      }
      if(canExpand)
      {
        newFreeLayer->setLength(length + 1);
        newFreeLayer->setX(x - 1);
        continue;
      }
    }
    // probujemy powiekszyc prostopadloscian w kierunku +y
    if(y + width < layer.getWidth())
    {
      canExpand = true;
      for(i = 0; i < length; i++)
      {
        if(layer.blockArray[x+i][y+width] == false)
        {
          canExpand = false;
          break;
        }
      }
      if(canExpand)
      {
        newFreeLayer->setWidth(width + 1);
        continue;
      }
    }
    // probujemy powiekszyc prostopadloscian w kierunku -y
    if(y > 0)
    {
      canExpand = true;
      for(i = 0; i < length; i++)
      {
        if(layer.blockArray[x+i][y-1] == false)
        {
          canExpand = false;
          break;
        }
      }
      if(canExpand)
      {
        newFreeLayer->setWidth(width + 1);
        newFreeLayer->setY(y - 1);
        continue;
      }
    }
    // tutaj dochodzimy tylko wtedy gdy juz niczego nie da sie powiekszyc
    return ;
  }
}


bool isCuboidInList(list<Cuboid>& freeCuboidsList, Cuboid& freeCuboid)
{
  list<Cuboid>::iterator iter = freeCuboidsList.begin();
  while (iter != freeCuboidsList.end())
  {
    if((*iter).equals(freeCuboid))
      return true;
    ++iter;
  }
  return false;
}

bool isLayerInList(list<FreeLayer>& freeLayersList, FreeLayer& freeLayer)
{
  list<FreeLayer>::iterator iter = freeLayersList.begin();
  while (iter != freeLayersList.end())
  {
    if((*iter).equals(freeLayer))
      return true;
    ++iter;
  }
  return false;
}

void FreeCuboidsSearch(CuboidalSphere& cuboidalSphere, list<Cuboid>& inputCuboidsList, list<Cuboid>& freeCuboidsList)
{
  Cuboid *newFreeCuboid = nullptr;

  for(int x = 0; x < cuboidalSphere.getLength(); x++)
  {
    //cout << x << endl;
    for(int y = 0; y < cuboidalSphere.getWidth(); y++)
    {
      for(int z = 0; z < cuboidalSphere.getHeight(); z++)
      {
        if(cuboidalSphere.withArray)
        {
            if(cuboidalSphere.blockArray[x][y][z] == false)
              continue;
        }

        else if(!cuboidalSphere.withArray)
        {
            if(isEmptyBlock(inputCuboidsList, x, y, z) == false)
            continue;
        }

        newFreeCuboid = new Cuboid(1, 1, 1, x, y, z);
        NewFreeCuboidExpand(cuboidalSphere, inputCuboidsList, newFreeCuboid);

        if(isCuboidInList(freeCuboidsList, *newFreeCuboid))
          free(newFreeCuboid);
        else
        {
          newFreeCuboid->setVolume(newFreeCuboid->getLength()*newFreeCuboid->getWidth()*newFreeCuboid->getHeight());
          freeCuboidsList.push_front(*newFreeCuboid);
        }
      }
    }
  }
}

void FreeLayersSearch(Layer& layer, list<FreeLayer>& freeLayersList)
{
  FreeLayer *newFreeLayer = nullptr;

  for(int x = 0; x < layer.getLength(); x++)
  {
    for(int y = 0; y < layer.getWidth(); y++)
    {
      if(layer.blockArray[x][y] == false)
        continue;

      newFreeLayer = new FreeLayer(1, 1, x, y);
      NewFreeLayerExpand(layer, newFreeLayer);

      if(isLayerInList(freeLayersList, *newFreeLayer))
        free(newFreeLayer);
      else
      {
        newFreeLayer->setArea(newFreeLayer->getLength() * newFreeLayer->getWidth());
        freeLayersList.push_front(*newFreeLayer);
      }
    }
  }
}

void RotateCuboid(Cuboid& cuboid, unsigned short sideA, unsigned short sideB, unsigned short sideC)
{
  cuboid.setLength(sideA);
  cuboid.setWidth(sideB);
  cuboid.setHeight(sideC);
}

// funkcja zwraca true jesli bok prostopadloscianu idealnie wypelnia warstwe
bool CuboidSideCheck(FreeLayer& freeLayer, Cuboid& cuboid, unsigned int& maximalArea,
  Cuboid **mostFlatCuboid, unsigned short& bestLength, unsigned short&  bestWidth, unsigned short&  bestHeight)
{
  unsigned int area;
  if(cuboid.getLength() <= freeLayer.getLength() && cuboid.getWidth() <= freeLayer.getWidth())
    {
      area = cuboid.getLength() * cuboid.getWidth();
      if(area > maximalArea)
      {
        maximalArea = area;
        *mostFlatCuboid = &cuboid;
        bestLength = cuboid.getLength();
        bestWidth = cuboid.getWidth();
        bestHeight = cuboid.getHeight();
      }
      if(area == freeLayer.getArea())
        return true;
    }
    return false;
}

// funkcja pomocnicza do funkcji isFittingInFreeCuboid
bool CuboidConfigurationCheck(Cuboid& inputCuboid, Cuboid& freeCuboid)
{
  return inputCuboid.getLength() <= freeCuboid.getLength() &&
    inputCuboid.getWidth() <= freeCuboid.getWidth() &&
    inputCuboid.getHeight() <= freeCuboid.getHeight();
}

// jesli wejsciowy prostopadloscian pasuje do wolnego prostopadloscianu to funkcja zwraca true, w przeciwnym razie false
bool isFittingInFreeCuboid(Cuboid& inputCuboid, Cuboid& freeCuboid)
{
  unsigned short length, width, height;

  if(freeCuboid.getVolume() < inputCuboid.getVolume())
    return false;

  length = inputCuboid.getLength();
  width = inputCuboid.getWidth();
  height = inputCuboid.getHeight();

  if(CuboidConfigurationCheck(inputCuboid, freeCuboid))
    return true;
  RotateCuboid(inputCuboid, length, height, width);
  if(CuboidConfigurationCheck(inputCuboid, freeCuboid))
    return true;
  RotateCuboid(inputCuboid, width, length, height);
  if(CuboidConfigurationCheck(inputCuboid, freeCuboid))
    return true;
  RotateCuboid(inputCuboid, width, height, length);
  if(CuboidConfigurationCheck(inputCuboid, freeCuboid))
    return true;
  RotateCuboid(inputCuboid, height, length, width);
  if(CuboidConfigurationCheck(inputCuboid, freeCuboid))
    return true;
  RotateCuboid(inputCuboid, height, width, length);
  if(CuboidConfigurationCheck(inputCuboid, freeCuboid))
    return true;

  return false;
}

// jesli nie znalazlo zadnego prostopadloscianu pasujacego do warstwy to funkcja zwraca nullptr
Cuboid* FindMostFlatCuboidFittingTheFreeLayer(list<Cuboid>& inputCuboidsList, FreeLayer& freeLayer,
        unsigned short& bestLength, unsigned short&  bestWidth, unsigned short&  bestHeight)
{
  list<Cuboid>::iterator iter;
  unsigned int maximalArea = 0;
  Cuboid *mostFlatCuboid = nullptr;
  unsigned short length, width, height;

  iter = inputCuboidsList.begin();

  while (iter != inputCuboidsList.end())
  {
    if(iter->getUsed() == true)
    {
      iter++;
      continue;
    }
    length = iter->getLength();
    width = iter->getWidth();
    height = iter->getHeight();

    if(CuboidSideCheck(freeLayer, *iter, maximalArea,
        &mostFlatCuboid, bestLength, bestWidth, bestHeight))
      return mostFlatCuboid;
    RotateCuboid(*iter, length, height, width);
    if(CuboidSideCheck(freeLayer, *iter, maximalArea,
        &mostFlatCuboid, bestLength, bestWidth, bestHeight))
      return mostFlatCuboid;
    RotateCuboid(*iter, width, length, height);
    if(CuboidSideCheck(freeLayer, *iter, maximalArea,
        &mostFlatCuboid, bestLength, bestWidth, bestHeight))
      return mostFlatCuboid;
    RotateCuboid(*iter, width, height, length);
    if(CuboidSideCheck(freeLayer, *iter, maximalArea,
        &mostFlatCuboid, bestLength, bestWidth, bestHeight))
      return mostFlatCuboid;
    RotateCuboid(*iter, height, length, width);
    if(CuboidSideCheck(freeLayer, *iter, maximalArea,
        &mostFlatCuboid, bestLength, bestWidth, bestHeight))
      return mostFlatCuboid;
    RotateCuboid(*iter, height, width, length);
    if(CuboidSideCheck(freeLayer, *iter, maximalArea,
        &mostFlatCuboid, bestLength, bestWidth, bestHeight))
      return mostFlatCuboid;

    iter++;
  }
  return mostFlatCuboid;
}

CuboidalSphere* AddNextLayer(CuboidalSphere *cuboidalSphere)
{
  CuboidalSphere *newCuboidalSphere;

  unsigned short sphereLength = cuboidalSphere->getLength();
  unsigned short sphereWidth = cuboidalSphere->getWidth();
  unsigned short sphereHeight = cuboidalSphere->getHeight();

  newCuboidalSphere = new CuboidalSphere(sphereLength, sphereWidth, sphereHeight + 1, true);

  for(int i = 0; i < sphereLength; i++)
    for(int j = 0; j < sphereWidth; j++)
      for(int k = 0; k < sphereHeight; k++)
        newCuboidalSphere->blockArray[i][j][k] = cuboidalSphere->blockArray[i][j][k];

  for(int i = 0; i < sphereLength; i++)
    for(int j = 0; j < sphereWidth; j++)
      newCuboidalSphere->blockArray[i][j][sphereHeight] = true;

  cuboidalSphere->~CuboidalSphere();
  //cuboidalSphere = newCuboidalSphere;
  return newCuboidalSphere;
}

void SetNextLayer(Layer& layer, list<Cuboid>& inputCuboidsList)
{
  list<Cuboid>::iterator iter;

  layer.setZ(layer.getZ() + 1);

  for(int i = 0; i < layer.getLength(); i++)
        for(int j = 0; j < layer.getWidth(); j++)
          layer.blockArray[i][j] = true;

  iter = inputCuboidsList.begin();

  while (iter != inputCuboidsList.end())
  {
    if(iter->getUsed() == true)
    {
      if(iter->getZ() + iter->getHeight() > layer.getZ())
      {
        for(int i = 0; i < iter->getLength(); i++)
          for(int j = 0; j < iter->getWidth(); j++)
            layer.blockArray[iter->getX()+i][iter->getY()+j] = false;
      }
    }
    iter++;
  }
}

unsigned short Algorithm_1(list<Cuboid>& inputCuboidsList, CuboidalSphere *cuboidalSphere)
{
  list<Cuboid> freeCuboidsList;
  list<Cuboid>::iterator freeCuboidIterator, inputCuboidsIterator;
  bool newCuboidInserted = false, start = true;

  inputCuboidsList.sort(LargerVolumeCompare);
  inputCuboidsIterator = inputCuboidsList.begin();

  while(inputCuboidsIterator != inputCuboidsList.end())
  {
    freeCuboidsList.clear();
    if(start)
    {
      freeCuboidsList.push_front(*(new Cuboid(cuboidalSphere->getLength(), cuboidalSphere->getWidth(), cuboidalSphere->getHeight(), 0, 0, 0)));
      start = false;
    }
    else
      FreeCuboidsSearch(*cuboidalSphere, inputCuboidsList, freeCuboidsList);
    freeCuboidsList.sort(SmallerVolumeCompare);
    freeCuboidIterator = freeCuboidsList.begin();
    newCuboidInserted = false;

    while (freeCuboidIterator != freeCuboidsList.end())
    {
      if(isFittingInFreeCuboid(*inputCuboidsIterator, *freeCuboidIterator))
      {
        inputCuboidsIterator->setUsed(true);
        inputCuboidsIterator->setX(freeCuboidIterator->getX());
        inputCuboidsIterator->setY(freeCuboidIterator->getY());
        inputCuboidsIterator->setZ(freeCuboidIterator->getZ());

        if(cuboidalSphere->withArray)
          for(int i = 0; i < inputCuboidsIterator->getLength(); i++)
            for(int j = 0; j < inputCuboidsIterator->getWidth(); j++)
              for(int k = 0; k < inputCuboidsIterator->getHeight(); k++)
                cuboidalSphere->blockArray[inputCuboidsIterator->getX()+i][inputCuboidsIterator->getY()+j][inputCuboidsIterator->getZ()+k] = false;

        newCuboidInserted = true;
        ++inputCuboidsIterator;
        break;
      }
      ++freeCuboidIterator;
    }
    if(!newCuboidInserted)
    {
      if(cuboidalSphere->withArray)
        cuboidalSphere = AddNextLayer(cuboidalSphere);
      else
        cuboidalSphere->setHeight(cuboidalSphere->getHeight() + 1);
    }
  }
  return cuboidalSphere->getHeight();
}

unsigned short Algorithm_2(list<Cuboid>& inputCuboidsList, Layer& layer)
{
  list<FreeLayer> freeLayersList;
  Cuboid *mostFlatCuboid = nullptr;
  list<FreeLayer>::iterator iter;
  unsigned short numberOfUsedCuboids = 0;
  bool newCuboidInserted = false;
  unsigned short bestLength, bestWidth, bestHeight;

  while(numberOfUsedCuboids < inputCuboidsList.size())
  {
    freeLayersList.clear();
    FreeLayersSearch(layer, freeLayersList);
    freeLayersList.sort(LargerAreaCompare);
    iter = freeLayersList.begin();
    newCuboidInserted = false;

    while (iter != freeLayersList.end())
    {
      if((mostFlatCuboid = FindMostFlatCuboidFittingTheFreeLayer(
        inputCuboidsList, *iter, bestLength, bestWidth, bestHeight)) != nullptr)
      {
        numberOfUsedCuboids++;
        mostFlatCuboid->setUsed(true);
        mostFlatCuboid->setX(iter->getX());
        mostFlatCuboid->setY(iter->getY());
        mostFlatCuboid->setZ(layer.getZ());
        mostFlatCuboid->setLength(bestLength);
        mostFlatCuboid->setWidth(bestWidth);
        mostFlatCuboid->setHeight(bestHeight);

        for(int i = 0; i < mostFlatCuboid->getLength(); i++)
          for(int j = 0; j < mostFlatCuboid->getWidth(); j++)
            layer.blockArray[mostFlatCuboid->getX()+i][mostFlatCuboid->getY()+j] = false;

        newCuboidInserted = true;
        break;
      }
      ++iter;
    }
    if(!newCuboidInserted)
    {
      SetNextLayer(layer, inputCuboidsList);
    }
  }
  return getHeightOfSphere(inputCuboidsList);
}
