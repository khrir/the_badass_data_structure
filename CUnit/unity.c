#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "../Huffman_implementacao/freq.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

void test_criar_nova_freq(void){
   ulli *freq = criar_nova_freq();
   CU_ASSERT(freq[0] == 0);
   CU_ASSERT(freq[255] == 0);
}

void test_contar_frequencia(void){
   FILE *arq = fopen("CUnit/public/arquivo_test.txt", "rb");

   ulli *freq = contar_frequencia_from_file(arq);
   CU_ASSERT(freq['a'] == 26);
   CU_ASSERT(freq['b'] == 3);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test of criar_nova_freq()", test_criar_nova_freq)) ||
       (NULL == CU_add_test(pSuite, "test of contar_frequencia()", test_contar_frequencia)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}