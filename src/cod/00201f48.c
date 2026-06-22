/* cScenario_debugPrint — a stripped (empty) variadic debug print: the body is
 * gone but the vararg register save area remains. Compiled with sn-2.95.3-136. */

__attribute__((section(".text.cScenario_debugPrint")))
void cScenario_debugPrint(int a0, int a1, ...) {}
