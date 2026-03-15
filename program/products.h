#ifndef products_h
#define products_h

#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <cstring>
#include <stdexcept>
using namespace std;

namespace Shop 
{
    /**
     * @brief Custom exception class for duplicate product errors
     * 
     * Thrown when attempting to add a product with a name that already exists
     * in the collection. Derived from std::runtime_error.
     */
    class ProductException : public std::runtime_error 
    {
        public:
            /**
             * @brief Constructs a ProductException with a specific message
             * @param message Description of what caused the exception
             */
            explicit ProductException(const std::string& message);
    };

    /**
     * @brief A hash table implementation for storing products with descriptions
     * 
     * This class implements a collection of products using a hash table
     * with separate chaining. Each product has a unique name (key) and
     * a description (value). The class follows the Pimpl idiom to hide 
     * implementation details and provides CRUD operations through operators.
     */
    class Products
    {
        private:
            /**
             * @brief Forward declaration of the inner implementation class
             * 
             * Contains all private members: the hash table array and its size.
             * Defined in the .cpp file to maintain encapsulation (Pimpl idiom).
             */
            class privateVariables;
            
            /**
             * @brief Pointer to the implementation (Pimpl)
             * 
             * Points to dynamically allocated privateVariables object.
             * Allows hiding implementation details from the header file.
             */
            privateVariables* pImpl;
            
        public:
            // ============ CONSTRUCTORS / DESTRUCTOR ============
            
            /**
             * @brief Default constructor
             * 
             * Creates an empty product collection with all hash buckets empty.
             * Allocates memory for the private implementation.
             */
            Products();
            
            /**
             * @brief Destructor
             * 
             * Cleans up dynamically allocated memory for the private implementation.
             * Ensures no memory leaks when object goes out of scope.
             */
            ~Products();
            
            /**
             * @brief Copy constructor
             * 
             * Performs a deep copy of another Products object.
             * Creates a new independent copy with the same products.
             * 
             * @param other The Products object to copy from
             */
            Products(const Products& other);
            
            /**
             * @brief Copy assignment operator
             * 
             * Performs a deep copy of another Products object.
             * Handles self-assignment correctly.
             * 
             * @param other The Products object to assign from
             * @return Reference to this object after assignment
             */
            Products& operator=(const Products& other);

            // ============ COMPARISON OPERATORS ============
            
            /**
             * @brief Equality comparison operator
             * 
             * Compares two product collections for exact equality.
             * Two collections are equal if they contain the exact same
             * products (same names and same descriptions).
             * 
             * @param other The Products object to compare with
             * @return true if both collections have identical products, false otherwise
             */
            bool operator==(const Products& other) const;
            
            /**
             * @brief Inequality comparison operator
             * 
             * Checks if two product collections are different.
             * 
             * @param other The Products object to compare with
             * @return true if collections are different, false if they are equal
             */
            bool operator!=(const Products& other) const;
            
            /**
             * @brief Less than comparison operator
             * 
             * Compares based on the total number of products.
             * A collection is "less than" another if it has fewer products.
             * 
             * @param other The Products object to compare with
             * @return true if this collection has fewer products, false otherwise
             */
            bool operator<(const Products& other) const;
            
            /**
             * @brief Less than or equal comparison operator
             * 
             * Compares based on the total number of products.
             * 
             * @param other The Products object to compare with
             * @return true if this collection has fewer or equal products
             */
            bool operator<=(const Products& other) const;
            
            /**
             * @brief Greater than comparison operator
             * 
             * Compares based on the total number of products.
             * A collection is "greater than" another if it has more products.
             * 
             * @param other The Products object to compare with
             * @return true if this collection has more products, false otherwise
             */
            bool operator>(const Products& other) const;
            
            /**
             * @brief Greater than or equal comparison operator
             * 
             * Compares based on the total number of products.
             * 
             * @param other The Products object to compare with
             * @return true if this collection has more or equal products
             */
            bool operator>=(const Products& other) const;
            
            // ============ UTILITY METHODS ============
            
            /**
             * @brief Checks if the collection is empty
             * 
             * @return true if there are no products in the collection, false otherwise
             */
            bool isEmpty() const;
            
            /**
             * @brief Clears all products from the collection
             * 
             * Removes every product from every hash bucket,
             * leaving the collection completely empty.
             */
            void operator!();
            
            /**
             * @brief Hash function for product names
             * 
             * Computes the hash bucket index for a given product name.
             * Uses std::hash internally and maps to valid bucket range.
             * 
             * @param name The product name to hash
             * @return Integer bucket index between 0 and (productListLength - 1)
             */
            int hashFunction(const std::string name) const;
            
            // ============ CRUD OPERATIONS ============
            
            /**
             * @brief Adds a new product to the collection (CREATE)
             * 
             * Creates a new entry with the given product name and description.
             * The product name must be unique.
             * 
             * @param item Pair containing (product name, product description)
             * @throws ProductException if a product with the same name already exists
             */
            void operator+=(const std::pair<std::string, std::string>& item);
            
            /**
             * @brief Removes a product from the collection (DELETE)
             * 
             * Deletes the product with the specified name.
             * 
             * @param name The name of the product to delete
             * @throws std::out_of_range if no product with the given name exists
             */
            void operator-=(const std::string& name);
            
            /**
             * @brief Updates an existing product's description (UPDATE)
             * 
             * Modifies the description of an existing product.
             * The product name remains unchanged.
             * 
             * @param item Pair containing (product name, new description)
             * @throws std::out_of_range if no product with the given name exists
             */
            void operator%=(const std::pair<std::string, std::string>& item);
            
            /**
             * @brief Searches for a product by name (READ)
             * 
             * Checks whether a product with the given name exists in the collection.
             * 
             * @param name The product name to search for
             * @return true if the product exists, false otherwise
             */
            bool operator[](const std::string& name) const;
            
            // ============ OUTPUT METHODS ============
            
            /**
             * @brief Generates a string representation of all products
             * 
             * Creates a formatted string containing all products
             * with their names and descriptions, organized by hash bucket.
             * 
             * @return Formatted string with complete product listing
             */
            std::string toString() const;
            
            /**
             * @brief Gets the total number of products in the collection
             * 
             * Counts all products across all hash buckets.
             * 
             * @return The total count of products
             */
            size_t getTotalElementCount() const;
    };
}

#endif