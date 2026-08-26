#include "ObjectManager.h"

std::unordered_map<int, ObjectManager::Object> ObjectManager::objectList;
std::vector<int> ObjectManager::printOrder;