# Uncarved clean-leaf worklist (first-try match candidates)

Named, uncarved, leaf (no calls), no VU0/quadword, 3-15 instructions —
the functions most likely to byte-match from straightforward C on the first
try (the reliable-progress tier). Workflow: dump asm from asm/cod/000000.s,
write C, `ee-cc-wrap.py -c -O2 -G0 -f=-freorder-blocks`, compare .text bytes,
carve. Regenerate with the census snippet in the session log.

**47 candidates**, smallest first:

| insns | addr | name |
|------:|------|------|
| 3 | 0x00297B88 | cEvent_getCutFrame |
| 3 | 0x002AF638 | cMessDrawFont_setRubyData |
| 3 | 0x002AF648 | cMessDrawFont_setDrawCounter |
| 4 | 0x002AF628 | cMessDrawFont_setBodyData |
| 4 | 0x002AF658 | cMessDrawFont_setDrawPos |
| 5 | 0x001FA820 | cCoreSave_initAddGold |
| 5 | 0x001FAC98 | cCoreSave_setVital |
| 5 | 0x001FBEB8 | cCoreSave_clearKillNpcNum |
| 5 | 0x001FBF60 | cCoreSave_initContinueNum |
| 5 | 0x002D6560 | CustomIDWork_SetMessNo |
| 6 | 0x002D8DE0 | cWorldLight_Gaibu_set_off |
| 9 | 0x00299320 | cEventConfig_setEventNo |
| 10 | 0x001BD178 | cOmDoor_setLock |
| 10 | 0x001E3218 | Slot1_SetSlotLayer |
| 10 | 0x001E6780 | Slot2_SetSlotLayer |
| 10 | 0x001FAB28 | cCoreSave_clearGodItem |
| 10 | 0x002BF108 | cRoomSave_getFree |
| 10 | 0x002D6630 | CustomIDWork_SetLocalPosX |
| 10 | 0x002D6658 | CustomIDWork_SetLocalPosY |
| 10 | 0x002D66D0 | CustomIDWork_SetOffsetPosX |
| 10 | 0x002D66F8 | CustomIDWork_SetOffsetPosY |
| 10 | 0x00308D40 | HideModelMgr_ClearHiddenModelList |
| 11 | 0x00289038 | cEma2_SetEscPos |
| 11 | 0x002A9420 | cGameObj_setRot |
| 11 | 0x002A9BC0 | cHeatSys_GetHeatLv |
| 11 | 0x002AEAD0 | cMessage_getMessageAddr |
| 11 | 0x002D6A30 | CustomIDWork_ResetScaleAnim |
| 11 | 0x0038B858 | is_reading__7filebuf |
| 11 | 0x0038BD60 | gbump__9streambufi |
| 12 | 0x0014E930 | cObj_setSuspend |
| 12 | 0x002AED10 | cMessage_searchWorkId |
| 12 | 0x0031BD88 | classPAD_WORK_Pad_act_all_stop |
| 12 | 0x003A4F88 | copysignf |
| 13 | 0x001FB830 | cCoreSave_getComboMax |
| 13 | 0x00201F48 | cScenario_debugPrint |
| 13 | 0x00299368 | classCFILTER_TAG_initialize |
| 13 | 0x002D6510 | CustomIDWork_SetChildNoDisp |
| 13 | 0x002D67B0 | CustomIDWork_SetMoveOffsetPosXSin |
| 14 | 0x001FA6C0 | cCoreSave_getClearNum |
| 14 | 0x00389770 | skip__7istreami |
| 14 | 0x0038D038 | _IO_remove_marker |
| 14 | 0x0038D080 | _IO_marker_delta |
| 15 | 0x001FBF90 | cCoreSave_setClearStage |
| 15 | 0x0026F0E0 | cEm00_ckDown |
| 15 | 0x002D6680 | CustomIDWork_SetLocalPosXY |
| 15 | 0x002D6720 | CustomIDWork_SetOffsetPosXY |
| 15 | 0x002E13D8 | Moji_size_set |
