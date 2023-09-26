#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <iomanip> 
# include <list>
# include <vector>
# include <algorithm>
# include <exception>
# include <sstream>
# include <ctime>
# include <cstring>
# include <set>

# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET "\033[m" 

class PmergeMe
{
    typedef std::list<int>::const_iterator ConstIntListIterator;

    typedef std::vector<int>::iterator IntVecIterator;
    typedef std::vector<int>::const_iterator ConstIntVecIterator;

    struct UnpairedElemenat {
        size_t length;
        int value;
        int position;
    };
    typedef enum 
    {
        LIST,
        VECTOR,
    } E_Type;
    
    private:
        std::list<int>              input_;
        std::list<int>              List_mainChain_;
        std::vector<int>            Vector_mainChain_;
        std::set<int>               sorted_;
        int size_;
    
    public:
        PmergeMe();
        PmergeMe(const PmergeMe & r);
        ~PmergeMe();
        PmergeMe & operator= (const PmergeMe &other);

        std::list<int> getList() const;
        std::vector<int> getVector() const;
        void printClock(std::clock_t start, std::clock_t end, E_Type type);
    
        template <typename T>
        void FordJohnsonAlgorithm(int size, T numbers) {
            this->size_ = size;
            try {
                this->initContainer(size, numbers);
            } catch (std::exception &e) {
                std::cerr << e.what() << " " << "line: " << __LINE__ << std::endl;
                std::exit(1);
            }


            std::clock_t list_start;
            std::clock_t list_end;
            try {
                list_start = std::clock();
                mergeInsertionSort(this->List_mainChain_, 1);
                list_end = std::clock();
            } catch (std::exception &e) {
                std::cerr << e.what() << " " << "line: " << __LINE__ << std::endl;
                std::exit(1);
            }
            
            std::clock_t vector_start ;
            std::clock_t vector_end ;
            try {
                vector_start = std::clock();
                mergeInsertionSort(this->Vector_mainChain_, 1);
                vector_end = std::clock();
            } catch (std::exception &e) {
                std::cerr << e.what() << " " << "line: " << __LINE__ << std::endl;
                std::exit(1);
            }

            try {
                if(!isSorted()) {
                    std::cout << "Before:  ";
                    PmergeMe::printContainer(input_);
                    std::cout << "After:   ";
                    PmergeMe::printContainer(List_mainChain_);
                    printClock(list_start, list_end, LIST);
                    printClock(vector_start, vector_end, VECTOR);
                }
            } catch ( std::exception &e ) {
                std::cerr << e.what() << " " << "line: " << __LINE__ << std::endl;
                std::exit(1);
            } 

        }
    
    private:
        int                         stoi(const std::string& str);
        void                        initContainer(int size, int numbers[]);
        void                        initContainer(int size, char* numbers);
        void                        initContainer(int size, char* numbers[]);
        void                        initContainer(int size, std::string numbers);
        void                        initContainer(int size, std::string numbers[]);
        int                         calculateJacobsthalNumber(int n);

    /**
     * list
    */
        //processPairs
        bool                        shouldSwapPairs(const std::list<int>& lst, int pairSize, int startIndex);
        void                        swapPairs(std::list<int>& lst, int pairSize, int startIndex);
        bool                        isPairPresent(const std::list<int>& lst, int pairSize, size_t startIndex);
        void                        processPairs(std::list<int>& lst, std::list<int>& subChain, int pairSize, UnpairedElemenat & unpairedData);

        //splitIntoMainAndSubChains
        void                        splitIntoMainAndSubChains(std::list<int>& mainChain, std::list<int>& subChain, int pairSize);
    
        // first insert
        void                        prependSubchainToMain(std::list<int>& mainChain, std::list<int>& subChain, int pairSize);

        // insert
        void                        mergeSubIntoMain(std::list<int>& mainChain, std::list<int>& subChain, int pairSize, UnpairedElemenat& unpairedData);
        int                         lower_bound(std::list<int> & mainChain, int key,int pairSize, UnpairedElemenat& unpairedData, int endpoint);
        void                        createComparisonListFromMainChain(std::list<int>& lst, std::list<int>& mainChain, int pairSize, UnpairedElemenat& unpairedData, int endpoint);
        bool                        elementExceedsKey(std::list<int>& lst, int index, int key);
        int                         find_lower_bound(std::list<int> & lst, int key);
        void                        insertSubChain(std::list<int> & mainChain, int insertPosition, ConstIntListIterator begin, ConstIntListIterator end);
        void                        insertSegmentToMainChain(std::list<int>& mainChain, std::list<int>& subChain, int segmentStart, int segmentEnd, int insertionPoint, int pairSize);
    /**
     * vector
    */
        //processPairs
        bool                        shouldSwapPairs(const std::vector<int>& vec, int pairSize, int startIndex);
        void                        swapPairs(std::vector<int>& vec, int pairSize, int startIndex);
        bool                        isPairPresent(const std::vector<int>& vec, int pairSize, size_t startIndex);
        void                        processPairs(std::vector<int>& vec, std::vector<int>& subChain, int pairSize, UnpairedElemenat & unpairedData);

        //splitIntoMainAndSubChains
        void                        splitIntoMainAndSubChains(std::vector<int>& mainChain, std::vector<int>& subChain, int pairSize);
        
        // first insert
        void                        prependSubchainToMain(std::vector<int>& mainChain, std::vector<int>& subChain, int pairSize);
        
        // insert
        void                        mergeSubIntoMain(std::vector<int>& mainChain, std::vector<int>& subChain, int pairSize, UnpairedElemenat& unpairedData);
        int                         lower_bound(std::vector<int> & mainChain, int key,int pairSize, UnpairedElemenat& unpairedData, int endpoint);
        void                        createComparisonVectorFromMainChain(std::vector<int>& lst, std::vector<int>& mainChain, int pairSize, UnpairedElemenat& unpairedData, int endpoint);
        bool                        elementExceedsKey(std::vector<int>& lst, int index, int key);
        int                         find_lower_bound(std::vector<int> & lst, int key);
        void                        insertSubChain(std::vector<int> & mainChain, int insertPosition, ConstIntVecIterator begin, ConstIntVecIterator end);
        void                        insertSegmentToMainChain(std::vector<int>& mainChain, std::vector<int>& subChain, int segmentStart, int segmentEnd, int insertionPoint, int pairSize);


        template <typename T>
        void mergeInsertionSort(T & mainChain,int pairSize) {
            if (mainChain.size() <= 2 * static_cast<size_t>(pairSize)) {
                if(mainChain.size()  <= static_cast<size_t>(pairSize)) return;

                #ifdef PAIR
                #ifdef LISTDEBUG
                    testPairDebug(mainChain, pairSize, "Before process pairs.");
                #endif
                #ifdef VECTORDEBUG
                    testPairDebug(mainChain, pairSize, "Before process pairs.");
                #endif
                #endif
                if(!shouldSwapPairs(mainChain, pairSize, 0)) { swapPairs(mainChain, pairSize, 0);}
                #ifdef PAIR
                #ifdef LISTDEBUG
                    testPairDebug(mainChain, pairSize, "After process pairs.");
                #endif
                #ifdef VECTORDEBUG
                    testPairDebug(mainChain, pairSize, "After process pairs.");
                #endif
                #endif
                return ; 
            } 
            
            T subChain;
            UnpairedElemenat unpairedData;

            #ifdef PAIR
                #ifdef LISTDEBUG
                    testPairDebug(mainChain, pairSize, "Before process pairs.");
                #endif
                #ifdef VECTORDEBUG
                    testPairDebug(mainChain, pairSize, "Before process pairs.");
                #endif
            #endif
            processPairs(mainChain, subChain, pairSize, unpairedData);
            #ifdef PAIR
                #ifdef LISTDEBUG
                    testPairDebug(mainChain, pairSize, "After process pairs.");
                #endif
                #ifdef VECTORDEBUG
                    testPairDebug(mainChain, pairSize, "After process pairs.");
                #endif
            #endif
            
            mergeInsertionSort(mainChain, pairSize * 2);

            #ifdef SEPARATE
                #ifdef LISTDEBUG
                    testSeparateDebug(mainChain, subChain, pairSize, "Before split into main and sub-chains.");
                #endif
                #ifdef VECTORDEBUG
                    testSeparateDebug(mainChain, subChain, pairSize, "Before split into main and sub-chains.");
                #endif
            #endif
            splitIntoMainAndSubChains(mainChain, subChain, pairSize);
            #ifdef SEPARATE
                #ifdef LISTDEBUG
                    testSeparateDebug(mainChain, subChain, pairSize, "After split into main and sub-chains.");
                #endif
                #ifdef VECTORDEBUG
                    testSeparateDebug(mainChain, subChain, pairSize, "After split into main and sub-chains.");
                #endif
            #endif

            #ifdef FIRST
                #ifdef LISTDEBUG
                    testFirstInsertDebug(mainChain, subChain, pairSize, "Before prepend sub-chain to main.");
                #endif
                #ifdef VECTORDEBUG
                    testFirstInsertDebug(mainChain, subChain, pairSize, "Before prepend sub-chain to main.");
                #endif
            #endif
            prependSubchainToMain(mainChain, subChain, pairSize);
            #ifdef FIRST
                #ifdef LISTDEBUG
                    testFirstInsertDebug(mainChain, subChain, pairSize, "After prepend sub-chain to main.");
                #endif
                #ifdef VECTORDEBUG
                    testFirstInsertDebug(mainChain, subChain, pairSize, "After prepend sub-chain to main.");
                #endif
            #endif
            
            #ifdef INSERT
                #ifdef LISTDEBUG
                    testInsertDebug(mainChain, subChain, pairSize, "Before merge insert", 0, 0);
                #endif
                #ifdef VECTORDEBUG
                    testInsertDebug(mainChain, subChain, pairSize, "Before merge insert", 0, 0);
                #endif
            #endif
            mergeSubIntoMain(mainChain, subChain, pairSize, unpairedData);
            #ifdef INSERT
                #ifdef LISTDEBUG
                    testInsertDebug(mainChain, subChain, pairSize, "After merge Insert",0 ,0);
                #endif
                #ifdef VECTORDEBUG
                    testInsertDebug(mainChain, subChain, pairSize, "After merge Insert",0 ,0);
                #endif
                std::cout << std::endl << std::endl;
            #endif
        }
    
    
    //utils
    private:
        template <typename T>
        typename std::vector<T>::iterator getIteratorAt(std::vector<T>& vec, size_t index) {
            if (index >= vec.size()) { return vec.end(); }

            typename std::vector<T>::iterator it = vec.begin();
            it += index;
            return it;
        }

        template <typename T>
        typename std::list<T>::iterator getIteratorAt(std::list<T>& lst, size_t index) {
            if (index >= lst.size()) { return lst.end(); }

            typename std::list<T>::iterator it = lst.begin();
            std::advance(it, index);
            return it;
        }

        template <typename T>
        typename std::vector<T>::const_iterator getConstIteratorAt(const std::vector<T>& vec, size_t index) {
            if (index >= vec.size()) { return vec.end(); }

            typename std::vector<T>::const_iterator it = vec.begin();
            it += index;
            return it;
        }

        template <typename T>
        typename std::list<T>::const_iterator getConstIteratorAt(const std::list<T>& lst, size_t index) {
            if (index >= lst.size()) { return lst.end(); }

            typename std::list<T>::const_iterator it = lst.begin();
            std::advance(it, index);
            return it;
        }

        template <typename T>
        typename std::vector<T>::const_iterator advanceTo(std::vector<T>& vec, typename std::vector<T>::const_iterator itr, size_t index) {
            if (itr + index < vec.end()) {
                return itr + index;
            } else {
                return vec.end();
            }
        }

        template <typename T>
        typename std::list<T>::const_iterator advanceTo(std::list<T>& lst, typename std::list<T>::const_iterator itr, size_t index) {
            for (size_t i=0; i< index ; ++i) {
                ++itr;
                if(itr == lst.end()) return lst.end();
            }
            return itr;
        }

        template <typename T>
        T getElementAtIndex(const std::vector<T>& vec, size_t index) {
            if (index >= vec.size()) { throw std::out_of_range("Index out of bounds"); }

            typename std::vector<T>::const_iterator it = vec.begin();
            it += index;
            return *it;
        }

        template <typename T>
        T getElementAtIndex(const std::list<T>& lst, size_t index) {
            if (index >= lst.size()) { throw std::out_of_range("Index out of bounds"); }

            typename std::list<T>::const_iterator it = getConstIteratorAt(lst, index);

            return *it;
        }

        public:
        template <typename T>
        static void printContainer(const T& container) {
            for (typename T::const_iterator it = container.begin(); it != container.end(); ) {
                std::cout << *it;
                ++it;
                if(it != container.end())
                    std::cout << " ";
            }
            std::cout << std::endl;
        }

        bool isSorted() {
            ConstIntListIterator list_it = List_mainChain_.begin();

            IntVecIterator vector_it = Vector_mainChain_.begin();

            std::set<int>::iterator set_it = sorted_.begin();

            while (set_it != sorted_.end()) {
                if( *set_it != *list_it) throw std::logic_error("The sequence is not sorted.");
                if( list_it == List_mainChain_.end() ) throw std::logic_error("The sequence is not sorted.");
                ++list_it;
                ++set_it;
            }
            if( list_it != List_mainChain_.end() ) throw std::logic_error("The sequence is not sorted.");

            set_it = sorted_.begin();
            while (set_it != sorted_.end()) {
                if( *set_it != *vector_it) throw std::logic_error("The sequence is not sorted.");
                if( vector_it == Vector_mainChain_.end() ) throw std::logic_error("The sequence is not sorted.");
                ++vector_it;
                ++set_it;
            }
            if( vector_it != Vector_mainChain_.end() ) throw std::logic_error("The sequence is not sorted.");
            return false;
        }



    //debug
    public:
        template <typename T>
        void testPairDebug(T main, int pairSize, std::string s) {
            typedef typename T::iterator Iter;
            int i = 0;
            if(s.compare(0,6,"Before", 0, 6) == 0) {
                std::cout << CYAN << "---------------------------------------------------------------------------------------------------------------------" << RESET << std::endl << std::endl;
                std::cout << GREEN;
                std::cout << s << " pairSize: " << pairSize << std::endl;
                std::cout << RESET;
            } else {
                std::cout << YELLOW;
                std::cout << s << " pairSize: " << pairSize << std::endl;
                std::cout << RESET;
            }
            for(Iter it=main.begin(); it != main.end(); ++it) {
                if(i == 0) std::cout << " [ ";
                std::cout << *it ;
                ++i;
                if(i == pairSize) { std::cout << " | "; }
                else { std::cout << " " ;} 
                if(i == pairSize * 2) {
                std::cout << "] ";
                i = 0;
                }
            }
            std::cout << std::endl << std::endl;;
        }

        template <typename T>
        void testSeparateDebug(T main, T sub,int pairSize, std::string s) {
            typedef typename T::iterator Iter;
            int i = 0;
            if(s.compare(0,6,"Before", 0, 6) == 0) {
                std::cout << CYAN << "---------------------------------------------------------------------------------------------------------------------" << RESET << std::endl << std::endl;
                std::cout << GREEN;
                std::cout << s << " pairSize: " << pairSize << std::endl;
                std::cout << RESET;
                for(Iter it=main.begin(); it != main.end(); ++it) {
                    if(i == 0) std::cout << " [ ";
                    std::cout << *it ;
                    ++i;
                    if(i == pairSize) { std::cout << " | "; }
                    else { std::cout << " " ;} 
                    if(i == pairSize * 2) {
                    std::cout << "] ";
                    i = 0;
                    }
                }
                std::cout << std::endl << std::endl;;
            } else {
                std::cout << YELLOW;
                std::cout << s << " pairSize: " << pairSize << std::endl;
                std::cout << RESET;
                std::cout << BLUE;
                std::cout << "main-chain" << std::endl;
                std::cout << RESET;
                for(Iter it=main.begin(); it != main.end(); ++it) {
                    if(i == 0) std::cout << " [ ";
                    std::cout << *it ;
                    ++i;
                    if(i == pairSize) { 
                        std::cout << " ] ";
                        i = 0;
                    }
                    else { std::cout << " " ;} 
                }
                std::cout << std::endl;
                i=0;
                std::cout << BLUE;
                std::cout << "sub-chain" << std::endl;
                std::cout << RESET;
                for(Iter it=sub.begin(); it != sub.end(); ++it) {
                    if(i == 0) std::cout << " [ ";
                    std::cout << *it ;
                    ++i;
                    if(i == pairSize) { 
                        std::cout << " ] ";
                        i=0;
                    }
                    else { std::cout << " " ;} 
                }
                std::cout << std::endl << std::endl;;
            }
        }

        template <typename T>
        void testFirstInsertDebug(T main, T sub,int pairSize, std::string s) {
            typedef typename T::iterator Iter;
            int i = 0;
            if(s.compare(0,6,"Before", 0, 6) == 0) {
                std::cout << CYAN << "---------------------------------------------------------------------------------------------------------------------" << RESET << std::endl << std::endl;
                std::cout << GREEN;
                std::cout << s << " pairSize: " << pairSize << std::endl;
                std::cout << RESET;
            } else {
                std::cout << YELLOW;
                std::cout << s << " pairSize: " << pairSize << std::endl;
                std::cout << RESET;
                std::cout << BLUE;
                std::cout << "main-chain" << std::endl;
                std::cout << RESET;
            }
            for(Iter it=main.begin(); it != main.end(); ++it) {
                if(i == 0) std::cout << " [ ";
                std::cout << *it ;
                ++i;
                if(i == pairSize) { 
                    std::cout << " ] ";
                    i = 0;
                }
                else { std::cout << " " ;} 
            }
            std::cout << std::endl;
            i=0;
            std::cout << BLUE;
            std::cout << "sub-chain" << std::endl;
            std::cout << RESET;
            for(Iter it=sub.begin(); it != sub.end(); ++it) {
                if(i == 0) std::cout << " [ ";
                std::cout << *it ;
                ++i;
                if(i == pairSize) { 
                    std::cout << " ] ";
                    i=0;
                }
                else { std::cout << " " ;} 
            }
            std::cout << std::endl << std::endl;;
        }

        template <typename T>
        void testInsertDebug(T main, T sub,int pairSize, std::string s, int key, int jacoNum) {
            typedef typename T::iterator Iter;
            int i = 0;
            if(s.compare(0,6,"Before", 0, 6) == 0) {
                std::cout << CYAN << "---------------------------------------------------------------------------------------------------------------------" << RESET << std::endl << std::endl;
                std::cout << GREEN;
                std::cout << s << " pairSize: " << pairSize << std::endl;
                std::cout << RESET;
                for(Iter it=main.begin(); it != main.end(); ++it) {
                    if(i == 0) std::cout << " [ ";
                    std::cout << *it ;
                    ++i;
                    if(i == pairSize) { 
                        std::cout << " ] ";
                        i = 0;
                    }
                    else { std::cout << " " ;} 
                }
                std::cout << std::endl;
                i=0;
                std::cout << BLUE;
                std::cout << "sub-chain" << std::endl;
                std::cout << RESET;
                for(Iter it=sub.begin(); it != sub.end(); ++it) {
                    if(i == 0) std::cout << " [ ";
                    std::cout << *it ;
                    ++i;
                    if(i == pairSize) { 
                        std::cout << " ] ";
                        i=0;
                    }
                    else { std::cout << " " ;} 
                }
                std::cout << std::endl << std::endl;;
            } else if(s.compare(0,5,"After", 0, 5) == 0) {
                std::cout << YELLOW;
                std::cout << s << " pairSize: " << pairSize << std::endl;
                std::cout << RESET;
                std::cout << BLUE;
                std::cout << "main-chain" << std::endl;
                std::cout << RESET;
                i =0;
                for(Iter it=main.begin(); it != main.end(); ++it) {
                    if(i == 0) std::cout << " [ ";
                    std::cout << *it ;
                    ++i;
                    if(i == pairSize) { 
                        std::cout << " ] ";
                        i = 0;
                    }
                    else { std::cout << " " ;} 
                }
                std::cout << std::endl;
                std::cout << BLUE;
                std::cout << "sub-chain" << std::endl;
                std::cout << RESET;
                for(Iter it=sub.begin(); it != sub.end(); ++it) {
                    std::cout << *it ;
                    std::cout << " " ;
                }
                std::cout << std::endl << std::endl;;
            } else {                
                std::cout << \
                BLUE << \
                "[" << \
                RESET << \
                "n: " << \
                jacoNum << \
                " key: " << \
                key << \
                BLUE << \
                "]" << \
                RESET;
            }
        }
};

#endif
