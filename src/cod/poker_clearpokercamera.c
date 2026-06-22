/* Poker_ClearPokerCamera — restore the player camera (D_00463050) to mode 0.
 * sn-2.95.3-136. */

extern void cCamManager_setPlCamera(void *, int);
extern char D_00463050;

__attribute__((section(".text.Poker_ClearPokerCamera")))
void Poker_ClearPokerCamera(void) {
    cCamManager_setPlCamera(&D_00463050, 0);
}
