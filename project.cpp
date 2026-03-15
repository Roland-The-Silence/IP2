#include <iostream>
#include <string>
#include <list>
#include <cstring>
#include <memory>
#include "products.h"
#include <sstream>
using namespace std;

namespace Shop 
{
    ProductException::ProductException(const std::string& message) : std::runtime_error("Shop::ProductException: " + message) {}

    class Products::privateVariables 
    {
        public:
            static const int productListLenght = 15;
            list<pair<string, string>> productList[productListLenght]; 
    };

    Products::Products() : pImpl(new privateVariables()) {}

    Products::Products(const Products& other) : pImpl(new privateVariables()) {
        for (int i = 0; i < privateVariables::productListLenght; ++i) {
            this->pImpl->productList[i] = other.pImpl->productList[i];
        }
    }

    Products::~Products() {
        delete pImpl; 
    }

    Products& Products::operator=(const Products& other) {
    if (this == &other) return *this;
    for (int i = 0; i < privateVariables::productListLenght; ++i) {
        this->pImpl->productList[i] = other.pImpl->productList[i];
    }

    return *this;
    }
    
    bool Products::isEmpty() const{
        int sum{};
        for (int i{}; i < privateVariables::productListLenght; i++) {
            sum += pImpl->productList[i].size();
        }

        if (!sum) {
            return true;
        }
        return false;
    }  

    int Products::hashFunction(const std::string name) const {
        std::hash<std::string> hasher;
        size_t hashValue = hasher(name);
        return hashValue % privateVariables::productListLenght;
    }

    void Products::operator+=(const pair<string,string>& item) {
        int idx = hashFunction(item.first);
        auto& cell = pImpl->productList[idx];
        for (const auto& existingItem : cell) {
            if (existingItem.first == item.first) {
                throw ProductException("Product: '" + item.first + "' already exists");
            }
        }
        
        cell.emplace_back(item.first, item.second);
    }

    void Products::operator-=(const string& name) {
        int idx = hashFunction(name);
        auto& cell = pImpl->productList[idx];
        
        for (auto bItr = cell.begin(); bItr != cell.end(); ++bItr) {
            if (bItr->first == name) {
                cell.erase(bItr);
                return;
            }
        }
        
        throw std::out_of_range("Cannot delete: product '" + name + "' not found");
    }

    void Products::operator%=(const pair<string, string>& item) {
        int idx = hashFunction(item.first);
        auto& cell = pImpl->productList[idx];
        
        for (auto& pair : cell) {
            if (pair.first == item.first) {
                pair.second = item.second;
                return;
            }
        }
        
        throw std::out_of_range("Cannot edit: product '" + item.first + "' not found");
    }

    bool Products::operator[](const string& name) const {
        int idx = hashFunction(name);
        for (const auto& item : pImpl->productList[idx]) {
            if (item.first == name) {
                return true; 
            }
        }
        return false;  
    }

    void Products::operator!() {
        for (int i = 0; i < privateVariables::productListLenght; ++i) {
            pImpl->productList[i].clear();
        }
    }

    string Products::toString() const {
        stringstream info;
        info << "------------Assortment------------" << endl;
        for (int i = 0; i < privateVariables::productListLenght; i++) {
            auto& currentList = pImpl->productList[i];
            if (!currentList.empty()) {
                for (const auto& item : currentList) {
                    info << "  - Product: " << item.first
                    << " | Description: " << item.second << "\n";
                }
            }
        }
        info << "--------------------------------\n";
        return info.str();
    }


    size_t Products::getTotalElementCount() const {
        size_t count = 0;
        for (int i = 0; i < privateVariables::productListLenght; ++i) {
            count += pImpl->productList[i].size();
        }
        return count;
    }

    bool Products::operator==(const Products& other) const {
        if (this->getTotalElementCount() != other.getTotalElementCount()) {
            return false;
        }
        
        for (int i = 0; i < privateVariables::productListLenght; ++i) {
            const auto& thisBucket = this->pImpl->productList[i];
            const auto& otherBucket = other.pImpl->productList[i];
            
            if (thisBucket.size() != otherBucket.size()) {
                return false;
            }
            
            for (const auto& thisItem : thisBucket) {
                bool found = false;
                for (const auto& otherItem : otherBucket) {
                    if (thisItem.first == otherItem.first && 
                        thisItem.second == otherItem.second) {
                        found = true;
                        break;
                    }
                }
                if (!found) return false;
            }
        }
        
        return true; 
    }

    bool Products::operator!=(const Products& other) const {
        return !(*this == other);
    }

    bool Products::operator<(const Products& other) const {

        return this->getTotalElementCount() < other.getTotalElementCount();
    }

    bool Products::operator<=(const Products& other) const {
        return this->getTotalElementCount() <= other.getTotalElementCount();
    }

    bool Products::operator>(const Products& other) const {
        return this->getTotalElementCount() > other.getTotalElementCount();
    }

    bool Products::operator>=(const Products& other) const {
        return this->getTotalElementCount() >= other.getTotalElementCount();
    }

}




