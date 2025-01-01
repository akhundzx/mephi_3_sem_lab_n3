#include <iostream>
#include "test_sparce_matrix.h"
#include "test_hash_table.h"
#include "test_sparse_vector.h"
#include "test_histogram.h"
#include "interface.h"
int main() {
    //test_sparse_matrix();
    //test_hashtable();
    //test_sparse_vector();
    //test_histogram();
    MainMenu();
}
//HashTable автонмный, он не может наследоватьс от Мапа
//если хотите, то можете сделать как в STL


//усложняем задачу:
//1)небольшую БД, по которой можно строить гистограмму
//2)перед построением выбрать параметр, а потом диапазон, по которому будет строиться гистограмма